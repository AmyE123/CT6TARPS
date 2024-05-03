#include "input.h"

void checkTouch(touchPosition touch, mm_sound_effect hit) {
    if (circles[0].active && abs(touch.px - circles[0].x) < HIT_RANGE && abs(touch.py - circles[0].y) < HIT_RANGE) {
        mmEffectEx(&hit);
        deactivateCircle();
    }
}