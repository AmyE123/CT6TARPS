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
	if (nitroFSInit(NULL)) {
		if (loadBeatsFromFile() != 1) {
			return 0;  // Turn off NDS if loading beats failed
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