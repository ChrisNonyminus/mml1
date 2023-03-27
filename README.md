# Megaman Legends Decomp
WIP Decompilation of Megaman Legends (aka Rockman Dash, formerly Rockman NEO) for the PlayStation 1.

This project/experiment was just recently started, so a lot of things are barebones at the moment.

The code is not yet shiftable.

Contributions and help are more than appreciated!

# Prequisites
- A Debian-based Linux distro. Arch-based distros and Gentoo *might* work, but I'm not positive.
- mipsel-linux-gnu toolchain
- [mkpsxiso](https://github.com/Lameguy64/mkpsxiso) (install the latest deb artifact from the latest commit action)
- python3
  - Run ``python3 -m pip install -U -r requirements.txt``

# BUILDING
- Take a cue and bin of the US release of Mega Man Legends, and place it in the disks folder.
- Rename the Track 1 bin to mml1.us.track1.bin. (Track 2 is just an empty 32MB file)
- run ``make extract_disk``
- run ``make split_all``
- run ``make``
- To make a new disk image of the game, run ``make disk``.

# Useful make phonies
- ``make format`` runs clang-format on all c code.
- ``make diff_rock_neo`` produces a diff file of hexdumps of ROCK_NEO.EXE.

