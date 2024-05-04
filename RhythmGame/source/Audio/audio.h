#pragma once

#include <maxmod9.h>
#include <nds.h>

extern mm_sound_effect hit;
extern mm_sound_effect music;

/// <summary>
/// Initialise all audio and load all effects.
/// </summary>
void initAudio();

/// <summary>
/// Play a hit sound effect.
/// </summary>
/// <param name="index">The hit sound effect wanted. 1 to 5 only.</param>
void playHitSoundEffect(int index);