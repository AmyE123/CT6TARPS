#pragma once

#include "../Graphics/circle.h"
#include "../Audio/audio.h"
#include <nds.h>

#define HIT_RANGE 20

/// <summary>
/// Checks the player's touch position to see if it is within the hit range of the circle.
/// If it is, then the hit sound effect plays and the circle is cleared.
/// </summary>
/// <param name="touch">The current touch screen position where the player has tapped.</param>
/// <param name="hit">The hit sound effect when the circle is successfully hit.</param>
void checkTouch(touchPosition touch, mm_sound_effect hit);