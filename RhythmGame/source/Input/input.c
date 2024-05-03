#include "input.h"

int score;
int streak;

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