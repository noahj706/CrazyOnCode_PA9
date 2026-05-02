#pragma once
#include "entity.hpp"
#include <string>

#define WINNING_SCORE 5

class Scoreboard : public RectangleEntity
{
private:
    int score1;
    int score2;
    int fontSize;
    Color textColor;
    unsigned int winningScore;
    float addScoreCooldown;

public:
    Scoreboard(Vector2 pos = { 10, 10 }, int fontSize = 60,
        unsigned int numRounds = WINNING_SCORE);
    void draw() override;
    void update() override; 

    // Score methods
    void addScoreP1();
    void addScoreP2();
    void resetScore();

    // getters
    int getScore1() const;
    int getScore2() const;

    // void testUI();
    unsigned int foundWinner() const;


};