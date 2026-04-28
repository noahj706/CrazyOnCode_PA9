/*
Programmer: Noah Julius, Angelo Reyes, Walker [LASTNAME], Lincoln Young
Title: Atari Combat Recreation / PA9
Description: Local 2 player pvp with tanks, first to 15 wins
*/

#include "raylib.h"

/*******************************************************************************************
*
*   raylib [shapes] example - colors palette
*
*   Example complexity rating: [★★☆☆] 2/4
*
*   Example originally created with raylib 1.0, last time updated with raylib 2.5
*
*   Example licensed under an unmodified zlib/libpng license, which is an OSI-certified,
*   BSD-like license that allows static linking with closed source software
*
*   Copyright (c) 2014-2025 Ramon Santamaria (@raysan5)
*
********************************************************************************************/

#include "raylib.h"
#include "walltest.hpp"
#include "wall.hpp"
//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
	Wall testwall;
	testwall.drawWall();

    return 0;
}