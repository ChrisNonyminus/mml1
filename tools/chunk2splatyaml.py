# The files are raw binary archive files, with specific chunks representing containing archived files, with the first chunk always at the start of the file with no header for the overall archive, just the chunks. Here's a rundown of the format of each chunk:
# ```
# CHUNK HEADER (offsets are relative to chunk's location)
# 0x0: ??? Type? (It seems that if 0, this is a code overlay loaded into executable game memory)
# 0x4: Size of chunk
# 0x8: ???
# 0xC: Load address if type 0
# 0x10-0x20: ???
# 0x20-0x40: ???
# 0x40-0x800: Chunk filename, as a null terminated string
# 0x800-(0x800+chunk size): file contents
# Chunk size, aligned up to 0x800: next chunk, starting with the header
# ```

# This python script will scan a given folder for files that follow this format, and create yamls for splat, placed in the "config" folder and named splatconfig.us.{overlay file name}.yaml. Also creates a json for buildoverlay.py that lists the offsets of each chunk header in the file, and the name of the chunk. This is used by buildoverlay.py to build the overlay file.

import json
import os
import struct
import yaml


def align_up(val, align):
    if (val % align) == 0:
        return val
    return (val + align - 1) & ~(align - 1)

def get_next_offset(file, offset, chunk_size, unk, chunk_type):
    if ("ST05_00E.BIN" in file) and offset == 0x89800:
        # hacky workaround
        return offset + align_up(chunk_size + 0x800, 0x800) + 0x800
    elif "ST04B.BIN" in file and offset == 0x43000:
        return offset + align_up(chunk_size + 0x800, 0x800) + 0x800
    elif "ST08_01.BIN" in file and offset == 0x8B800:
        return offset + align_up(chunk_size + 0x800, 0x800) + 0x800
    elif "ST14.BIN" in file and offset == 0x4B800:
        return offset + align_up(chunk_size + 0x800, 0x800) + 0x800
    elif "ST08_02.BIN" in file and offset == 0x89800:
        return offset + align_up(chunk_size + 0x800, 0x800) + 0x800
    elif "ST0F_03.BIN" in file and offset == 0x69800:
        return offset + align_up(chunk_size + 0x800, 0x800) + 0x800
    elif "ST05_02.BIN" in file and offset == 0x72800:
        return offset + align_up(chunk_size + 0x800, 0x800) + 0x800
    elif "ST00.BIN" in file and offset in [0x0009E000, 0x000C2800]:
        return offset + align_up(chunk_size + 0x800, 0x800) + 0x800
    elif chunk_type == 5 and unk in [0x1820]:
        return offset + align_up(chunk_size + 0x800, 0x800) + 0x800
    elif chunk_type == 4:
        return offset + align_up(chunk_size, 0x800)
    else:
        return offset + align_up(chunk_size + 0x800, 0x800)

def get_chunks(file):
    chunks = []
    with open(file, "rb") as f:
        offset = 0
        while True:
            f.seek(offset, 0)
            chunk = f.read(0x800)
            if len(chunk) == 0:
                break
            chunk_type, chunk_size, _, chunk_load_addr = struct.unpack("<IIII", chunk[0:0x10])
            if chunk_type in [1, 9, 10]:
                chunk_size = struct.unpack("<I", chunk[0x28:0x2C])[0] * struct.unpack("<I", chunk[0x24:0x28])[0] * 2
            if chunk_type == 0xFFFFFFFF:
                break
            unk = struct.unpack("<I", chunk[0x18:0x1C])[0]
            print(f"{file}, {offset:X}")
            chunk_name = chunk[0x40:0x60].split(b"\x00")[0].decode("ascii")
            chunks.append((chunk_type, chunk_size, chunk_load_addr, chunk_name, offset, os.path.getsize(file), unk))
            if (chunk_type not in [1, 9, 10] or chunk_size > 0):
                offset = get_next_offset(file, offset, chunk_size, unk, chunk_type)
                print(f"Aligned to {offset:X}")
            else:
                offset += 0x800
            if offset >= os.path.getsize(file):
                break
    return chunks

