# The files are raw binary archive files, with specific chunks representing containing archived files, with the first chunk always at the start of the file with no header for the overall archive, just the chunks. Here's a rundown of the format of each chunk:
# ```
# CHUNK HEADER (offsets are relative to chunk's location)
# 0x0: ??? Type? (It seems that if 0, this is a code overlay loaded into executable game memory)
# 0x4: Size of chunk
# 0x8: ???
# 0xC: Load address if type 0
# 0x10-0x40: ???
# 0x40-0x800: Chunk filename, as a null terminated string
# 0x800-(0x800+chunk size): file contents
# Chunk size, aligned up to 0x800: next chunk, starting with the header
# ```

# This python script will scan a given folder for files that follow this format, and create yamls for splat, placed in the "config" folder and named splatconfig.us.{overlay file name}.yaml.

# template yaml:

# options:
#     platform:     psx
#     basename:     {file.replace(".bin", "")}
#     base_path:    ../
#     target_path:  ./{folder}/{file}
#     asm_path:     asm/{file.replace(".bin", "")}
#     asset_path:   assets/{file.replace(".bin", "")}
#     src_path:     src/{file.replace(".bin", "")}
#     compiler:     GCC
#     symbol_addrs_path: config/syms.us.{file.replace(".bin", "")}.txt
#     undefined_funcs_auto_path: config/undefined_funcs_auto.us.{file.replace(".bin", "")}.txt
#     undefined_syms_auto_path:  config/undefined_syms_auto.us.{file.replace(".bin", "")}.txt
#     find_file_boundaries: yes
#     use_legacy_include_asm: no
#     migrate_rodata_to_functions: no
#     auto_decompile_empty_functions: no
#     gp_value: 0x80097864
#
# segments:
# (for each type 0 overlay)
# #     - name: {file.replace(".bin", "")}_{ovlXX if chunk name empty, otherwise chunk name}_header
# #       type: bin
# #       start: 0x{header offset:08X}
# #
# #     - name: {file.replace(".bin", "")}_{ovlXX if chunk name empty, otherwise chunk name}
# #       type: code
# #       start: 0x{header offset + 0x800:08X}
# #       vram: 0x{load address:08X}
# #       subalign: 4
# #       subsegments:
# #         - [0x{header offset + 0x800:X}, data, {ovlXX if chunk name empty, otherwise chunk name}]
# (for each non-type 0 overlay: bin)
# #     - name: {file.replace(".bin", "")}_{chunk name}_header
# #       type: bin
# #       start: 0x{header offset:08X}
# #
# #     - name: {file.replace(".bin", "")}_{chunk name}
# #       type: data
# #       start: 0x{header offset + 0x800:08X}
# #       vram: 0x{load address:08X}
# #       subalign: 4
# #       subsegments:
# #         - [0x{header offset + 0x800:X}, bin, {chunk name}}]
#     - [0x{file size:X}]

import os
import struct
import yaml


def align_up(val, align):
    print (val, align)
    if (val % align) == 0:
        return val
    return (val + align - 1) & ~(align - 1)

def get_chunks(file):
    print(file)
    chunks = []
    with open(file, "rb") as f:
        offset = 0
        while True:
            f.seek(offset, 0)
            chunk = f.read(0x800)
            if len(chunk) == 0:
                break
            chunk_type, chunk_size, _, chunk_load_addr = struct.unpack("<IIII", chunk[0:0x10])
            if chunk_size + offset + 0x800 >= os.path.getsize(file):
                break
            if chunk_size == 0:
                offset += 0x800
                continue
            print (offset)
            chunk_name = chunk[0x40:0x60].split(b"\x00")[0].decode("ascii")
            print(chunk_type, chunk_size, chunk_load_addr, chunk_name)
            chunks.append((chunk_type, chunk_size, chunk_load_addr, chunk_name, offset, os.path.getsize(file)))
            offset = align_up(offset + 0x800 + chunk_size, 0x800) if chunk_type != 1 else align_up(offset + chunk_size, 0x800)
    return chunks

