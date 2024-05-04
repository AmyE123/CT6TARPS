#pragma once
#include <stdbool.h>

/// <summary>
/// Load the beats from the timestamps file.
/// Checks for lack of timestamps file, or too many beats within timestamps.
/// </summary>
/// <returns>True is success and False is failure.</returns>
bool loadBeatsFromFile(const char* filePath, int* beats, int maxBeats, int* numBeatsLoaded);