load_addresses = {}
def get_yaml(file, chunks):
    for i, chunk in enumerate(chunks):
        (chunk_type, chunk_size, chunk_load_addr, chunk_name, chunk_offset, _, _) = chunk
        chunk_id = chunk_name
        chunk_id = f"ovl{i}_" + chunk_id.replace("\\", "_")[2:]
        os.makedirs(f"config/overlay/splat.us.{file.replace('.BIN', '')}/", exist_ok= True)
        with open(f"config/overlay/splat.us.{file.replace('.BIN', '')}/{chunk_id}.yaml", "w") as f:
            f.write(f"options:\n")
            f.write(f"  platform: psx\n")
            f.write(f"  basename: {file.replace('.BIN', '')}.{chunk_id}\n")
            f.write(f"  base_path: ../../../\n")
            f.write(f"  target_path: ./disks/us/CDDATA/DAT/{file}\n")
            f.write(f"  asm_path: asm/{file.replace('.BIN', '')}/{chunk_id}\n")
            f.write(f"  asset_path: assets/{file.replace('.BIN', '')}/{chunk_id}\n")
            f.write(f"  src_path: src/{file.replace('.BIN', '')}/{chunk_id}\n")
            f.write(f"  compiler: GCC\n")
            f.write(f"  extensions_path: tools/splat_ext\n")
            f.write(f"  symbol_addrs_path: config/overlay/splat.us.{file.replace('.BIN', '')}/generated.syms.{chunk_id}.txt\n")
            f.write(f"  undefined_funcs_auto_path: config/overlay/splat.us.{file.replace('.BIN', '')}/undefined_funcs_auto.us.{chunk_id}.txt\n")
            f.write(f"  undefined_syms_auto_path: config/overlay/splat.us.{file.replace('.BIN', '')}/undefined_syms_auto.us.{chunk_id}.txt\n")
            f.write(f"  find_file_boundaries: yes\n")
            f.write(f"  use_legacy_include_asm: no\n")
            f.write(f"  migrate_rodata_to_functions: no\n")
            f.write(f"  auto_decompile_empty_functions: no\n")
            f.write(f"segments:\n")
            # strip chunkname to just the filename
            f.write (f"# {chunk_name}\n")
            if "/" in chunk_name:
                chunk_name = chunk_name.split("/")[-1]
            if "\\" in chunk_name:
                chunk_name = chunk_name.split("\\")[-1]
            if "." in chunk_name:
                chunk_name = chunk_name.split(".")[0]
            
            if chunk_type == 0 and chunk_load_addr != 0:
                if chunk_load_addr not in load_addresses:
                    load_addresses[chunk_load_addr] = chunk_id
                f.write(f"  - name: {file.replace('.BIN', '')}_{('ovl') if chunk_name == '' else chunk_name}_{i}_header\n")
                f.write(f"    type: dashchunkheader\n")
                f.write(f"    start: 0x{chunk_offset:08X}\n")
                f.write(f"  - name: {file.replace('.BIN', '')}_{('ovl') if chunk_name == '' else chunk_name}_{i}\n")
                f.write(f"    type: code\n")
                f.write(f"    start: 0x{chunk_offset + 0x800:08X}\n")
                f.write(f"    vram: 0x{chunk_load_addr:08X}\n")
                f.write(f"    exclusive_ram_id: {file.replace('.BIN', '')}_{('ovl') if chunk_name == '' else chunk_name}_ram_{i}\n")
                f.write(f"    subalign: 4\n")
                f.write(f"    subsegments:\n")
                f.write(f"      - [0x{chunk_offset + 0x800:X}, data, {('ovl') if chunk_name == '' else chunk_name}_{i}]\n")
            else:
                f.write(f"  - name: {file.replace('.BIN', '')}_{chunk_name}_{i}_header\n")
                f.write(f"    type: dashchunkheader\n")
                f.write(f"    start: 0x{chunk_offset:08X}\n")
                if (chunk_type not in [1, 9, 10] or chunk_size > 0):
                    f.write(f"  - name: {file.replace('.BIN', '')}_{chunk_name}_{i}\n")
                    f.write(f"    type: bin\n")
                    f.write(f"    start: 0x{chunk_offset + (0x800 if chunk_type != 4 else 0x100):08X}\n")
            f.write(f"  - [0x{(chunk_offset + chunk_size + (0x800 if chunk_type != 4 else 0x100) + (0x800 if chunk_type == 5 else 0)):X}]\n")

def make_json(file, chunks):
    with open(f"config/overlay/splat.us.{file.replace('.BIN', '')}/build.json", "w") as f:
        f.write("{\n")
        f.write(f"\"overlays\": [\n")
        for i, chunk in enumerate(chunks):
            (chunk_type, chunk_size, chunk_load_addr, chunk_name, chunk_offset, fsize, unk) = chunk
            chunk_id = chunk_name
            chunk_id = f"ovl{i}_" + chunk_id.replace("\\", "_")[2:]
            f.write(f"[\"{chunk_id}\", {chunk_type}, {chunk_size}, {unk}]{', ' if i < len(chunks) - 1 else ''}\n")
        f.write(f"]\n")
        f.write("}\n")

if __name__ == "__main__":
    import sys
    if len(sys.argv) < 2:
        print("Usage: python3 make_yaml.py <folder>")
        exit(1)
    for file in os.listdir(sys.argv[1]):
        if file.endswith(".BIN"):
            chunks = get_chunks(os.path.join(sys.argv[1], file))
            get_yaml(file, chunks)
            make_json(file, chunks)
    print("common_load_addresses_for_overlays = {")
    for load in load_addresses:
        print(f"\t0x{load:08X}: \"{load_addresses[load]}\"")
    print("}")

