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

#include "common.h"

#ifdef NXDK
#include <assert.h>
#include <windows.h>
#include <nxdk/mount.h>
#include <hal/xbox.h>
#include <hal/video.h>

extern uint8_t* _fb;
#endif
int main(int argc, char *argv[])
{
	g_argc = argc;
	g_argv = argv;

	#ifdef NXDK
	size_t fb_size = 640 * 480 * 4;
	_fb = (uint8_t*)MmAllocateContiguousMemoryEx(fb_size,
	                                             0,
												 0xFFFFFFFF,
												 0x1000,
												 PAGE_READWRITE | PAGE_WRITECOMBINE);
	memset(_fb, 0x00, fb_size);
	XVideoSetMode(640, 480, 32, REFRESH_DEFAULT);

	BOOL mounted = nxMountDrive('E', "\\Device\\Harddisk0\\Partition1\\");
	assert(mounted);
	CreateDirectoryA(savePath, NULL);
	CreateDirectoryA(settingsPath, NULL);
	CreateDirectoryA(replayPath, NULL);
	CreateDirectoryA(popSavePath, NULL);
	CreateDirectoryA(scorePath, NULL);

	//Create game profile for saves
	FILE* fp = fopen("E:\\UDATA\\PoPX\\TitleMeta.xbx", "wb");
	fprintf(fp, "TitleName=Prince of Persia\r\n");
	fclose(fp);

	//Copy title image to game profile
	FILE* titleImageFileSrc = fopen("D:\\data\\TitleImage.xbx", "rb");
	FILE* titleImageFileDest = fopen("E:\\UDATA\\PoPX\\TitleImage.xbx", "wb");
	int c = fgetc(titleImageFileSrc);
	while (c != EOF){
		fputc(c, titleImageFileDest);
		c = fgetc(titleImageFileSrc);
	}
	fclose(titleImageFileDest);
	fclose(titleImageFileSrc);

	//Create saves for each item I want to store and add the required metadata.
	fp = fopen("E:\\UDATA\\PoPX\\Settings\\SaveMeta.xbx", "wb");
	fprintf(fp, "Name=Settings\r\n");
	fclose(fp);

	fp = fopen("E:\\UDATA\\PoPX\\Replays\\SaveMeta.xbx", "wb");
	fprintf(fp, "Name=Replays\r\n");
	fclose(fp);

	fp = fopen("E:\\UDATA\\PoPX\\Saves\\SaveMeta.xbx", "wb");
	fprintf(fp, "Name=Saves\r\n");
	fclose(fp);

	fp = fopen("E:\\UDATA\\PoPX\\Highscores\\SaveMeta.xbx", "wb");
	fprintf(fp, "Name=Highscores\r\n");
	fclose(fp);
	#endif

	pop_main();
	return 0;
}

