BASENAME  = bm64
VERSION  := us

VERSIONS  := us eu
ifeq ($(filter $(VERSION),$(VERSIONS)),)
$(error Unknown VERSION '$(VERSION)'; expected one of $(VERSIONS))
endif

# asm/ and assets/ hold one version at a time; leftovers from another
# VERSION would link in silently and only show as a sha1 mismatch.
ifneq ($(filter-out clean setup,$(or $(MAKECMDGOALS),all)),)
TREE_VERSION := $(shell cat .version 2>/dev/null)
ifneq ($(TREE_VERSION),)
ifneq ($(TREE_VERSION),$(VERSION))
$(error tree holds $(TREE_VERSION) output; run 'make clean' first)
endif
endif
endif

# SHIFT=1 builds into its own directory, so a shifted and a matching build
# sit side by side (tools/shift_check.py compares them)
SHIFT     ?= 0
BUILD_DIR = build/$(VERSION)$(if $(filter-out 0,$(SHIFT)),-shift)
TOOLS_DIR = tools
VENV      = .env
PYTHON    = $(VENV)/bin/python3

CROSS     = mips-linux-gnu-
AS        = $(CROSS)as
LD        = $(CROSS)ld
OBJCOPY   = $(CROSS)objcopy

ASFLAGS   = -EB -mtune=vr4300 -march=vr4300 -mabi=32 -I include
BASEROM   = baserom.$(VERSION).z64
CONFIG    = $(BASENAME).$(VERSION).yaml
LD_SCRIPT = $(BASENAME).$(VERSION).ld
TARGET    = $(BUILD_DIR)/$(BASENAME).$(VERSION)

# splat writes the linker script; every object it names is built below.
# Paths in it are relative to the repo root and start with build/.
LD_OBJS  := $(shell grep -o 'build/[^ ()]*\.o' $(LD_SCRIPT) 2>/dev/null)
O_FILES  := $(patsubst build/%,$(BUILD_DIR)/%,$(LD_OBJS))

# The code image (tools/layout.py): the ROM below the first archive, then
# every overlay inflated.  The link rebuilds it from asm/ and the bins;
# tools/rom.py builds the ROM from it and the archives in assets/bankNN/.
IMAGE        = $(BUILD_DIR)/code.bin
ARCHIVE_SRCS = $(shell find assets -path 'assets/bank*/*' -type f 2>/dev/null)

# SHIFT=1: every movable module gets SHIFT_PAD bytes of zeros after its entry
# and at the start of its data (tools/ld_fix.py), which proves nothing
# depends on where things are.  Not sha1-checked.
SHIFT_PAD ?= 0x10
ifneq ($(SHIFT),0)
SHIFT_PAD_USED := $(SHIFT_PAD)
else
SHIFT_PAD_USED := 0
endif

# The Hudson LZSS encoder in C (tools/hudson_lzss.py falls back to Python).
LZSS_LIB  = build/tools/libhudson_lzss.so
# a mupen64plus video plugin that counts frames, for tools/emu_ram.py
VICOUNT   = build/tools/m64p_vicount.so
# and an input plugin that plays a script on controller 1
INPUTSCRIPT = build/tools/m64p_inputscript.so

### Targets

default: all

all: verify

# The tools, once per checkout: submodules, the venv, IDO.
setup:
	git submodule update --init --recursive
	test -d $(VENV) || python3 -m venv $(VENV)
	$(VENV)/bin/pip install -q -r requirements.txt
	$(TOOLS_DIR)/get_ido.sh
	$(MAKE) $(LZSS_LIB)

check: .baserom.$(VERSION).ok

stamp:
	@echo $(VERSION) > .version

# The archives become assets/bankNN/ (checked to rebuild) and the code
# image assets/code.bin, which splat then splits into asm/ and bins.
extract: check stamp $(LZSS_LIB)
	$(PYTHON) $(TOOLS_DIR)/assets.py extract $(VERSION)
	$(PYTHON) -m splat split $(CONFIG) | grep -v "^File split suggestions" || true
	$(PYTHON) $(TOOLS_DIR)/postsplit.py $(VERSION)
	$(PYTHON) $(TOOLS_DIR)/vermap.py --rename $(VERSION)

# eu's address map (tools/vermap.py): regenerate after the ROMs or the tool
# change; needs both ROMs.  `make extract` for eu renames with it.
vermap:
	$(PYTHON) $(TOOLS_DIR)/vermap.py

# the rebuilt code image, checked against the extracted one
image: $(IMAGE)
	@cmp $(IMAGE) assets/code.bin && echo "$(IMAGE): OK"

