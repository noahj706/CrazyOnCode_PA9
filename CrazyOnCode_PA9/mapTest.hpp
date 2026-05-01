#pragma once
#include "map.hpp"

void mapLayoutTest()
{
	// Initial window setupization
	InitWindow(SCREENWIDTH, SCREENHEIGHT, "Atari Combat + Wii Tanks Love Child");
	SetTargetFPS(60);

	Map map("wii1.tnkm");

	while (!WindowShouldClose())
	{
		//make window exist
		BeginDrawing();
		ClearBackground(BG_COLOR);

		map.draw();

		EndDrawing();
	}
}