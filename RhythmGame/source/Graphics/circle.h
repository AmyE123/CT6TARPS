#pragma once

#include "graphics.h"
#include "../utils.h"

#define SCREEN_PADDING 30

typedef struct {
	int x, y; // Position
	bool active; // Is the circle currently active?
	int appearTimes[MAX_BEATS]; // Array of times when the circle should appear
	int nextAppearIndex; // Index to track the next appearance time
	int duration; // Duration in frames the circle should remain visible
	int disappearTime; // Calculated time when the circle should disappear
} Circle;

extern Circle circles[MAX_CIRCLES];

void initCircle();

void repositionCircle(int index);

void repositionAndActivateCircle(int index);

void deactivateCircle();