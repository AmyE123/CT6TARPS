#pragma once

#include "graphics.h"
#include "../utils.h"

#define SCREEN_PADDING 30
#define CIRCLE_DISAPPEAR_GAP 5

typedef struct {
	int x, y; // Position
	bool active; // Is the circle currently active?
	int appearTimes[MAX_BEATS]; // Array of times when the circle should appear
	int nextAppearIndex; // Index to track the next appearance time
	int duration; // Duration in frames the circle should remain visible
	int disappearTime; // Calculated time when the circle should disappear
} Circle;

extern Circle circles[MAX_CIRCLES];

/// <summary>
/// Load the beats from the framestamps file.
/// Checks for lack of framestamps file, or too many beats within framestamps.
/// </summary>
/// <returns>An integer, where '1' is success and '0' is fail.</returns>
int loadBeatsFromFile();

/// <summary>
/// For initialising the circle at the very start of the game.
/// </summary>
void initCircle();

/// <summary>
/// To reposition a circle to a random screen position.
/// </summary>
/// <param name="index">The index of the circle to reposition. (incase of multiple circles on screen at once.)</param>
void repositionCircle(int index);

/// <summary>
/// Activates the circle and calculates durations.
/// </summary>
/// <param name="index">The index of the circle to reposition. (incase of multiple circles on screen at once.)</param>
void activateCircle(int index);

/// <summary>
/// Manages the deactivation of a circle.
/// </summary>
void deactivateCircle();