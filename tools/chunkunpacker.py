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


import struct
import os
import sys

def align_up(val, align):
    print (val, align)
    if (val % align) == 0:
        return val
    return (val + align - 1) & ~(align - 1)

def extract_chunks(bin_file_path):
    with open(bin_file_path, 'rb') as f:
        while True:
            chunk_header = f.read(0x800)
            if not chunk_header:  # End of file
                break
            

            chunk_type, chunk_size, unknown1, load_address = struct.unpack('<IIII', chunk_header[0x0:0x10])
            if chunk_size + f.tell() > os.path.getsize(bin_file_path):
                break
            if chunk_size == 0:
                f.seek(0x800, os.SEEK_CUR)
                continue
            unknown2, unknown3, unknown4 = struct.unpack('<III', chunk_header[0x10:0x1C])
            chunk_filename = chunk_header[0x40:0x60].split(b"\x00")[0]
            try:
                fn = chunk_filename.decode("ascii").rstrip('\0')
            except:
                chunk_filename = b""
            print(f'Found chunk "{fn}" of type {chunk_type} at 0x{f.tell():08X} with size 0x{chunk_size:08X} and load address 0x{load_address:08X}')
            # Get the file contents and align the size to 0x800
            file_contents = f.read(chunk_size)
            aligned_size = (chunk_size + 0x7FF) & ~0x7FF

            # Yield the chunk's header and contents
            yield chunk_type, chunk_size, unknown1, load_address, unknown2, unknown3, unknown4, chunk_filename.decode('ascii').rstrip('\0'), file_contents[:chunk_size], f.tell() - chunk_size, bin_file_path

            # Move to the next chunk
            f.seek(align_up(f.tell() + 0x800, 0x800) if chunk_type != 1 else align_up(f.tell() - 0x800, 0x800), os.SEEK_SET)

def perform_extraction(bin_file_path, output_dir):
    if not os.path.exists(output_dir):
        os.makedirs(output_dir)

    for i, (chunk_type, chunk_size, unknown1, load_address, unknown2, unknown3, unknown4, filename, contents, off, bin_file_name) in enumerate(extract_chunks(bin_file_path)):
        filename = filename.replace('\\', '/').replace('..', '').strip()
        if (filename == ''):
            filename = f'chunk_{i:03d}'

        # Create a text file with the chunk's header information
        # create the folder if it doesn't exist
        if not os.path.exists(os.path.dirname(output_dir + "/" + filename)):
            os.makedirs(os.path.dirname(output_dir + "/" + filename))
        header_file_path = output_dir + "/" + filename + ".txt"
        with open(header_file_path, 'w') as header_file:
            header_file.write(f'Type: {chunk_type}\n')
            header_file.write(f'Size: {chunk_size}\n')
            header_file.write(f'Unknown1: 0x{unknown1:08X}\n')
            header_file.write(f'Load Address: 0x{load_address:08X}\n')
            header_file.write(f'Unknown2: 0x{unknown2:08X}\n')
            header_file.write(f'Unknown3: 0x{unknown3:08X}\n')
            header_file.write(f'Unknown4: 0x{unknown4:08X}\n')
            header_file.write(f'Filename: {filename}\n')
            header_file.write(f'Bin File: {bin_file_name}\n')
            header_file.write(f'Offset: 0x{off:08X}\n')

        print(f'Exported header information for chunk "{filename}" to {header_file_path}')

        # Create a binary file with the chunk's contents
        contents_file_path = output_dir + "/" + filename
        with open(contents_file_path, 'wb') as contents_file:
            contents_file.write(contents)

        print(f'Exported contents for chunk "{filename}" to {contents_file_path}')

if __name__ == '__main__':
    if len(sys.argv) != 3:
        print('Usage: python chunkunpacker.py <bin_file_folder_path> <output_dir>')
        exit(1)

bin_file_folder_path = sys.argv[1]
output_dir = sys.argv[2].strip()

for bin_file_name in os.listdir(bin_file_folder_path):
    if not bin_file_name.endswith('.bin'):
        continue
    bin_file_path = os.path.join(bin_file_folder_path, bin_file_name)
    print(f'Processing {bin_file_path}...')
    perform_extraction(bin_file_path, output_dir)