verify: $(TARGET).z64
ifeq ($(SHIFT),0)
	@echo "$$(cat $(BASENAME).$(VERSION).sha1)  $<" | sha1sum --check
else
	@$(PYTHON) $(TOOLS_DIR)/n64crc.py $< --check
	@echo "$<: shifted build (SHIFT_PAD=$(SHIFT_PAD)), not sha1-checked"
endif

clean:
	rm -rf asm assets build include/macro.inc
	rm -f *auto.txt $(BASENAME).*.ld .version

### Recipes

$(LZSS_LIB): $(TOOLS_DIR)/src/hudson_lzss.c
	@mkdir -p $(dir $@)
	$(CC) -O2 -shared -fPIC -o $@ $<

$(VICOUNT): $(TOOLS_DIR)/src/m64p_vicount.c
	@mkdir -p $(dir $@)
	$(CC) -O2 -shared -fPIC -o $@ $<

$(INPUTSCRIPT): $(TOOLS_DIR)/src/m64p_inputscript.c
	@mkdir -p $(dir $@)
	$(CC) -O2 -shared -fPIC -o $@ $<

# The shifted build run against the original in mupen64plus (the system's, or
# the unpacked Linux bundle in $M64P_DIR) with tools/inputs/menus.txt on
# controller 1: the same game state at every checkpoint frame.
SHIFT_FRAMES ?= 600,1800,3600,6000,12000,24000
shift-check: $(VICOUNT) $(INPUTSCRIPT)
	$(MAKE) VERSION=$(VERSION) SHIFT=0
	$(MAKE) VERSION=$(VERSION) SHIFT=1
	$(PYTHON) $(TOOLS_DIR)/shift_check.py $(VERSION) --frames $(SHIFT_FRAMES) $(SHIFT_CHECK_FLAGS)

# every compressed member decompresses and recompresses to the ROM's bytes
lzss-check: check $(LZSS_LIB)
	$(PYTHON) $(TOOLS_DIR)/lzss_check.py $(BASEROM)

.baserom.$(VERSION).ok: $(BASEROM)
	@echo "$$(cat $(BASENAME).$(VERSION).sha1)  $<" | sha1sum --check
	@touch $@

$(BUILD_DIR)/%.s.o: %.s
	@mkdir -p $(dir $@)
	$(AS) $(ASFLAGS) -o $@ $<

$(BUILD_DIR)/%.bin.o: %.bin
	@mkdir -p $(dir $@)
	$(LD) -r -b binary -o $@ $<

# splat's script, with the fixed ROM positions kept and (SHIFT=1) the
# modules padded (tools/ld_fix.py); it names build/..., and this version's
# objects live in $(BUILD_DIR).
$(BUILD_DIR)/$(BASENAME).ld: $(LD_SCRIPT) $(TOOLS_DIR)/ld_fix.py $(BUILD_DIR)/shift.stamp
	@mkdir -p $(dir $@)
	$(PYTHON) $(TOOLS_DIR)/ld_fix.py $(VERSION) $< $@.tmp --shift $(SHIFT_PAD_USED)
	sed 's|build/|$(BUILD_DIR)/|g' $@.tmp > $@ && rm $@.tmp

$(BUILD_DIR)/shift.stamp: FORCE
	@mkdir -p $(dir $@)
	@if [ "$$(cat $@ 2>/dev/null)" != "$(SHIFT_PAD_USED)" ]; then echo "$(SHIFT_PAD_USED)" > $@; fi

$(TARGET).elf: $(O_FILES) $(BUILD_DIR)/$(BASENAME).ld module_syms_auto.txt undefined_syms_auto.txt undefined_funcs_auto.txt
	$(LD) -T $(BUILD_DIR)/$(BASENAME).ld -T module_syms_auto.txt \
		-T undefined_syms_auto.txt -T undefined_funcs_auto.txt \
		-Map $(TARGET).map --no-check-sections --emit-relocs -o $@

$(IMAGE): $(TARGET).elf
	$(OBJCOPY) -O binary $< $@

$(TARGET).z64: $(IMAGE) $(ARCHIVE_SRCS) $(CONFIG) $(TOOLS_DIR)/rom.py $(TOOLS_DIR)/assets.py $(TOOLS_DIR)/hudson_lzss.py | $(LZSS_LIB)
	$(PYTHON) $(TOOLS_DIR)/rom.py $(VERSION) --image $(IMAGE) --elf $(TARGET).elf --out $@
	$(PYTHON) $(TOOLS_DIR)/n64crc.py $@

.SECONDARY:
.PHONY: FORCE all image check shift-check clean default extract lzss-check setup stamp verify vermap
SHELL = /bin/bash -e -o pipefail
