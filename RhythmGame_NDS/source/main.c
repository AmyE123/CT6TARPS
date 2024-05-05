#include <fat.h>

#include "Graphics/graphics.h"
#include "Graphics/circle.h"
#include "Audio/audio.h"
#include "Game/game.h"
#include "utils.h"
#include "data_loader.h"

bool gameActive = true;
int beats[MAX_BEATS];
int num_beats = 0;

int main(void) {
	consoleDemoInit(); // Initializes the debugging console
	fatInitDefault();  // Initializes the FAT file system

	if (!loadBeatsFromFile("/app_data/framestamps.txt", beats, MAX_BEATS, &num_beats)) {
		while (1) swiWaitForVBlank();
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