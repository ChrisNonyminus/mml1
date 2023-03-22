#!/usr/bin/python3

import json
import os
import sys
from typing import Optional
from pathlib import Path
import spimdisasm

sys.path.append(f"{os.getcwd()}/tools/splat")
sys.path.append(f"{os.getcwd()}/tools/splat_ext")
from util import options, log, symbols
from segtypes.common.header import CommonSegHeader

class PSXSegDashchunkheader(CommonSegHeader):
    def should_split(self):
        return self.extract and options.opts.is_mode_active("code")

    def new_get_line(self, typ, data, comment):
        dword = None
        if len(data) == 4:
            dword = int.from_bytes(data, "big")
            print(dword)
        if typ == "ascii":
            text = data.decode("ASCII").strip()
            text = text.replace("\x00", "\\0")  # escape NUL chars
            dstr = '"' + text + '"'
        elif typ == "symbol" and dword in self.symbols:
            typ = "word"
            dstr = self.symbols[dword]
        elif typ == "symbol" and dword not in self.symbols:
            typ = "word"
            dstr = "0x" + data.hex().upper()
        else:  # .word, .byte
            dstr = "0x" + data.hex().upper()

        dstr = dstr.ljust(20 - len(typ))

        return f".{typ} {dstr} /* {comment} */"

    def out_path(self) -> Path:
        return options.opts.asm_path / self.dir / f"{self.name}.s"

    def parse_header(self, rom_bytes):
        header_lines = []
        header_lines.append(".section .data\n")

        header_lines.append(
            self.new_get_line("word", rom_bytes[0x00:0x04][::-1], "Type?")
        )

        header_lines.append(
            self.new_get_line("word", rom_bytes[0x04:0x08][::-1], "Chunk Size")
        )
        header_lines.append(self.new_get_line("word", rom_bytes[0x8:0xC][::-1], "???"))

        header_lines.append(
            self.new_get_line("symbol", rom_bytes[0xC:0x10][::-1], "Load Address if type 0")
        )
        for i in range (0x10, 0x40, 4):
            header_lines.append(
                self.new_get_line("word", rom_bytes[i:i+4][::-1], "???")
            )
        header_lines.append(
            self.new_get_line("ascii", rom_bytes[0x40:0x60], "Original filename")
        )

        return header_lines


    def split(self, rom_bytes):
        rom_bytes = rom_bytes[self.rom_start : self.rom_end]
        self.symbols = {
            0x801F6000: "SUPPORT_STG_LOAD_ADDRESS",
            0x801F2000: "SUPPORT_EBD_LOAD_ADDRESS",
            0x801D8000: "SUPPORT_PROGBIN_LOAD_ADDRESS",
            0x80194000: "STAGE_STG_LOAD_ADDRESS",
            0x80190000: "STAGE_EBD_LOAD_ADDRESS2",
            0x8016C000: "STAGE_EBD_LOAD_ADDRESS1",
            0x80164000: "STAGE_MDT_LOAD_ADDRESS",
            0x8015C000: "STAGE_IDX_LOAD_ADDRESS",
            0x80153000: "MSG_LOAD_ADDRESS",
            0x8013A000: "STAGE_HED_LOAD_ADDRESS",
            0x80100000: "STAGE_PROGBIN_LOAD_ADDRESS",
            0x800D8800: "SHL_PROGBIN_LOAD_ADDRESS",
        }

        header_lines = self.parse_header(rom_bytes)

        src_path = self.out_path()
        src_path.parent.mkdir(parents=True, exist_ok=True)
        with open(src_path, "w", newline="\n") as f:
            f.write("\n".join(header_lines))
        self.log(f"Wrote {self.name} to {src_path}")

    @staticmethod
    def get_default_name(addr):
        return "dashchunkheader"
