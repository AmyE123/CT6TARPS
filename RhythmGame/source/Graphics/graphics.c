#include "graphics.h"
#include "../utils.h"

int backgroundLayer;

void setupTopScreen() {
	videoSetMode(MODE_0_2D);  // Mode 0 is used for text and uses less video memory
	vramSetBankA(VRAM_A_MAIN_BG);
	bgInit(0, BgType_Text4bpp, BgSize_T_256x256, 31, 0); // Initialise MAIN background for Mode 0, Text4bpp stands for 4 bits per pixel which is good for console text.
	consoleInit(NULL, 0, BgType_Text4bpp, BgSize_T_256x256, 31, 0, true, true);
}

void setupBottomScreen() {
	videoSetModeSub(MODE_5_2D); // Mode 5 is the most flexible
	vramSetBankC(VRAM_C_SUB_BG);
	backgroundLayer = bgInitSub(3, BgType_Bmp16, BgSize_B16_256x256, 0, 0); // Initialise SUB background for Mode 5, using BgType_Bmp16 for 16-bit bitmap graphics
	u16* bgMem = bgGetGfxPtr(backgroundLayer);
	dmaFillWords(0xFFFF, bgMem, 256 * 256 * 2); // Clear the screen to white
	BG_PALETTE_SUB[1] = RGB15(0, 0, 0); // Set black color for circles
}

int getBackgroundLayer() {
	return backgroundLayer;
}

void initGraphics() {
	// Power on the 2D graphics engines
	powerOn(POWER_ALL_2D);

	setupTopScreen();
	setupBottomScreen();
}

void clearScreen() {
	u16* videoMemory = bgGetGfxPtr(backgroundLayer);
	dmaFillWords(0xFFFF, videoMemory, SCREEN_WIDTH * SCREEN_HEIGHT * sizeof(u16)); // Fill screen with white
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