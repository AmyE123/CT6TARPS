#include "input.h"
#include "../Assembly/asm_functions.h"

int score;
int streak;
static unsigned short prevKeys = 0;

void checkTouch(touchPosition touch, mm_sound_effect hit) {
	if (circles[0].active && abs(touch.px - circles[0].x) < HIT_RANGE && abs(touch.py - circles[0].y) < HIT_RANGE) {
		consoleClear();
		mmEffectEx(&hit);
		deactivateCircle();

		int basePoints = BASE_HIT_POINTS;

		if (streak > 1)
		{
			int scoreIncrement = basePoints * streak;
			score += scoreIncrement;
		}
		else
		{
			score += basePoints;
		}

		printf("Circle Hit! \n Score: %d\n", score);

		streak += 1;
		if (streak > 1)
		{
			printf("Streak: %d\n", streak);
		}
	}
}

void touchMissed() {
	consoleClear();
	streak = 0;
	printf("Circle Miss! \n Score: %d\n", score);
}

void updateInput() {
	updateButtonInput();
	updateTouchInput();
}

void updateTouchInput() {
	scanKeys();
	touchPosition touch;
	touchRead(&touch);

	if (keysHeld() & KEY_TOUCH) {
		checkTouch(touch, hit);
	}
}

void updateButtonInput() {
	unsigned short currentKeys = read_keys_asm();
	unsigned short justPressed = currentKeys & (currentKeys ^ prevKeys);

	if (justPressed & KEY_UP) {
		playHitSoundEffect(1);
	}

	if (justPressed & KEY_DOWN) {
		playHitSoundEffect(2);
	}

	if (justPressed & KEY_LEFT) {
		playHitSoundEffect(3);
	}

	if (justPressed & KEY_RIGHT) {
		playHitSoundEffect(4);
	}

	if (justPressed & KEY_R || justPressed & KEY_L) {
		playHitSoundEffect(5);
	}

	// Update previous keys state at the end of the frame
	prevKeys = currentKeys;
}