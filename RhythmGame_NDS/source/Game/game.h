#pragma once

#include "../Graphics/circle.h"
#include "../Input/input.h"
#include <nds.h>

/// <summary>
/// This code updates the gameplay loop.
/// </summary>
/// <param name="gameTime">The current game time (in frames).</param>
/// <param name="circles">The array of circles.</param>
void updateGameLoop(int* gameTime, Circle circles[]);