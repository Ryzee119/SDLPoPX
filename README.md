# SDLPoP
An open-source port of Prince of Persia, based on the disassembly of the DOS version.

More info: doc/Readme.txt

Ported to OG Xbox with https://github.com/XboxDev/nxdk

## Building:

Requires PR #319 of nxdk (until merged):
```
git clone https://github.com/XboxDev/nxdk.git
cd nxdk
git fetch origin pull/319/head:PR319
git merge PR319
git submodule init
git submodule update --recursive
```

```
cd ~
git clone https://github.com/Ryzee119/SDLPoPX.git
cd SDLPoPX
```
Modify `NXDK_DIR` in `Makefile.nxdk` to point to your NXDK directory.
Then you can build with: `make -f Makefile.nxdk`

The original Makefile is located in `/src/` and still can be used to build for Windows or Linux.
