#!/usr/bin/env python3

def add_custom_arguments(parser):
    parser.add_argument(
        "--version",
        default="us",
        dest='version',
        help="Decide what version of the game to use (us, etc.)",
    )


def apply_rock_neo(config, version):
    config['baseimg'] = f'disks/{version}/' + (f'ROCK_NEO.EXE')
    config['myimg'] = f'build/' + (f'rock_neo.exe')
    config['mapfile'] = f'build/rock_neo.map'
    config['source_directories'] = [
        f'src/rock_neo', 'include', f'asm/rock_neo']
    config['objdump_executable'] = 'mipsel-linux-gnu-objdump'


def apply_bin(config, version, name):
    config["arch"] = "mipsel"
    config['baseimg'] = f'disks/{version}/' + (f'CDDATA/DAT/{name}.BIN').upper()
    config['myimg'] = f'build/{version}/' + (f'{name}.bin').upper()
    config['mapfile'] = f'build/{version}/{name}.map'
    config['source_directories'] = [
        f'src/{name}', 'include', f'asm/{version}/{name}']
    config['objdump_executable'] = 'mipsel-linux-gnu-objdump'


def apply(config, args):
    name = 'rock_neo'
    version = args.version or 'us'
    if name.startswith("rock_neo"):
        apply_rock_neo(config, version)

    config["arch"] = "mipsel"
    config['objdump_executable'] = 'mipsel-linux-gnu-objdump'
