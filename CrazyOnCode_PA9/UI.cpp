#include "UI.hpp"
#include <iostream>

Scoreboard::Scoreboard(Vector2 pos, int fontSize, unsigned int numRounds)
    : RectangleEntity(pos, 0, 0, 200, fontSize * 2 + 10)
    , score1(0)
    , score2(0)
    , fontSize(fontSize)
    , textColor(BLACK)
    , numRounds(numRounds)
{
}

void Scoreboard::draw()
{
    DrawText("Player 1:", position.x, position.y, fontSize, textColor);
    DrawText(std::to_string(score1).c_str(), position.x + 120, position.y, fontSize, textColor);

    // Draws Player 2 below player 1
    DrawText("Player 2:", position.x, position.y + fontSize + 5, fontSize, textColor);
    DrawText(std::to_string(score2).c_str(), position.x + 120, position.y + fontSize + 5, fontSize, textColor);
}

void Scoreboard::update() 
{

}

void Scoreboard::addScoreP1()
{
    score1++;
}

void Scoreboard::addScoreP2()
{
    score2++;
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

void Scoreboard::testUI()
{
    // Initialize window
    const int screenWidth = 800;
    const int screenHeight = 600;
    InitWindow(screenWidth, screenHeight, "Scoreboard Demo");
    SetTargetFPS(60);

    // Main game loop
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        // Draw the scoreboard
        draw();
        if (IsKeyPressed('T'))
        {
            addScoreP1();
        }
        if (IsKeyPressed('Y'))
        {
            addScoreP2();
        }

        if (foundWinner() == 1)
        {
            std::cout << "Player 1 won!" << std::endl;
            resetScore();
        }
        if (foundWinner() == 2)
        {
            std::cout << "Player 2 won!" << std::endl;
            resetScore();
        }

        EndDrawing();
    }

    CloseWindow();
}

unsigned int Scoreboard::foundWinner() const
{
    if (score1 >= numRounds)
    {
        return 1;
    }
    else if (score2 >= numRounds)
    {
        return 2;
    }
    return 0;
}

