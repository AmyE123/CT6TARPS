#include "input.h"

void checkTouch(touchPosition touch, mm_sound_effect hit) {
    if (circles[0].active && abs(touch.px - circles[0].x) < 20 && abs(touch.py - circles[0].y) < 20) {
        consoleClear();

        mmEffectEx(&hit);
        deactivateCircle();
    }
}