def get_yaml(file, chunks):
    # yaml_dict = {
    #     "options": {
    #         "platform": "psx",
    #         "basename": file.replace(".bin", ""),
    #         "base_path": "../",
    #         "target_path": f"./disks/us/cddata/dat/{file}",
    #         "asm_path": f"asm/{file.replace('.bin', '')}",
    #         "asset_path": f"assets/{file.replace('.bin', '')}",
    #         "src_path": f"src/{file.replace('.bin', '')}",
    #         "compiler": "GCC",
    #         "symbol_addrs_path": f"config/syms.us.{file.replace('.bin', '')}.txt",
    #         "undefined_funcs_auto_path": f"config/undefined_funcs_auto.us.{file.replace('.bin', '')}.txt",
    #         "undefined_syms_auto_path": f"config/undefined_syms_auto.us.{file.replace('.bin', '')}.txt",
    #         "find_file_boundaries": "yes",
    #         "use_legacy_include_asm": "no",
    #         "migrate_rodata_to_functions": "no",
    #         "auto_decompile_empty_functions": "no",
    #         "gp_value": "0x80097864",
    #     },
    #     "segments": [],
    # }
    # for i, chunk in enumerate(chunks):
    #     chunk_type, chunk_size, chunk_load_addr, chunk_name, chunk_offset, fsize = chunk
    #     # strip chunkname to just the filename
    #     if "." in chunk_name:
    #         chunk_name = chunk_name.split(".")[0]
    #     if "/" in chunk_name:
    #         chunk_name = chunk_name.split("/")[-1]
        
    #     if chunk_type == 0:
    #         yaml_dict["segments"].append({
    #             "name": f"{file.replace('.bin', '')}_{('ovl' + str(i)) if chunk_name == '' else chunk_name}_header",
    #             "type": "bin",
    #             "start": f"0x{chunk_offset:08X}",
    #         })
    #         yaml_dict["segments"].append({
    #             "name": f"{file.replace('.bin', '')}_{('ovl' + str(i)) if chunk_name == '' else chunk_name}",
    #             "type": "code",
    #             "start": chunk_offset + 0x800,
    #             "vram": f"0x{chunk_load_addr:08X}",
    #             "subalign": 4,
    #             "subsegments": [
    #                 [f"0x{chunk_offset + 0x800:X}", "data", f"{('ovl' + str(i)) if chunk_name == '' else chunk_name}"],
    #             ],
    #         })
    #     else:
    #         yaml_dict["segments"].append({
    #             "name": f"{file.replace('.bin', '')}_{chunk_name}_header",
    #             "type": "bin",
    #             "start": f"0x{chunk_offset:08X}",
    #         })
    #         yaml_dict["segments"].append({
    #             "name": f"{file.replace('.bin', '')}_{chunk_name}",
    #             "type": "data",
    #             "start": f"0x{chunk_offset + 0x800:08X}",
    #             "vram": f"0x{chunk_load_addr:08X}",
    #             "subalign": 4,
    #             "subsegments": [
    #                 [f"0x{chunk_offset + 0x800:X}", "bin", f"{chunk_name}"],
    #             ],
    #         })
    # yaml_dict["segments"].append([f"0x{fsize:X}"])
    # return yaml_dict
    with open(f"config/splat.us.{file.replace('.bin', '')}.yaml", "w") as f:
        f.write(f"options:\n")
        f.write(f"  platform: psx\n")
        f.write(f"  basename: {file.replace('.bin', '')}\n")
        f.write(f"  base_path: ../\n")
        f.write(f"  target_path: ./disks/us/cddata/dat/{file}\n")
        f.write(f"  asm_path: asm/{file.replace('.bin', '')}\n")
        f.write(f"  asset_path: assets/{file.replace('.bin', '')}\n")
        f.write(f"  src_path: src/{file.replace('.bin', '')}\n")
        f.write(f"  compiler: GCC\n")
        f.write(f"  symbol_addrs_path: config/syms.us.{file.replace('.bin', '')}.txt\n")
        f.write(f"  undefined_funcs_auto_path: config/undefined_funcs_auto.us.{file.replace('.bin', '')}.txt\n")
        f.write(f"  undefined_syms_auto_path: config/undefined_syms_auto.us.{file.replace('.bin', '')}.txt\n")
        f.write(f"  find_file_boundaries: yes\n")
        f.write(f"  use_legacy_include_asm: no\n")
        f.write(f"  migrate_rodata_to_functions: no\n")
        f.write(f"  auto_decompile_empty_functions: no\n")
        f.write(f"  gp_value: 0x80097864\n")
        f.write(f"segments:\n")
        fsize = 0
        for i, chunk in enumerate(chunks):
            (chunk_type, chunk_size, chunk_load_addr, chunk_name, chunk_offset, fsize) = chunk
            # strip chunkname to just the filename
            f.write (f"# {chunk_name}\n")
            if "/" in chunk_name:
                chunk_name = chunk_name.split("/")[-1]
            if "\\" in chunk_name:
                chunk_name = chunk_name.split("\\")[-1]
            if "." in chunk_name:
                chunk_name = chunk_name.split(".")[0]
            
            if chunk_type == 0 and chunk_load_addr != 0:
                f.write(f"  - name: {file.replace('.bin', '')}_{('ovl') if chunk_name == '' else chunk_name}_{i}_header\n")
                f.write(f"    type: bin\n")
                f.write(f"    start: 0x{chunk_offset:08X}\n")
                f.write(f"  - name: {file.replace('.bin', '')}_{('ovl') if chunk_name == '' else chunk_name}_{i}\n")
                f.write(f"    type: code\n")
                f.write(f"    start: 0x{chunk_offset + 0x800:08X}\n")
                f.write(f"    vram: 0x{chunk_load_addr:08X}\n")
                f.write(f"    exclusive_ram_id: {file.replace('.bin', '')}_{('ovl') if chunk_name == '' else chunk_name}_ram_{i}\n")
                f.write(f"    subalign: 4\n")
                f.write(f"    subsegments:\n")
                f.write(f"      - [0x{chunk_offset + 0x800:X}, data, {('ovl') if chunk_name == '' else chunk_name}_{i}]\n")
            else:
                f.write(f"  - name: {file.replace('.bin', '')}_{chunk_name}_{i}_header\n")
                f.write(f"    type: bin\n")
                f.write(f"    start: 0x{chunk_offset:08X}\n")
                f.write(f"  - name: {file.replace('.bin', '')}_{chunk_name}_{i}\n")
                f.write(f"    type: bin\n")
                f.write(f"    start: 0x{chunk_offset + 0x800:08X}\n")
        f.write(f"  - [0x{fsize:X}]\n")

if __name__ == "__main__":
    import sys
    if len(sys.argv) < 2:
        print("Usage: python3 make_yaml.py <folder>")
        exit(1)
    for file in os.listdir(sys.argv[1]):
        if file.endswith(".bin"):
            chunks = get_chunks(os.path.join(sys.argv[1], file))
            get_yaml(file, chunks)

