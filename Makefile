.SECONDEXPANSION:
.SECONDARY:

SHELL := /bin/bash -e -o pipefail
VERSION ?= us
SPLATYAML_FOLDER := config

# EXEs
MAIN := main
ROCK_NEO := rock_neo

CROSS           := mipsel-linux-gnu-
AS              := $(CROSS)as
CC              := ./bin/cc1-27
LD              := $(CROSS)ld
CPP				:= $(CROSS)cpp
OBJCOPY         := $(CROSS)objcopy
AS_FLAGS        += -Iinclude -march=r3000 -mtune=r3000 -no-pad-sections -O1 -G0
CC_FLAGS        += -mcpu=3000 -quiet -G0 -w -O2 -funsigned-char -fpeephole -ffunction-cse -fpcc-struct-return -fcommon -fverbose-asm -fgnu-linker -mgas -msoft-float
CPP_FLAGS       += -Iinclude -undef -Wall -lang-c -fno-builtin -gstabs
CPP_FLAGS       += -Dmips -D__GNUC__=2 -D__OPTIMIZE__ -D__mips__ -D__mips -Dpsx -D__psx__ -D__psx -D_PSYQ -D__EXTENSIONS__ -D_MIPSEL -D_LANGUAGE_C -DLANGUAGE_C -DHACKS


ASM_DIR         := asm
SRC_DIR         := src
ASSETS_DIR      := assets
INCLUDE_DIR     := include
BUILD_DIR       := build
DISK_DIR        := $(BUILD_DIR)/disk
CONFIG_DIR      := config
TOOLS_DIR       := tools


PYTHON          := python3
SPLAT_DIR       := $(TOOLS_DIR)/splat
SPLAT_APP       := $(SPLAT_DIR)/split.py
SPLAT           := $(PYTHON) $(SPLAT_APP)
ASMDIFFER_DIR   := $(TOOLS_DIR)/asm-differ
ASMDIFFER_APP   := $(ASMDIFFER_DIR)/diff.py
GO				:= $(HOME)/go/bin/go
GOPATH			:= $(HOME)/go
ASPATCH			:= $(GOPATH)/bin/aspatch
SOTNDISK		:= $(GOPATH)/bin/sotn-disk
PYPATCHASM := $(TOOLS_DIR)/patchasm.py
DUMPSXISO := dumpsxiso
MKPSXISO := mkpsxiso
REGEXR := python3 $(TOOLS_DIR)/regexr.py

DIFF := diff -u --color=never
XXD := xxd -u -g 4


