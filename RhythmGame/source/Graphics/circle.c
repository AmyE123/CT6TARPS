#include "circle.h"
#include "../utils.h"
#include <stdio.h>

Circle circles[MAX_CIRCLES];

int beats[] = {
	105, 180, 255, 330, 630, 660, 705, 735, 780, 810,
	840, 885, 915, 930, 960, 990, 1005, 1020, 1065, 1095,
	1140, 1170, 1200, 1230, 1245, 1275, 1290, 1305, 1350, 1365,
	1380, 1425, 1440, 1455, 1485, 1530, 1560, 1605, 1635, 1665,
	1710, 1740, 1785, 1860, 1920, 1995, 2070, 2145, 2205, 2280,
	2355, 2430, 2505, 2565, 2640, 2745, 2790, 2865, 2940, 3000,
	3075, 3150, 3225, 3285, 3360, 3435, 3645, 3720, 3765, 3795,
	3825, 3870, 3900, 3945, 3975, 4020, 4050, 4080, 4365, 4410,
	4470, 4485, 4500, 4515, 4545, 4620, 4650, 4695, 4770, 4785,
	4785, 4800, 4845, 4890, 4920, 4935, 4950, 5025, 5055, 5085,
	5160, 5175, 5205, 5205, 5220, 5235, 5265, 5325, 5340, 5355,
	5385, 5415, 5445, 5490, 5520, 5565, 5625, 5640, 5655, 5670,
	5700, 5775, 5805, 5850, 5925, 5940, 5940, 5955, 6000, 6045,
	6060, 6075, 6090, 6165, 6210, 6240, 6315, 6330, 6345, 6360,
	6375, 6390, 6420, 6480, 6495, 6510, 6525, 6570, 6600, 6645,
	6675, 6705, 6735, 6750, 6780, 6810, 6825, 6840, 6855, 6870,
	6900, 6915, 6930, 6945, 6960, 6975, 7005, 7020, 7035, 7050,
	7080, 7095, 7110, 7125, 7140, 7170, 7185, 7200, 7215, 7230,
	7260, 7275, 7290, 7305, 7320, 7335, 7365, 7380, 7395, 7410,
	7425, 7455, 7470, 7485, 7500, 7515, 7545, 7560, 7575, 7590,
	7620, 7635, 7650, 7665, 7680, 7710, 7725, 7740, 7755, 7770,
	7800, 7815, 7830, 7845, 7860, 7875, 7890, 7920, 7935, 7950,
	7980, 7995, 8010, 8025, 8040, 8055, 8085, 8100, 8115, 8130,
	8145, 8175, 8190, 8205, 8220, 8235, 8265, 8280, 8295, 8310,
	8325, 8355, 8370, 8385, 8400, 8430, 8445, 8460, 8475, 8490,
	8520, 8535, 8550, 8565, 8580, 8610, 8625, 8640, 8655, 8670,
	8700, 8715, 8730, 8745, 8760, 8790, 8805, 8820, 8835, 8850,
	8865, 8865, 8880, 8880, 8895, 8910, 8910, 8925, 8940, 8940,
	8955, 8955, 8970, 8985, 8985, 9000, 9015, 9015, 9030, 9030,
	9045, 9060, 9060, 9075, 9090, 9105, 9120, 9135, 9165, 9180,
	9195, 9210, 9240, 9240, 9255, 9270, 9300, 9345, 9375, 9405,
	9450, 9480, 9525, 9525, 9540, 9555, 9585, 9630, 9660, 9690,
	9720, 9735, 9750, 9780, 9795, 9810, 9825, 9840, 9870, 9885,
	9900, 9915, 9930, 9960, 9975, 9990, 10020, 10065, 10095, 10110,
	10125, 10125, 10170, 10215, 10245, 10260, 10275, 10350, 10380, 10410,
	10485, 10500, 10530, 10530, 10545, 10560, 10605, 10650, 10665, 10695,
	10710, 10740, 10785, 10815 }; // Times in frames when circles should appear.

void initCircle() {
	repositionCircle(0);

	for (int i = 0; i < MAX_BEATS - 1; i++) {
		circles[0].appearTimes[i] = beats[i];
	}

	circles[0].nextAppearIndex = 0; // Start with the first beat.
	circles[0].active = false;  // Initially inactive.
}

void repositionCircle(int index) {
	circles[index].x = SCREEN_PADDING + rand() % (SCREEN_WIDTH - 2 * SCREEN_PADDING);
	circles[index].y = SCREEN_PADDING + rand() % (SCREEN_HEIGHT - 2 * SCREEN_PADDING);
}

void activateCircle(int index) {
	repositionCircle(index);

	// Check if there is a next beat.
	if (circles[index].nextAppearIndex < MAX_BEATS - 1) {
		// Frames to disappear before the next circle appears. If circles stop spawning suddenly that could mean the defined gap was larger that the duration between the beats.
		int gap = CIRCLE_DISAPPEAR_GAP;

		// Calculates duration circle should be active.
		int currentBeatTime = beats[circles[index].nextAppearIndex];
		int nextBeatTime = beats[circles[index].nextAppearIndex + 1];
		circles[index].duration = nextBeatTime - currentBeatTime - gap;
	}
	else {
		circles[index].duration = 180; // Default duration if it's the last beat or no next beat.
	}

	// Sets the circle as visible and sets the disappear time.
	circles[index].active = true;
	circles[index].disappearTime = beats[circles[index].nextAppearIndex] + circles[index].duration;
}

void deactivateCircle() {
	circles[0].active = false; // Sets the circle as not visible.
	clearScreen(); // Clear the screen when the circle is deactivated.   

	// Prepares for next circle appearance.
	if (circles[0].nextAppearIndex + 1 < MAX_BEATS) {
		circles[0].nextAppearIndex++;
		if (circles[0].nextAppearIndex < MAX_BEATS - 1) {
			int nextAppearanceTime = beats[circles[0].nextAppearIndex];
			circles[0].disappearTime = nextAppearanceTime + circles[0].duration;
		}
		repositionCircle(0); // Reposition the circle for its next appearance.
	}
}