#include "wall.hpp"

// ------------------------------------------------------------------------------------
// function to test wall display, this is called in main and will run the game loop for the wall test.
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
        wall1.defaultArena();

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

void Wall::defaultArena()
{
	for (int i = 0; i < 16; i++)
    {
        Wall wall1({i*WALL_SIZE,0});
        Wall wall2({i*WALL_SIZE,450-WALL_SIZE});
        Wall wall3({ 0,i * WALL_SIZE });
        Wall wall4({ 800 - WALL_SIZE,i * WALL_SIZE });
        wall1.draw();
        wall2.draw();
        wall3.draw();
        wall4.draw();
    }
}


