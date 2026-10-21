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

BUILD_DIR = build/$(VERSION)
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

# The archives (bankNN in the config) are built from assets/bankNN/ by
# tools/assets.py, everything else is splat's bin as extracted.
ARCHIVE_DIR  = $(BUILD_DIR)/archives
ARCHIVE_SRCS = $(shell find assets -path 'assets/bank*/*' -type f 2>/dev/null)

# The Hudson LZSS encoder in C (tools/hudson_lzss.py falls back to Python).
LZSS_LIB  = build/tools/libhudson_lzss.so

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

# splat cuts the ROM into the config's bins; the archives' bins are then
# replaced by their entries (tools/assets.py extract checks they rebuild).
extract: check stamp $(LZSS_LIB)
	$(PYTHON) -m splat split $(CONFIG)
	$(PYTHON) $(TOOLS_DIR)/assets.py extract $(VERSION)
	rm -f assets/bank[0-9A-F][0-9A-F].bin

# the archives rebuilt from assets/ (see ARCHIVE_DIR above)
archives: $(ARCHIVE_DIR)/.stamp

verify: $(TARGET).z64
	@echo "$$(cat $(BASENAME).$(VERSION).sha1)  $<" | sha1sum --check

clean:
	rm -rf asm assets build include/macro.inc
	rm -f *auto.txt $(BASENAME).*.ld .version

### Recipes

$(LZSS_LIB): $(TOOLS_DIR)/src/hudson_lzss.c
	@mkdir -p $(dir $@)
	$(CC) -O2 -shared -fPIC -o $@ $<

# every compressed member decompresses and recompresses to the ROM's bytes
lzss-check: check $(LZSS_LIB)
	$(PYTHON) $(TOOLS_DIR)/lzss_check.py $(BASEROM)

.baserom.$(VERSION).ok: $(BASEROM)
	@echo "$$(cat $(BASENAME).$(VERSION).sha1)  $<" | sha1sum --check
	@touch $@

$(BUILD_DIR)/%.s.o: %.s
	@mkdir -p $(dir $@)
	$(AS) $(ASFLAGS) -o $@ $<

$(ARCHIVE_DIR)/.stamp: $(ARCHIVE_SRCS) $(TOOLS_DIR)/assets.py $(TOOLS_DIR)/hudson_lzss.py $(TOOLS_DIR)/layout.py | $(LZSS_LIB)
	$(PYTHON) $(TOOLS_DIR)/assets.py build $(VERSION) --out $(ARCHIVE_DIR)
	@touch $@

$(ARCHIVE_DIR)/%.bin: $(ARCHIVE_DIR)/.stamp ;

$(BUILD_DIR)/assets/bank%.bin.o: $(ARCHIVE_DIR)/bank%.bin
	@mkdir -p $(dir $@)
	$(LD) -r -b binary -o $@ $<

$(BUILD_DIR)/%.bin.o: %.bin
	@mkdir -p $(dir $@)
	$(LD) -r -b binary -o $@ $<

# The script names build/...; this version's objects live in $(BUILD_DIR).
$(BUILD_DIR)/$(BASENAME).ld: $(LD_SCRIPT)
	@mkdir -p $(dir $@)
	sed 's|build/|$(BUILD_DIR)/|g' $< > $@

$(TARGET).elf: $(O_FILES) $(BUILD_DIR)/$(BASENAME).ld
	$(LD) -T $(BUILD_DIR)/$(BASENAME).ld -Map $(TARGET).map --no-check-sections -o $@

$(TARGET).z64: $(TARGET).elf
	$(OBJCOPY) -O binary $< $@
	$(PYTHON) $(TOOLS_DIR)/n64crc.py $@

.SECONDARY:
.PHONY: all archives check clean default extract lzss-check setup stamp verify
SHELL = /bin/bash -e -o pipefail
