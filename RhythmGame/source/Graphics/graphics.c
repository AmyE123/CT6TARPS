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
	// Power on the 2D graphics engines
	powerOn(POWER_ALL_2D);

	// Setup the top screen for console output
	videoSetMode(MODE_0_2D);  // Mode 0 is used for text and uses less video memory
	vramSetBankA(VRAM_A_MAIN_BG);
	bgInit(0, BgType_Text4bpp, BgSize_T_256x256, 31, 0); // Initialise MAIN background for Mode 0, Text4bpp stands for 4 bits per pixel which is good for console text.
	consoleInit(NULL, 0, BgType_Text4bpp, BgSize_T_256x256, 31, 0, true, true); // Higher map base block numbers (like 31) means it is less likely to have been used by other parts of the game. Block 31 ensures the console's text doesn't overlap with graphical data.

	// Setup the bottom screen for game graphics
	videoSetModeSub(MODE_5_2D); // Mode 5 is the most flexible
	vramSetBankC(VRAM_C_SUB_BG);
	backgroundLayer = bgInitSub(3, BgType_Bmp16, BgSize_B16_256x256, 0, 0); // Initialise SUB background for Mode 5, using BgType_Bmp16 for 16-bit bitmap graphics
	u16* bgMem = bgGetGfxPtr(backgroundLayer);
	dmaFillWords(0xFFFF, bgMem, 256 * 256 * 2); // Clear the screen to white
	BG_PALETTE_SUB[1] = RGB15(0, 0, 0); // Set black color for circles
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