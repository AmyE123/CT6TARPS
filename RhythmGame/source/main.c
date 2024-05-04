#include <nds.h>
#include <filesystem.h>
#include <string.h>
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>

#include "Graphics/graphics.h"
#include "Graphics/circle.h"
#include "Audio/audio.h"
#include "Game/game.h"
#include "utils.h"

bool gameActive = true;

int main(void) {
    consoleDemoInit();

    // Initialize file system
    if (!nitroFSInit(NULL)) {
        iprintf("Failed to initialize the NITRO file system\n Did you add a 'timestamps.txt' file to the 'nitrofiles' folder?");
        while (1) {
            swiWaitForVBlank();
        }
        
    }

    // Load beats from file
    if (loadBeatsFromFile() != 1) {
        iprintf("Failed to load beats from file.\n The issue may be that you have surpassed the max amount of beats.");
        while (1) {
            swiWaitForVBlank();
        }
    }

	initGraphics();
	initCircle();
	initAudio();
	
	int gameTime = 0;

	while (gameActive && gameTime <= GAME_DURATION) {
		updateGameLoop(&gameTime, circles);
	}

	return 0;
}