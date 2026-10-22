BASENAME  = bm64
VERSION  := us

VERSIONS  := us eu jp
ifeq ($(filter $(VERSION),$(VERSIONS)),)
$(error Unknown VERSION '$(VERSION)'; expected one of $(VERSIONS))
endif

# asm/ and assets/ hold one version at a time; leftovers from another
# VERSION would link in silently and only show as a sha1 mismatch.
ifneq ($(filter-out clean setup libultra-ref build/libultra_bm64/%,$(or $(MAKECMDGOALS),all)),)
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

# C (src/): IDO 5.3 through asm-processor, which assembles the GLOBAL_ASM
# functions in place.  A text object is C when src/ has its file
# (tools/layout.py makes it a `c` subsegment).  docs/DECOMPILING.md has the
# loop and the evidence for the flags.
IDO       = $(TOOLS_DIR)/ido/5.3/cc
ASM_PROC  = $(PYTHON) $(TOOLS_DIR)/asm-processor/build.py
VERSION_DEFINE := VERSION_$(shell echo $(VERSION) | tr a-z A-Z)
INCLUDE_CFLAGS := -I include -I include/PR -I src
CFLAGS    = -G 0 -Xfullwarn -Xcpluscomm -nostdinc -non_shared -Wab,-r4300_mul \
            -D_LANGUAGE_C -D_FINALROM -D$(VERSION_DEFINE) -woff 649,838,712,807 \
            $(INCLUDE_CFLAGS)
# Hudson's game code: -mips1 (a nop fills every load delay slot it can't
# schedule, and no branch-likely) at -O2.  Overridden per file below.
OPT_FLAGS = -O2
MIPSISET  = -mips1 -32
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
	$(PYTHON) $(TOOLS_DIR)/split.py $(VERSION) | grep -v "^File split suggestions" || true
	$(PYTHON) $(TOOLS_DIR)/postsplit.py $(VERSION)
	$(PYTHON) $(TOOLS_DIR)/vermap.py --rename $(VERSION)

# eu's and jp's address maps (tools/vermap.py): regenerate after the ROMs or the tool
# change; needs us's ROM and theirs.  `make extract` for eu and jp renames with them.
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
SHIFT_FRAMES ?= 300,900,1800,3600,6000,10300,12000,18000,24000
# and with tools/inputs/battle.<v>.txt: battle mode, one human and three CPU
# players, several matches.  --expect makes it fail unless the arena
# (ovl_17_01) and the result screen (ovl_0B_07) were loaded at checkpoints.
shift-check: shift-build $(VICOUNT) $(INPUTSCRIPT)
	$(PYTHON) $(TOOLS_DIR)/shift_check.py $(VERSION) --frames $(SHIFT_FRAMES) $(SHIFT_CHECK_FLAGS)
	$(PYTHON) $(TOOLS_DIR)/shift_check.py $(VERSION) \
		--input tools/inputs/battle.$(VERSION).txt --expect ovl_17_01,ovl_0B_07 $(SHIFT_CHECK_FLAGS)

# only the battle run
shift-check-battle: shift-build $(VICOUNT) $(INPUTSCRIPT)
	$(PYTHON) $(TOOLS_DIR)/shift_check.py $(VERSION) \
		--input tools/inputs/battle.$(VERSION).txt --expect ovl_17_01,ovl_0B_07 $(SHIFT_CHECK_FLAGS)

shift-build:
	$(MAKE) VERSION=$(VERSION) SHIFT=0
	$(MAKE) VERSION=$(VERSION) SHIFT=1

# every compressed member decompresses and recompresses to the ROM's bytes
lzss-check: check $(LZSS_LIB)
	$(PYTHON) $(TOOLS_DIR)/lzss_check.py $(BASEROM)

.baserom.$(VERSION).ok: $(BASEROM)
	@echo "$$(cat $(BASENAME).$(VERSION).sha1)  $<" | sha1sum --check
	@touch $@

$(BUILD_DIR)/%.s.o: %.s
	@mkdir -p $(dir $@)
	$(AS) $(ASFLAGS) -o $@ $<

