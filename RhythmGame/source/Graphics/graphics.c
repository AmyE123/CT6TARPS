#include "graphics.h"
#include "../utils.h"

int backgroundLayer;

void powerOnGraphics() {
	powerOn(POWER_ALL_2D);
}

void setupVideoMode() {
	videoSetModeSub(MODE_5_2D);
}

void setupVRAM() {
	vramSetBankC(VRAM_C_SUB_BG);
}

void initBackground(int layer, BgType type, BgSize size, int mapBase, int tileBase) {
	backgroundLayer = bgInitSub(layer, type, size, mapBase, tileBase);
}

void clearScreen() {
	u16* videoMemory = bgGetGfxPtr(backgroundLayer);
	dmaFillWords(0xFFFF, videoMemory, SCREEN_WIDTH * SCREEN_HEIGHT * sizeof(u16)); // Fill screen with white
	// Optionally redraw any static background elements here
}

void setupPalette(u8 index, u16 colour) {
	BG_PALETTE_SUB[index] = colour;
}

int getBackgroundLayer() {
	return backgroundLayer;
}

void initGraphics() {
	//powerOnGraphics();
	//setupVideoMode();
	//setupVRAM();

	//// Initialize background for Mode 5, Layer 3 is chosen (0 - 3) as the rhythm circles should be overlays and on top of eveyrthing. 
	//// BgType_Bmp16 is used for 16-bit bitmap graphics of the form aBBBBBGGGGGRRRRR. BgSize_B16_256x256 is used as it is 256 x 256 pixel 16 bit bitmap background.
	//initBackground(3, BgType_Bmp16, BgSize_B16_256x256, 0, 0);

	//// RGB15 is a macro to convert 5 bit r g b components into a single 15 bit RGB triplet.
	//// RGB15 allows 32 levels of each primary colour (0 to 31) meaning this RGB15 colour represents white in RGB555.
	//clearScreen(RGB15(31, 31, 31));

	//// Sets colour index 1 to black.
	//setupPalette(1, RGB15(0, 0, 0));

	powerOn(POWER_ALL_2D); // Ensure all 2D engines are powered on

	// Set up the video mode for the bottom screen
	videoSetModeSub(MODE_5_2D);
	vramSetBankC(VRAM_C_SUB_BG);

	// Initialize background for Mode 5, using BgType_Bmp16 for 16-bit bitmap graphics
	backgroundLayer = bgInitSub(3, BgType_Bmp16, BgSize_B16_256x256, 0, 0);

	// Clear the screen to white
	u16* bgMem = bgGetGfxPtr(backgroundLayer);
	dmaFillWords(0xFFFF, bgMem, 256 * 256 * 2); // 0xFFFF represents white color in RGB555

	// Set black color for circles
	BG_PALETTE_SUB[1] = RGB15(0, 0, 0); // Color index 1 to black
}

void drawCircle(int x, int y, int bgLayer) {
	// Pointer to background graphics.
	u16* videoMemory = bgGetGfxPtr(bgLayer);

	// The nested loops check every point around the center.
	for (int dx = -CIRCLE_RADIUS; dx <= CIRCLE_RADIUS; dx++) {
		for (int dy = -CIRCLE_RADIUS; dy <= CIRCLE_RADIUS; dy++) {
			// Checks if the current point is inside the circle.
			if (dx * dx + dy * dy <= CIRCLE_RADIUS * CIRCLE_RADIUS) {
				// These integers calculate the corrdinates on the screen where the pixel needs to be.
				int posX = x + dx;
				int posY = y + dy;

				// This condition makes sure the pixel is on the screen and not outside the display area.
				if (posX >= 0 && posX < SCREEN_WIDTH && posY >= 0 && posY < SCREEN_HEIGHT) {
					// This sets the colour of the pixel at the calculated position to the predfined circle colour.
					videoMemory[posY * SCREEN_WIDTH + posX] = CIRCLE_COLOR;
				}
			}
		}
	}
}