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

mm_sound_effect hitclap1 = {
	{ SFX_HITCLAP1 },           // id
	(int)(1.0f * (1 << 10)),    // rate
	0,                          // handle
	255,                        // volume
	255                         // panning
};

mm_sound_effect hitclap2 = {
	{ SFX_HITCLAP2 },           // id
	(int)(1.0f * (1 << 10)),    // rate
	0,                          // handle
	255,                        // volume
	255                         // panning
};

mm_sound_effect hitclap3 = {
	{ SFX_HITCLAP3 },           // id
	(int)(1.0f * (1 << 10)),    // rate
	0,                          // handle
	255,                        // volume
	255                         // panning
};

mm_sound_effect hitclap4 = {
	{ SFX_HITCLAP4 },           // id
	(int)(1.0f * (1 << 10)),    // rate
	0,                          // handle
	255,                        // volume
	255                         // panning
};

mm_sound_effect hitclap5 = {
	{ SFX_HITCLAP5 },           // id
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
	mmLoadEffect(SFX_HITCLAP1);
	mmLoadEffect(SFX_HITCLAP2);
	mmLoadEffect(SFX_HITCLAP3);
	mmLoadEffect(SFX_HITCLAP4);
	mmLoadEffect(SFX_HITCLAP5);
	mmLoadEffect(SFX_MUSIC);

	// Play music once at game start
	mmEffectEx(&music);
}

void playHitSoundEffect(int index) {
	switch (index) {
	case 1:
		mmEffectEx(&hitclap1);
		break;
	case 2:
		mmEffectEx(&hitclap2);
		break;
	case 3:
		mmEffectEx(&hitclap3);
		break;
	case 4:
		mmEffectEx(&hitclap4);
		break;
	case 5:
		mmEffectEx(&hitclap5);
		break;
	default:
		mmEffectEx(&hit);
	}
}