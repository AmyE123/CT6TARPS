#pragma once
#include <stdbool.h>

/// <summary>
/// Load the beats from the framestamps file.
/// Checks for lack of framestamps file, or too many beats within framestamps.
/// </summary>
/// <returns>True is success and False is failure.</returns>
bool loadBeatsFromFile(const char* filePath, int* beats, int maxBeats, int* numBeatsLoaded);