### Per-file compiler flags (paths under src/; the same in every version)

# main_code's entry (func_80225800): -g (every value goes through the stack,
# and the return is branched to).
G_C_FILES  := main_code_entry.c
# -O3: IDO inlines a file's small functions into their callers there (40FB0:
# func_80226860 holds func_80226818's and func_802267E0's bodies), which
# -O2 never does.  asm-processor can't do -O3 either: these are all C.
O3_C_FILES := 40FB0.c 412F0.c 41FD0.c 4DE50.c 4E030.c 52270.c 530C0.c 53D70.c 995C0.c 9BFD0.c \
              overlays/ovl_0A_04/137330.c \
              overlays/ovl_17_01/2A7080.c overlays/ovl_17_06/2B1100.c overlays/ovl_17_08/2B60C0.c
$(foreach f,$(G_C_FILES),$(BUILD_DIR)/src/$(f).o): OPT_FLAGS := -g
$(foreach f,$(O3_C_FILES),$(BUILD_DIR)/src/$(f).o): OPT_FLAGS := -O3

# libultra (src/libultra/, docs/LIBULTRA.md): ultralib's headers
# (include/ultralib) and its flags for 2.0I's libultra_rom: -mips2, -O1,
# and -O3 for libaudio, libc and gu.  Its handwritten .s files are
# assembled by IDO too (it schedules them), -mips3 as in the SDK.
LIB_CPPFLAGS = -D_MIPS_SZLONG=32 -DF3DEX_GBI -DBUILD_VERSION=VERSION_I \
               '-DBUILD_VERSION_STRING="2.0I"' -non_shared -DNDEBUG -D_FINALROM -D$(VERSION_DEFINE)
LIB_INCLUDE  = -I include/ultralib -I include/ultralib/compiler/ido -I include/ultralib/PR -I src/libultra
LIB_CFLAGS   = -Wab,-r4300_mul -G 0 -nostdinc -Xcpluscomm -fullwarn -woff 516,649,838,712 \
               -D_LANGUAGE_C $(LIB_CPPFLAGS) $(LIB_INCLUDE)
LIB_ASFLAGS  = -Wab,-r4300_mul -G 0 -nostdinc -woff 516,649,838,712 $(LIB_CPPFLAGS) $(LIB_INCLUDE)
LIB_O3_DIRS  = audio libc gu
$(BUILD_DIR)/src/libultra/%.o: CFLAGS = $(LIB_CFLAGS)
$(BUILD_DIR)/src/libultra/%.o: INCLUDE_CFLAGS = $(LIB_INCLUDE)
$(BUILD_DIR)/src/libultra/%.o: MIPSISET := -mips2 -32
$(BUILD_DIR)/src/libultra/%.o: OPT_FLAGS := -O1
$(foreach d,$(LIB_O3_DIRS),$(BUILD_DIR)/src/libultra/$(d)/%.o): OPT_FLAGS := -O3

# A library .s is a `hasm` subsegment (tools/layout.py), which the link
# script names asm/libultra/...; it is built from src/libultra/ instead
# of splat's disassembly.  IDO's assembler leaves local undefined symbols
# after the globals, which GNU ld rejects: rewriting the object with strip
# (as ultralib does for a modern ld) and dropping .mdebug fixes that.  And
# ld won't mix a -mips3 object with the -mips2 ones, so it's relabelled
# mips2 (the code is what it is).
$(BUILD_DIR)/asm/libultra/%.s.o: src/libultra/%.s
	@mkdir -p $(dir $@)
	$(IDO) -c $(LIB_ASFLAGS) -O1 -mips3 -32 -o $@ $<
	$(CROSS)strip $@ -N __rewrite_the_symbol_table__
	$(OBJCOPY) --remove-section .mdebug $@
	$(PYTHON) $(TOOLS_DIR)/elf_mips2.py $@

