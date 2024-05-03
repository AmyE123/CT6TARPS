#include "audio.h"
#include "soundbank.h"
#include "soundbank_bin.h"

mm_sound_effect hit = {
    { SFX_HITSOUND },           // id
    (int)(1.0f * (1 << 10)),    // rate
    0,                          // handle
    255,                        // volume
    255                         // panning
};

mm_sound_effect music = {
    { SFX_MUSIC },
    (int)(1.0f * (1 << 10)),    // rate
    0,                          // handle
    100,                        // volume
    255                         // panning
};

void initAudio() {
    soundEnable();

    mmInitDefaultMem((mm_addr)soundbank_bin);

    mmLoadEffect(SFX_HITSOUND);
    mmLoadEffect(SFX_MUSIC);

    // Play music once at game start
    mmEffectEx(&music);
}

void playHitSoundEffect() {
    mmEffectEx(&hit);
}