import hashlib
import os, sys, elftools, json, yaml, struct, subprocess, shutil, glob, re
import elftools.elf.elffile
from elftools.elf.sections import SymbolTableSection

VERSION = "us"
CROSS = "mipsel-linux-gnu-"
AS = f"{CROSS}as"
LD = f"{CROSS}ld"
CPP = f"{CROSS}cpp"
OBJCOPY = f"{CROSS}objcopy"
CC = "./bin/cc1-27"
AS_FLAGS        = "-Iinclude -march=r3000 -mtune=r3000 -no-pad-sections -O1 -G0"
CC_FLAGS        = "-mcpu=3000 -quiet -G0 -w -O2 -funsigned-char -fpeephole -ffunction-cse -fpcc-struct-return -fcommon -fverbose-asm -fgnu-linker -mgas -msoft-float"
CPP_FLAGS       = "-Iinclude -undef -Wall -lang-c -fno-builtin -gstabs -Dmips -D__GNUC__=2 -D__OPTIMIZE__ -D__mips__ -D__mips -Dpsx -D__psx__ -D__psx -D_PSYQ -D__EXTENSIONS__ -D_MIPSEL -D_LANGUAGE_C -DLANGUAGE_C -DHACKS"

ASM_DIR         = "asm"
SRC_DIR         = "src"
ASSETS_DIR      = "assets"
INCLUDE_DIR     = "include"
BUILD_DIR       = "build"
CONFIG_DIR      = "config"
TOOLS_DIR       = "tools"

ASPATCH = "$HOME/go/bin/aspatch"
PYPATCHASM = "tools/patchasm.py"

def generate_rock_neo_syms_txt():
    rock_neo_elf = f"{BUILD_DIR}/rock_neo.elf.unstripped"
    rock_neo_syms_txt = f"{BUILD_DIR}/generated.rock_neo.syms.txt"

    elf_file = open(rock_neo_elf, "rb")
    elf = elftools.elf.elffile.ELFFile(elf_file)
    syms = elf.get_section_by_name(".symtab")
    with open(rock_neo_syms_txt, "w") as f:
        for sym in syms.iter_symbols():
            if sym.entry.st_value >= 0x80010000 and sym.entry.st_value < 0x80200000 and " " not in sym.name and sym.name != "":
                f.write(f"{sym.name} = 0x{sym.entry.st_value:08x};\n")
        f.write("""
SUPPORT_STG_LOAD_ADDRESS = 0x801F6000;
SUPPORT_EBD_LOAD_ADDRESS = 0x801F2000;
SUPPORT_PROGBIN_LOAD_ADDRESS = 0x801D8000;
STAGE_STG_LOAD_ADDRESS = 0x80194000;
STAGE_EBD_LOAD_ADDRESS2 = 0x80190000;
STAGE_EBD_LOAD_ADDRESS1 = 0x8016C000;
STAGE_MDT_LOAD_ADDRESS = 0x80164000;
STAGE_IDX_LOAD_ADDRESS = 0x8015C000;
MSG_LOAD_ADDRESS = 0x80153000;
STAGE_HED_LOAD_ADDRESS = 0x8013A000;
STAGE_PROGBIN_LOAD_ADDRESS = 0x80100000;
SHL_PROGBIN_LOAD_ADDRESS = 0x800D8800;
""")

last_hash = "" if not os.path.exists(f"{BUILD_DIR}/rock_neo_hash.txt") else open(f"{BUILD_DIR}/rock_neo_hash.txt").read().strip()

def update_hash():
    global last_hash
    with open(f"{BUILD_DIR}/rock_neo_hash.txt", "w") as f:
        f.write(hashlib.md5(open(f"{BUILD_DIR}/rock_neo.elf", "rb").read()).hexdigest())
    last_hash = open(f"{BUILD_DIR}/rock_neo_hash.txt").read().strip()

def main():
    if last_hash != hashlib.md5(open(f"{BUILD_DIR}/rock_neo.elf", "rb").read()).hexdigest():
        update_hash()
        generate_rock_neo_syms_txt()

if __name__ == "__main__":
    main()
