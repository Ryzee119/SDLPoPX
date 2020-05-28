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

	#define _PCRTC_START 0xFD600800
	*(unsigned int*)(_PCRTC_START) = (unsigned int)_fb & 0x03FFFFFF;

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
	if(titleImageFileSrc != NULL && titleImageFileDest != NULL){
		int c = fgetc(titleImageFileSrc);
		while (c != EOF){
			fputc(c, titleImageFileDest);
			c = fgetc(titleImageFileSrc);
		}
	}
	if(titleImageFileDest)
		fclose(titleImageFileDest);
	if(titleImageFileSrc)
		fclose(titleImageFileSrc);

	//Create saves for each item I want to store and add the required metadata.
	fp = fopen("E:\\UDATA\\PoPX\\Settings\\SaveMeta.xbx", "wb");
	if(fp){
		fprintf(fp, "Name=Settings\r\n");
		fclose(fp);
	}

	fp = fopen("E:\\UDATA\\PoPX\\Replays\\SaveMeta.xbx", "wb");
	if(fp){
		fprintf(fp, "Name=Replays\r\n");
		fclose(fp);
	}

	fp = fopen("E:\\UDATA\\PoPX\\Saves\\SaveMeta.xbx", "wb");
	if(fp){
		fprintf(fp, "Name=Saves\r\n");
		fclose(fp);
	}

	fp = fopen("E:\\UDATA\\PoPX\\Highscores\\SaveMeta.xbx", "wb");
	if(fp){
		fprintf(fp, "Name=Highscores\r\n");
		fclose(fp);
	}


	//Let's make a quick and simple error is no compatible controller
	//was connected. There's also a bug in NXDK where hotplugging does not work.
	extern int nextRow;
	extern int nextCol;
	SDL_Init(SDL_INIT_GAMECONTROLLER);
	SDL_GameController* gamepad = SDL_GameControllerOpen(0);
	SDL_SetHint(SDL_HINT_JOYSTICK_ALLOW_BACKGROUND_EVENTS, "1");

	if(gamepad == NULL){
		const char error_msg0[] = "No compatible controller connected.\n";
		const char error_msg1[] = "Restart Xbox and try again\n";
		debugPrint("\n\n\n\n");
		nextCol = 640/2 - (strlen(error_msg0) * 8 / 2); debugPrint(error_msg0);
		nextCol = 640/2 - (strlen(error_msg1) * 8 / 2); debugPrint(error_msg1);
		while(1);
	}
	SDL_GameControllerClose(0);
	SDL_Quit();
	#endif


	pop_main();
	return 0;
}

