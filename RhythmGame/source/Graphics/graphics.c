#include "graphics.h"

int background;

/// <summary>
/// Powers on just 2D hardware.
/// </summary>
void powerOnGraphics() {
    powerOn(POWER_ALL_2D);
}

/// <summary>
/// Sets up the sub 2D engine video mode, sub is picked to be used as it is the default bottom screen.
/// The video mode that the bottom screen is set to is Mode 5, which is the most common mode, as it is the most flexible out of all modes. (2 Static layers + 2 Affine Extended layers.)
/// </summary>
void setupVideoMode() {
    videoSetModeSub(MODE_5_2D);
}

/// <summary>
/// Sets bank C as the background memory (VRAM) for the sub (bottom) screen. C is picked as A and B are mostly used on the Main screen for the 3D engine.
/// </summary>
void setupVRAM() {
    vramSetBankC(VRAM_C_SUB_BG);
}

/// <summary>
/// Initialises a background on the sub display
/// </summary>
int initBackground(int layer, BgType type, BgSize size, int mapBase, int tileBase) {
    background = bgInitSub(layer, type, size, mapBase, tileBase);
}

/// <summary>
/// Clears the screen to a specified colour.
/// </summary>
void clearScreen(u16 colour) {    
    dmaFillWords(colour, bgGetGfxPtr(background), 256 * 256 * 2);
}

// Sets up the colour palette for drawing things like the rhythm circles.
void setupPalette(u8 index, u16 colour) {
    BG_PALETTE_SUB[index] = colour;
}

/// <summary>
/// Initialises all graphics for the NDS.
/// </summary>
void initGraphics() {
    powerOnGraphics();
    setupVideoMode();
    setupVRAM();

    // Initialize background for Mode 5, Layer 3 is chosen (0 - 3) as the rhythm circles should be overlays and on top of eveyrthing. 
    // BgType_Bmp16 is used for 16-bit bitmap graphics of the form aBBBBBGGGGGRRRRR. BgSize_B16_256x256 is used as it is 256 x 256 pixel 16 bit bitmap background.
    initBackground(3, BgType_Bmp16, BgSize_B16_256x256, 0, 0);

    // RGB15 is a macro to convert 5 bit r g b components into a single 15 bit RGB triplet.
    // RGB15 allows 32 levels of each primary colour (0 to 31) meaning this RGB15 colour represents white in RGB555.
    clearScreen(RGB15(31, 31, 31));

    // Sets colour index 1 to black.
    setupPalette(1, RGB15(0, 0, 0));
}

void drawCircle(int x, int y, int background) {
    // Implementation
}

void clearAndDrawBackground() {
    // Implementation
}