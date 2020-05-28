# SDLPoP
An open-source port of Prince of Persia, based on the disassembly of the DOS version.

More info: doc/Readme.txt

Ported to OG Xbox with https://github.com/XboxDev/nxdk

## Building:

Setup and install nxdk. Refer to `https://github.com/XboxDev/nxdk`  
We also need a experimental [audio fix](https://github.com/XboxDev/nxdk-sdl/pull/27) (until merged into master)
```
cd path/to/nxdk
cd lib/sdl/SDL2
git fetch origin pull/27/head:pr27
git checkout pr27
```

Then do this:  
```
cd~
export NXDK_DIR=/path/to/nxdk
git clone https://github.com/Ryzee119/SDLPoPX.git
cd SDLPoPX
make -f Makefile.nxdk
```
Compiled xbe can be found in `SDLPoPx/bin/`

The original Makefile is located in `/src/` and still can be used to build for Windows or Linux.
