/*
SDLPoP, a port/conversion of the DOS game Prince of Persia.
Copyright (C) 2013-2021  Dávid Nagy

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

int main(int argc, char *argv[])
{
#ifdef NXDK
	XVideoSetMode(640, 480, 32, REFRESH_DEFAULT);
	/* Inject args */
	argc = 1;
	argv = malloc(sizeof(char *) * argc);
	for (int i = 0; i < argc; i++)
		argv[i] = malloc(256);
	strcpy(argv[0], "D:\\default.xbe");
	SDL_SetHint(SDL_HINT_JOYSTICK_ALLOW_BACKGROUND_EVENTS, "1");

	BOOL mounted = nxMountDrive('E', "\\Device\\Harddisk0\\Partition1\\");
	assert(mounted);
	CreateDirectoryA("E:\\UDATA", NULL);
	CreateDirectoryA(savePath, NULL);
	CreateDirectoryA(settingsPath, NULL);
	CreateDirectoryA(popSavePath, NULL);
	CreateDirectoryA(scorePath, NULL);

	//Create game profile for saves
	FILE *fp = fopen("E:\\UDATA\\PoPX\\TitleMeta.xbx", "wb");
	fprintf(fp, "TitleName=Prince of Persia\r\n");
	fclose(fp);

	//Copy title image to game profile
	FILE *titleImageFileSrc = fopen("D:\\data\\TitleImage.xbx", "rb");
	FILE *titleImageFileDest = fopen("E:\\UDATA\\PoPX\\TitleImage.xbx", "wb");
	if (titleImageFileSrc != NULL && titleImageFileDest != NULL)
	{
		int c = fgetc(titleImageFileSrc);
		while (c != EOF)
		{
			fputc(c, titleImageFileDest);
			c = fgetc(titleImageFileSrc);
		}
	}
	if (titleImageFileDest)
		fclose(titleImageFileDest);
	if (titleImageFileSrc)
		fclose(titleImageFileSrc);

	//Create saves for each item I want to store and add the required metadata.
	fp = fopen("E:\\UDATA\\PoPX\\Settings\\SaveMeta.xbx", "wb");
	if (fp)
	{
		fprintf(fp, "Name=Settings\r\n");
		fclose(fp);
	}

	fp = fopen("E:\\UDATA\\PoPX\\Replays\\SaveMeta.xbx", "wb");
	if (fp)
	{
		fprintf(fp, "Name=Replays\r\n");
		fclose(fp);
	}

	fp = fopen("E:\\UDATA\\PoPX\\Saves\\SaveMeta.xbx", "wb");
	if (fp)
	{
		fprintf(fp, "Name=Saves\r\n");
		fclose(fp);
	}

	fp = fopen("E:\\UDATA\\PoPX\\Highscores\\SaveMeta.xbx", "wb");
	if (fp)
	{
		fprintf(fp, "Name=Highscores\r\n");
		fclose(fp);
	}
#endif
	g_argc = argc;
	g_argv = argv;
	pop_main();
	return 0;
}

