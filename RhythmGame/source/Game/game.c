#include "game.h"
#include "../Graphics/circle.h"
#include "../Graphics/graphics.h"
#include "../Input/input.h"
#include "../Audio/audio.h"
#include "../Assembly/asm_functions.h"

static unsigned short prevKeys = 0;

void updateGameLoop(int* gameTime, Circle circles[]) {    
    unsigned short currentKeys = read_keys_asm();
    unsigned short justPressed = currentKeys & (currentKeys ^ prevKeys);
    
    scanKeys();
    touchPosition touch;
    touchRead(&touch);

    if (keysHeld() & KEY_TOUCH) {
        checkTouch(touch, hit);
    }

    if (justPressed & KEY_UP) {
        playHitSoundEffect(1);
    }

    if (justPressed & KEY_DOWN) {
        playHitSoundEffect(2);
    }

    if (justPressed & KEY_LEFT) {
        playHitSoundEffect(3);
    }

    if (justPressed & KEY_RIGHT) {
        playHitSoundEffect(4);
    }

    if (justPressed & KEY_R || justPressed & KEY_L) {
        playHitSoundEffect(5);
    }

    // Update previous keys state at the end of the frame
    prevKeys = currentKeys;

    // Handle circle appearance based on pre-defined beats
    if (!circles[0].active && circles[0].nextAppearIndex < MAX_BEATS && *gameTime == circles[0].appearTimes[circles[0].nextAppearIndex]) {
        repositionAndActivateCircle(0);
    }

    // Check to deactivate circle
    if (circles[0].active && *gameTime >= circles[0].disappearTime) {
        deactivateCircle();
    }

    // Only draw the circle if it's active
    if (circles[0].active) {
        drawCircle(circles[0].x, circles[0].y, getBackgroundLayer());
    }
    else {
        clearScreen();
    }

    swiWaitForVBlank(); // Sync with the vertical blank
    (*gameTime)++; // Increment the game timer
}