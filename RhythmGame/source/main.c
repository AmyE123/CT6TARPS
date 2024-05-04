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

bool loadFile() {
    consoleDemoInit(); // Initialize console for output, if not already initialized
    FILE* file = fopen("/app_data/timestamps.txt", "rb");

    if (!file) {
        iprintf("Failed to open file. Error: %s\n", strerror(errno));
        return false;  // Return false on failure to open the file
    }

    fclose(file);
    iprintf("File loaded successfully.\n");
    return true;  // Return true on successful loading
}

int main(void) {
    consoleDemoInit(); // Initializes the debugging console
    fatInitDefault();  // Initializes the FAT file system

    if (!loadFile()) {
        iprintf("Failed to load beats from file.\n");
        while (1) {            
            swiWaitForVBlank(); // Wait for vertical blanking interval
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