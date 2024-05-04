#include "circle.h"
#include "../utils.h"
#include <stdio.h>

Circle circles[MAX_CIRCLES];

int beats[MAX_BEATS];
int num_beats = 0;

int loadBeatsFromFile() {
	FILE* file = fopen("/app_data/timestamps.txt", "rb"); // Opens the timestamps file.

	if (!file) {
		iprintf("Failed to open the file.\n Did you use the wrong version of the ROM? (NDS/Emulator)\n\n If not, on the root of your SD Card, create a 'app_data' folder and put your 'timestamps.txt' file inside of it.");
		return 0;  // Return 0 on failure to open the file
	}

	int value;
	while (fscanf(file, "%d,", &value) > 0) {
		if (num_beats < MAX_BEATS) {
			beats[num_beats++] = value;
		}
		else {
			fclose(file);
			iprintf("Failed to load beats from file.\n Too many values within the 'timestamps.txt' file.");
			return 0;  // Return 0 on reaching maximum capacity
		}
	}

	fclose(file);
	return 1;  // Return 1 on successful loading
}

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