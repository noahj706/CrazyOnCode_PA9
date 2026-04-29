#include "wall.hpp"

// ------------------------------------------------------------------------------------
// function to test wall display, this is called in main and will run the game loop for the wall test.
int Wall::drawWallDisplay()
{
    // Initialization
   //--------------------------------------------------------------------------------------
    const int screenWidth = 900;
    const int screenHeight = 500;

    InitWindow(screenWidth, screenHeight, "TestMap");

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

        ClearBackground(LIGHTGRAY);


        //Wall Wall1;
        Wall wall1;
        wall1.defaultArena1();

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

void Wall::defaultArena1()// 500 / 900
{   
    // I did not know how to do this without hardcoding the values.
    const int screenWidth = 900;
    const int screenHeight = 500;
	for (int i = 0; i < 18; i++)
    {   
        
        Wall wall1({i * WALL_SIZE,0}); //
        Wall wall2({i * WALL_SIZE,screenHeight - WALL_SIZE}); // bottom edge of screen
		wall1.draw();// top wall
        wall2.draw();// bottom wall
    }
    for (int i = 0; i < 10; i++)
    {   
        Wall wall3({ 0,50 + i * WALL_SIZE }); // 
        Wall wall4({ screenWidth - WALL_SIZE,50 + i * WALL_SIZE });
        wall3.draw();// left wall
        wall4.draw();// right wall
    }
}

void Wall::arenaFromfile(const char* filename)
{
    // get the "mapbse.tnkm" file.
    // walls = w
    // empty = E
    // playerspawn = @
    // 18 wide 900 devided by 50 = 18
    // 10 high 500 devided by 50 = 10

    //test map: WEE@EWWEEWEEEWW
    // getline 
	

}

void Wall::infile(const char* filename)
{
	fstream map;
    map.open("mapTest.tnkm");
    if (map == nullptr)
    {
		cout << "Error opening file: " << filename << endl;
    }
}


