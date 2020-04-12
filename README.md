# SDLPoP
An open-source port of Prince of Persia, based on the disassembly of the DOS version.

More info: doc/Readme.txt

Ported to OG Xbox with https://github.com/XboxDev/nxdk

Building:

Requires PR #319 of nxdk (until merged):
```
git clone https://github.com/XboxDev/nxdk.git
cd nxdk
git fetch origin pull/319/head
git checkout -b pullrequest FETCH_HEAD
git submodule init
git submodule update --recursive
```

```
cd ~
git clone https://github.com/Ryzee119/SDLPoP.git
cd SDLPoP
```
Modify `NXDK_DIR` in `Makefile.nxdk` to point to your NXDK directory
Build with:
`make -f Makefile.nxdk`
