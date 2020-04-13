/*
SDLPoP, a port/conversion of the DOS game Prince of Persia.
Copyright (C) 2013-2019  Dávid Nagy

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <https://www.gnu.org/licenses/>.

The authors of this program may be contacted at https://forum.princed.org
*/

#include <hal/xbox.h>
#include <hal/video.h>
#include "common.h"

extern uint8_t* _fb;

int main(int argc, char *argv[])
{
	g_argc = argc;
	g_argv = argv;
	
	size_t fb_size = 640 * 480 * 4;
	_fb = (uint8_t*)MmAllocateContiguousMemoryEx(fb_size, 0, 0xFFFFFFFF, 0x1000, PAGE_READWRITE | PAGE_WRITECOMBINE);
	memset(_fb, 0x00, fb_size);
	
	XVideoSetMode(640, 480, 32, REFRESH_DEFAULT);
	pop_main();
	return 0;
}

