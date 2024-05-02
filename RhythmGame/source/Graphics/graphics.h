#pragma once

#include <nds.h>

#define CIRCLE_RADIUS 30
#define CIRCLE_COLOR 1
#define SCREEN_WIDTH 256
#define SCREEN_HEIGHT 192

/// <summary>
/// Powers on just 2D hardware.
/// </summary>
void powerOnGraphics();

/// <summary>
/// Sets up the sub 2D engine video mode, sub is picked to be used as it is the default bottom screen.
/// The video mode that the bottom screen is set to is Mode 5, which is the most common mode, as it is the most flexible out of all modes. (2 Static layers + 2 Affine Extended layers.)
/// </summary>
void setupVideoMode();

/// <summary>
/// Sets bank C as the background memory (VRAM) for the sub (bottom) screen. C is picked as A and B are mostly used on the Main screen for the 3D engine.
/// </summary>
void setupVRAM();

/// <summary>
/// Initialises a background on the sub display. (Param documentation from libnds.devkitpro.org)
/// </summary>
/// <param name="layer">Background hardware layer to initialise. Must be 0 - 3.</param>
/// <param name="type">The type of background to initialize.</param>
/// <param name="size">The size of the background.</param>
/// <param name="mapBase">The 2k offset into vram the tile map will be placed or the 16k offset into vram the bitmap data will be placed for bitmap backgrounds.</param>
/// <param name="tileBase">The 16k offset into vram the tile graphics data will be placed.</param>
void initBackground(int layer, BgType type, BgSize size, int mapBase, int tileBase);

/// <summary>
/// Clears the screen to a specified colour.
/// </summary>
/// <param name="colour">The colour the screen should be cleared to.</param>
void clearScreen(u16 colour);

/// <summary>
/// Sets up the colour palette for drawing things like the rhythm circles.
/// </summary>
/// <param name="index">The index from BG_PALETTE_SUB to set the memory to.</param>
/// <param name="colour">The colour to set to memory.</param>
void setupPalette(u8 index, u16 colour);

/// <summary>
/// Gets the background layer variable (int).
/// </summary>
/// <returns>The background layer integer value.</returns>
int getBackgroundLayer();

/// <summary>
/// Initialises all graphics for the NDS.
/// </summary>
void initGraphics();

/// <summary>
/// Draws a circle on the screen. The circles are drawn by setting specific pixel colours.
/// </summary>
/// <param name="x">The x coordinate of where the circle should be drawn.</param>
/// <param name="y">The y coordinate of where the circle should be drawn.</param>
/// <param name="background">The background layer the circle should be drawn on.</param>
void drawCircle(int x, int y, int backgroundLayer);