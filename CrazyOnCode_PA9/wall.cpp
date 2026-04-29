#include "wall.hpp"

int Wall::drawWallDisplay()
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


        //Wall Wall1;
        Wall wall1;
        wall1.draw();

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------
	return 0;
}

Wall::Wall(const Vector2& position, const float& angle, const float& speed, const float& width, const float& height)
    : RectangleEntity(position, angle, speed, width, height) {};

Wall::~Wall()
{
}

void Wall::update()
{
}
void Wall::draw()
{
     
     DrawRectangleRec(getBounds(), BROWN);
}
