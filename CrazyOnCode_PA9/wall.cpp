#include "wall.hpp"

int Wall::drawWall()
{
    // Initialization
   //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        // TODO: Update your variables here
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

        ClearBackground(RAYWHITE);

		//DrawRectangle(0, 0, WALL_SIZE, WALL_SIZE, BROWN);
        //DrawRectangle(0+WALL_SIZE, 0, WALL_SIZE, WALL_SIZE, BROWN);

        Wall Wall1;

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------
	return 0;
}

Wall::Wall()
{
    for (int i = 0; i < 20; i++)
    {
		DrawRectangle(i * WALL_SIZE, 0, WALL_SIZE, WALL_SIZE, BROWN);

    }
}

Wall::~Wall()
{
}
