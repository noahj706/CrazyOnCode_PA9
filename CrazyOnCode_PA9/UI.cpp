#include "UI.hpp"

// Example of setting up the scoreboard in main cpp
//#include "UI.hpp" 
//#include "raylib.h"
//
//int main() {
//    // Window initialization
//    InitWindow(800, 600, "Scoreboard Example");
//    SetTargetFPS(60);
//
//    // Create scoreboard with default position and font size
//    Scoreboard scoreboard;
//
//    // Or create with custom position and font size
//    // Scoreboard scoreboard({50, 30}, 30);
//
//    while (!WindowShouldClose()) 
//    {
//        // Game logic - add scores
//        if (IsKeyPressed(KEY_A)) 
//        {
//            scoreboard.addScore(true);   // Player 1 scores
//        }
//        if (IsKeyPressed(KEY_L)) {
//            scoreboard.addScore(false);  // Player 2 scores
//        }
//
//        // Check for winner
//        if (scoreboard.hasWinner(5)) 
//        {  // First to 5 wins
//            // Handle game over
//            if (IsKeyPressed(KEY_R)) 
//            {
//                scoreboard.resetScore();
//            }
//        }
//
//        // Drawing
//        BeginDrawing();
//        ClearBackground(RAYWHITE);
//
//        scoreboard.draw();  // Draw the scoreboard
//
//        EndDrawing();
//    }
//
//    CloseWindow();
//    return 0;
//}