#include "UI.hpp"
#include "common.hpp"
#include <iostream>

Scoreboard::Scoreboard(Vector2 pos, int fontSize, unsigned int numRounds)
    : RectangleEntity(pos, 0, 0, 200, fontSize * 2 + 10)
    , score1(0)
    , score2(0)
    , fontSize(fontSize)
    , textColor(BLACK)
    , winningScore(numRounds)
{
}



void Scoreboard::draw()
{
    // No player details just scores, left being P1 score, right being P2 score
    // Refer to header for changing size of the scores with the new FONT_SIZE macro
    DrawText(std::to_string(score1).c_str(), position.x + 10, position.y, fontSize, textColor);
    // Now draws in the top-right corner
    DrawText(std::to_string(score2).c_str(), position.x + 1525, position.y, fontSize, textColor);
}

void Scoreboard::update() 
{
    if (addScoreCooldown > 0)
    {
        addScoreCooldown -= GetFrameTime();
    }
}

void Scoreboard::addScoreP1()
{
    if (addScoreCooldown <= 0)
    {
        score1++;
        addScoreCooldown = 0.5;
    }
}

void Scoreboard::addScoreP2()
{
    if (addScoreCooldown <= 0)
    {
        score2++;
        addScoreCooldown = 0.5;
    }
}

int Scoreboard::getScore1() const
{
    return score1;
}

int Scoreboard::getScore2() const
{
    return score2;
}
void Scoreboard::resetScore()
{
    score1 = 0;
    score2 = 0;
}

//void Scoreboard::testUI()
//{
//    // Initialize window
//    const int screenWidth = 1600;
//    const int screenHeight = 900;
//    InitWindow(screenWidth, screenHeight, "Scoreboard Demo");
//    InitAudioDevice(); // Make sure to place this before loadSounds()
//    //Texture2D woodTex = drawWood(); // Added for Custom Texture
//    loadSounds();
//    SetTargetFPS(60);
//
//    // Main game loop
//    while (!WindowShouldClose())
//    {
//        BeginDrawing();
//        ClearBackground(RAYWHITE);
//        //DrawTexture(woodTex, 0, 0, WHITE); // Texture Stuff
//        // Draw the scoreboard
//        draw();
//        
//        if (IsKeyPressed('T'))
//        {
//            addScoreP1();
//            playFire();
//        }
//        if (IsKeyPressed('Y'))
//        {
//            addScoreP2();
//            playDestroyed();
//        }
//
//        if (foundWinner() == 1)
//        {
//            std::cout << "Player 1 won!" << std::endl;
//            resetScore();
//        }
//        if (foundWinner() == 2)
//        {
//            std::cout << "Player 2 won!" << std::endl;
//            resetScore();
//        }
//
//        EndDrawing();
//    }
//
//    //UnloadTexture(woodTex); // Texture code fragment
//    CloseAudioDevice(); // Similarly to Initwindow having a CloseWindow(), InitAudioDevice has this
//    CloseWindow();
//}

// Use this to play fire sound example shown in testUI

unsigned int Scoreboard::foundWinner() const
{
    if (score1 >= winningScore)
    {
        return 1;
    }
    else if (score2 >= winningScore)
    {
        return 2;
    }
    return 0;
}

// Dynamic Background switching



