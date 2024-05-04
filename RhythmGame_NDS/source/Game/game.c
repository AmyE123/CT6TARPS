#include "game.h"
#include "../Graphics/circle.h"
#include "../Graphics/graphics.h"
#include "../Input/input.h"
#include "../Audio/audio.h"

void updateGameLoop(int* gameTime, Circle circles[]) {
	updateInput();

	// Handle circle appearance based on pre-defined beats
	if (!circles[0].active && circles[0].nextAppearIndex < MAX_BEATS && *gameTime == circles[0].appearTimes[circles[0].nextAppearIndex]) {
		activateCircle(0);
	}

	// Check to deactivate circle
	if (circles[0].active && *gameTime >= circles[0].disappearTime) {
		deactivateCircle();
		touchMissed();
	}

	// Only draw the circle if it's active
	if (circles[0].active) {
		drawCircle(circles[0].x, circles[0].y, getBackgroundLayer());
	}
	else {
		clearScreen();
	}

	swiWaitForVBlank(); // Sync with the vertical blank
	(*gameTime)++; // Increment the game timer
}