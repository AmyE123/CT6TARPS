#pragma once

#include <nds.h>
#include <stdio.h>

#define CIRCLE_RADIUS 30
#define CIRCLE_COLOR 1

/// <summary>
/// Gets the background layer variable (int).
/// </summary>
/// <returns>The background layer integer value.</returns>
int getBackgroundLayer();

/// <summary>
/// Sets up the main engine video mode. Main is picked for the top screen as sub is the default bottom screen.
/// The video mode that the top screen is set to is Mode 0, which is used for text and was chosen as it uses less video memory.
/// Sets bacnk A as the background memory for the main screen. A is picked as it is the first VRAM bank, and is avaliable for the main screen.
/// Initialises a main background for mode 0.
/// Initialises the console for debug text.
/// </summary>
void setupTopScreen();

/// <summary>
/// Sets up the sub 2D engine video mode, sub is picked to be used as it is the default bottom screen.
/// The video mode that the bottom screen is set to is Mode 5, which is the most common mode, as it is the most flexible out of all modes. (2 Static layers + 2 Affine Extended layers.)
/// Sets bank C as the background memory (VRAM) for the sub (bottom) screen. C is picked as A and B are mostly used on the Main screen for the 3D engine.
/// Initialises a background on the sub display.
/// Clears the screen to white and set black color for circles.
/// </summary>
void setupBottomScreen();

/// <summary>
/// Initialises all graphics for the NDS.
/// </summary>
void initGraphics();

/// <summary>
/// Clears the screen.
/// </summary>
void clearScreen();

/// <summary>
/// Draws a circle on the screen. The circles are drawn by setting specific pixel colours.
/// </summary>
/// <param name="x">The x coordinate of where the circle should be drawn.</param>
/// <param name="y">The y coordinate of where the circle should be drawn.</param>
/// <param name="background">The background layer the circle should be drawn on.</param>
void drawCircle(int x, int y, int backgroundLayer);