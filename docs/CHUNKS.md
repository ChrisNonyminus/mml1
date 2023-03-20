The files are raw binary archive files, with specific chunks representing containing archived files, with the first chunk always at the start of the file with no header for the overall archive, just the chunks. Here's a rundown of the format of each chunk:
```
CHUNK HEADER (offsets are relative to chunk's location)
0x0: ??? Type? (It seems that if 0, this is a code overlay loaded into executable game memory)
0x4: Size of chunk
0x8: ???
0xC: Load address if type 0
0x10-0x40: ???
0x40-0x800: Chunk filename, as a null terminated string
0x800-(0x800+chunk size): file contents
Chunk size, aligned up to 0x800: next chunk, starting with the header
```