# The library's sources built on their own, as reference objects for
# tools/libmatch.py and gen_symbols.py (docs/LIBULTRA.md, "Workflow"): they
# are a libultra revision like ultralib's builds.  Needs no extract.
LIB_SRCS := $(shell find src/libultra -name '*.c' -o -name '*.s' 2>/dev/null)
LIB_REF  := $(patsubst src/libultra/%,build/libultra_bm64/src/%.o,$(basename $(LIB_SRCS)))
libultra-ref: $(LIB_REF)
build/libultra_bm64/src/%.o: src/libultra/%.c
	@mkdir -p $(dir $@)
	$(IDO) -c $(LIB_CFLAGS) $(if $(filter $(addsuffix /%,$(LIB_O3_DIRS)),$*),-O3,-O1) -mips2 -32 -o $@ $<
build/libultra_bm64/src/%.o: src/libultra/%.s
	@mkdir -p $(dir $@)
	$(IDO) -c $(LIB_ASFLAGS) -O1 -mips3 -32 -o $@ $<

# IDO can't write dependency files: the headers come from the host's cpp
# (.d), the .s files the GLOBAL_ASM lines pull in from asm-processor
# (.asmproc.d; re-extracting rewrites them).  Both give every prerequisite
# an empty rule too (as -MP does).
define write_deps
	@cpp -MM -MP -MT $@ $(INCLUDE_CFLAGS) -D_LANGUAGE_C -D_FINALROM -D$(VERSION_DEFINE) $< > $(@:.o=.d) 2>/dev/null || echo "$@: $<" > $(@:.o=.d)
endef

# PERMUTER=1 (tools/permute.sh) shows the plain IDO command.
# A file with GLOBAL_ASM left goes through tools/version_ifs.py (which
# decides the VERSION_* #ifs, so asm-processor only sees the GLOBAL_ASM
# lines this version has a .s for) and then asm-processor (which can't do
# -g with -mips1: such a file has to be all C); the rest IDO compiles as
# they are.  PERMUTER=1 compiles the file as is (the permuter's own
# preprocessing handles #if).
ifndef PERMUTER
$(BUILD_DIR)/%.c.o: %.c
	@mkdir -p $(dir $@)
	@rm -f $(@:.o=.asmproc.d)
	@if grep -q '^ *#pragma  *GLOBAL_ASM' $<; then \
		echo "asm-processor $<"; \
		$(PYTHON) $(TOOLS_DIR)/version_ifs.py $(VERSION_DEFINE) $< -o $(@:.o=.vi.c); \
		$(ASM_PROC) $(IDO) -- $(AS) $(ASFLAGS) -- -c $(CFLAGS) $(OPT_FLAGS) $(MIPSISET) -o $@ $(@:.o=.vi.c); \
	else \
		echo "$(IDO) -c $(CFLAGS) $(OPT_FLAGS) $(MIPSISET) -o $@ $<"; \
		$(IDO) -c $(CFLAGS) $(OPT_FLAGS) $(MIPSISET) -o $@ $<; \
	fi
	$(write_deps)
else
$(BUILD_DIR)/%.c.o: %.c
	$(IDO) -c $(CFLAGS) $(OPT_FLAGS) $(MIPSISET) -o $@ $<
endif

-include $(foreach o,$(filter %.c.o,$(O_FILES)),$(o:.o=.d) $(o:.o=.asmproc.d))

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

$(TARGET).z64: $(IMAGE) $(ARCHIVE_SRCS) $(CONFIG) $(TOOLS_DIR)/rom.py $(TOOLS_DIR)/assets.py $(wildcard $(TOOLS_DIR)/assetlib/*.py) $(TOOLS_DIR)/hudson_lzss.py | $(LZSS_LIB)
	$(PYTHON) $(TOOLS_DIR)/rom.py $(VERSION) --image $(IMAGE) --elf $(TARGET).elf --out $@
	$(PYTHON) $(TOOLS_DIR)/n64crc.py $@

.SECONDARY:
.PHONY: FORCE libultra-ref all image check shift-check shift-check-battle shift-build clean default extract lzss-check setup stamp verify vermap
SHELL = /bin/bash -e -o pipefail