define list_src_files
	$(foreach dir,$(ASM_DIR)/$(1),$(wildcard $(dir)/**.s))
	$(foreach dir,$(ASM_DIR)/$(1)/data,$(wildcard $(dir)/**.s))
	$(foreach dir,$(ASM_DIR)/$(1)/psxsdk,$(wildcard $(dir)/**.s))
	$(foreach dir,$(ASM_DIR)/$(1)/data/psxsdk,$(wildcard $(dir)/**.s))
	$(foreach dir,$(SRC_DIR)/$(1),$(wildcard $(dir)/**.c))
	$(foreach dir,$(SRC_DIR)/$(1)/psxsdk,$(wildcard $(dir)/**.c))
	$(foreach dir,$(ASSETS_DIR)/$(1),$(wildcard $(dir)/**.bin))
endef

define list_o_files
	$(foreach file,$(call list_src_files,$(1)),$(BUILD_DIR)/$(file).o)
endef

define link
	$(LD) -o $(2) \
		-Map $(BUILD_DIR)/$(1).map \
		-T $(1).ld \
		-T $(CONFIG_DIR)/undefined_syms_auto.$(VERSION).$(1).txt \
		-T $(CONFIG_DIR)/undefined_funcs_auto.$(VERSION).$(1).txt \
		--no-check-sections \
		-nostdlib \
		-s

endef

define link_overlay_chunk
	$(LD) -o $(2) \
		-Map $(BUILD_DIR)/$(1).map \
		-T $(1).ld \
		-T $(CONFIG_DIR)/syms.$(VERSION).rock_neo.txt \
		-T $(CONFIG_DIR)/overlay/$(3)/undefined_syms_auto.$(VERSION).$(1).txt \
		-T $(CONFIG_DIR)/overlay/$(3)/undefined_funcs_auto.$(VERSION).$(1).txt \
		--no-check-sections \
		-nostdlib \
		-s

endef

define copy_syms_txt

	cpp $(1) > $(CONFIG_DIR)/generated.syms.$(VERSION).$(patsubst $(CONFIG_DIR)/syms.$(VERSION).%.txt,%,$(1)).txt

endef

define split_yaml
	$(SPLAT) $(1) > logs/$(notdir $(1)).log

endef

ROCK_NEO_YAML := $(SPLATYAML_FOLDER)/splat.$(VERSION).rock_neo.yaml
ROCK_NEO_SYMBOL_LIST := $(CONFIG_DIR)/syms.$(VERSION).rock_neo.txt
ROCK_NEO_TARGET := $(BUILD_DIR)/rock_neo.exe

ALL_BIN_YAML_SUBDIRS := $(shell find $(SPLATYAML_FOLDER)/overlay -type d -name "*")
# remove "." and ".." from the list
ALL_BIN_YAML_SUBDIRS := $(filter-out . ..,$(ALL_BIN_YAML_SUBDIRS))
ALL_BIN_YAML_FILES := $(foreach dir,$(ALL_BIN_YAML_SUBDIRS),$(wildcard $(dir)/*.yaml))


default: all
all: build check
build: logs $(ALL_BINARIES)

logs:
	@mkdir -p logs/

clean:
	rm -rf $(BUILD_DIR) asm/ assets/ logs/

define get_overlay_parent_file
$(shell echo $(1) | sed -e 's/config\/overlay\/\(.*\)\/.*\.yaml/\1/')
endef

define get_overlay_name
$(shell echo $(1) | sed -e 's/config\/overlay\/.*\/\(.*\)\.yaml/\1/')
endef



define generate_symbol_list
	@$(shell if [ ! -f "$(CONFIG_DIR)/overlay/$(call get_overlay_parent_file,$(1))/syms.$(VERSION).$(call get_overlay_name,$(1)).txt" ]; then touch "$(CONFIG_DIR)/overlay/$(call get_overlay_parent_file,$(1))/syms.$(VERSION).$(call get_overlay_name,$(1)).txt"; fi)
	@$(shell cat $(ROCK_NEO_SYMBOL_LIST) "$(CONFIG_DIR)/overlay/$(call get_overlay_parent_file,$(1))/syms.$(VERSION).$(call get_overlay_name,$(1)).txt" > "$(CONFIG_DIR)/overlay/$(call get_overlay_parent_file,$(1))/generated.syms.$(VERSION).$(call get_overlay_name,$(1)).txt")
endef
	

dosplit_%:
	$(call split_yaml,config/splat.$(VERSION).$(patsubst dosplit_%,%,$@).yaml)

split_all:
	@mkdir -p logs/
	$(call split_yaml,$(ROCK_NEO_YAML))
	$(foreach file,$(ALL_BIN_YAML_FILES),$(call generate_symbol_list,$(file)))
	$(foreach file,$(ALL_BIN_YAML_FILES),$(call split_yaml,$(file)))

# make a sha1 file for each binary, and edit it so that the path in the sha1 points to the binary in the build dir
define make_sha1_file

	@$(shell sha1sum $(1) > hash/$(VERSION)/$(notdir $(1)).sha1)
	@$(shell cat hash/$(VERSION)/$(notdir $(1)).sha1 | python3 tools/regexr.py "disks/$(VERSION)/CDDATA/DAT/(.*).BIN" "$(BUILD_DIR)/$(notdir $(1))" > hash/$(VERSION)/$(notdir $(1)).sha1.tmp)
	@$(shell mv hash/$(VERSION)/$(notdir $(1)).sha1.tmp hash/$(VERSION)/$(notdir $(1)).sha1)
	
endef

make_sha1_files:
	@mkdir -p hash/$(VERSION)
	$(foreach file,$(wildcard disks/$(VERSION)/CDDATA/DAT/*.BIN),$(call make_sha1_file,$(file)))

define get_dirname_from_file
	$(dir $(1))
endef

# make build dirs for module
# also, if config/syms.$(VERSION).$(1).txt doesn't exist, make it
%_build_dirs:
	$(foreach file,$(call list_src_files,$*),$(shell mkdir -p $(BUILD_DIR)/$(dir $(file))))
	$(shell if [ ! -f $(CONFIG_DIR)/syms.$(VERSION).$*.txt ]; then touch $(CONFIG_DIR)/syms.$(VERSION).$*.txt; fi)

$(BUILD_DIR)/%.bin: $(BUILD_DIR)/%.elf
	$(OBJCOPY) -O binary $< $@

$(BUILD_DIR)/%.elf: %_build_dirs $$(call list_o_files,$$*)
	$(call link,$*,$@)

$(BUILD_DIR)/$(MAIN).exe: $(BUILD_DIR)/$(MAIN).elf
	$(OBJCOPY) -O binary $< $@

$(BUILD_DIR)/$(MAIN).elf: $(call list_o_files,$(MAIN))
	$(call link,$(MAIN),$@)

$(BUILD_DIR)/main.bin: main_build_dirs $(BUILD_DIR)/main.exe
	rm -f $(BUILD_DIR)/main.bin

$(BUILD_DIR)/$(ROCK_NEO).exe: $(BUILD_DIR)/$(ROCK_NEO).elf
	$(OBJCOPY) -O binary $< $@

$(BUILD_DIR)/$(ROCK_NEO).elf: $(call list_o_files,$(ROCK_NEO))
	$(call link,$(ROCK_NEO),$@)

$(BUILD_DIR)/rock_neo.bin: rock_neo_build_dirs $(BUILD_DIR)/rock_neo.exe
	rm -f $(BUILD_DIR)/rock_neo.bin

UC = $(shell echo '$1' | tr '[:lower:]' '[:upper:]')

extract_disk: $(SOTNDISK)
	$(DUMPSXISO) -x disks/$(VERSION) -s disks/mml1.$(VERSION).xml disks/mml1.$(VERSION).track1.bin 
disk: build $(SOTNDISK)
	mkdir -p $(DISK_DIR)
	cp -r disks/$(VERSION)/* $(DISK_DIR)
	cp $(BUILD_DIR)/$(MAIN).exe $(DISK_DIR)/SLUS_006.03
	cp $(BUILD_DIR)/$(ROCK_NEO).exe $(DISK_DIR)/ROCK_NEO.EXE
	$(foreach file,$(wildcard $(BUILD_DIR)/**.bin),cp $(file) $(DISK_DIR)/CDDATA/DAT/$(call UC,$(notdir $(file)));)
	$(MKPSXISO) -y mml1.$(VERSION).xml

$(GO):
	curl -L -o go1.19.7.linux-amd64.tar.gz https://go.dev/dl/go1.19.7.linux-amd64.tar.gz
	tar -C $(HOME) -xzf go1.19.7.linux-amd64.tar.gz
	rm go1.19.7.linux-amd64.tar.gz
$(ASPATCH): $(GO)
	$(GO) install github.com/xeeynamo/sotn-decomp/tools/aspatch@latest
$(SOTNDISK): $(GO)
	$(GO) install github.com/xeeynamo/sotn-decomp/tools/sotn-disk@latest

tools: $(ASPATCH) $(SOTNDISK)
format:
	clang-format -i $$(find $(SRC_DIR)/ -type f -name "*.c")
	clang-format -i $$(find $(INCLUDE_DIR)/ -type f -name "*.h")

diff_%:
	$(XXD) $(BUILD_DIR)/$*.bin > $(BUILD_DIR)/$*.bin.xxd
	$(XXD) disks/$(VERSION)/CDDATA/DAT/$(call UC,$*).BIN > $(BUILD_DIR)/$*.bin.good.xxd
	$(DIFF) $(BUILD_DIR)/$*.bin.xxd $(BUILD_DIR)/$*.bin.good.xxd > $(BUILD_DIR)/$*.diff

diff_rock_neo:
	$(XXD) $(BUILD_DIR)/rock_neo.exe > $(BUILD_DIR)/rock_neo.bin.xxd
	$(XXD) disks/$(VERSION)/ROCK_NEO.EXE > $(BUILD_DIR)/rock_neo.bin.good.xxd
	$(DIFF) $(BUILD_DIR)/rock_neo.bin.xxd $(BUILD_DIR)/rock_neo.bin.good.xxd > $(BUILD_DIR)/rock_neo.diff

diff_main:
	$(XXD) $(BUILD_DIR)/main.exe > $(BUILD_DIR)/main.bin.xxd
	$(XXD) disks/$(VERSION)/SLUS_006.03 > $(BUILD_DIR)/main.bin.good.xxd
	$(DIFF) $(BUILD_DIR)/main.bin.xxd $(BUILD_DIR)/main.bin.good.xxd > $(BUILD_DIR)/main.diff

$(BUILD_DIR)/%.s.o: %.s
	$(AS) $(AS_FLAGS) -o $@ $<
$(BUILD_DIR)/%.c.o: %.c $(ASPATCH)
	$(CPP) $(CPP_FLAGS) $< | $(CC) $(CC_FLAGS) | $(ASPATCH) | $(PYTHON) $(PYPATCHASM) | $(AS) $(AS_FLAGS) -o $@
$(BUILD_DIR)/$(ASSETS_DIR)/%.bin.o: $(ASSETS_DIR)/%.bin
	$(LD) -r -b binary -o $@ $<

CHECK_FOLDER := hash/$(VERSION)
ALL_HASHES := $(wildcard $(CHECK_FOLDER)/**.sha1)

# for each sha1 file in hash/$(VERSION), whose filename is in the ALL_MODULE_NAMES list, check it
check:
	$(foreach module,$(ALL_MODULE_NAMES),$(shell if [ -f hash/$(VERSION)/$(module).bin.sha1 ]; then sha1sum -c --quiet hash/$(VERSION)/$(module).bin.sha1; fi))
	@echo "OK"


.PHONY: all, build, clean, disk, extract_disk, split_all, make_sha1_files, check, tools, default, debug_log_%, dosplit_%, make_sha1_file, %_build_dirs, %_bin
.PHONY: logs, diff_%, diff_main, diff_rock_neo
