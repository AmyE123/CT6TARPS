#include "Graphics/graphics.h"
#include "Graphics/circle.h"
#include "Audio/audio.h"
#include "Game/game.h"
#include "utils.h"
#include <fat.h>
#include <unistd.h>
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

bool gameActive = true;

int main(void) {
    consoleDemoInit(); // Initializes the debugging console
    fatInitDefault();  // Initializes the FAT file system

    if (!loadBeatsFromFile()) {
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