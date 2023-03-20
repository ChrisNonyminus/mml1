# patches MIPS assembly output from GCC to fix shenanigans caused by the assembler

import sys
import re

def patch_asm(asm):
    re_li_pattern = r"\tli\s+(\$\w+),\s*(0x[0-9a-fA-F]+)"
    # Ensure that any li instance where the \2 value is less than 0xFFFF is addiu instead
    # This is because the assembler will automatically convert these lis to ori for whatever reason
    for line in asm.splitlines():
        match = re.match(re_li_pattern, line)
        if match:
            reg, val = match.groups()
            if int(val, 16) < 0xFFFF:
                asm = asm.replace(line, f"\taddiu {reg}, $0, {val}")

    return asm

def main():
    asm = sys.stdin.read()
    print(patch_asm(asm))
    f = open("build/test.s", "w")
    f.write(patch_asm(asm))

if __name__ == "__main__":
    main()
