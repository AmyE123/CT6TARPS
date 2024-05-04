#include "Graphics/graphics.h"
#include "Graphics/circle.h"
#include "Audio/audio.h"
#include "Game/game.h"
#include "utils.h"

bool gameActive = true;

int main(void) {
	initGraphics();
	initCircle();
	initAudio();
	
	int gameTime = 0;

	while (gameActive && gameTime <= GAME_DURATION) {
		updateGameLoop(&gameTime, circles);
	}

	return 0;
}

