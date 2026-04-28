#pragma once
#include "entity.hpp"
#include <string>

#define MAX_ROUNDS 15

class Scoreboard : public RectangleEntity
{
private:
    int score1;
    int score2;
    int fontSize;
    Color textColor;
    unsigned int numRounds;

public:
    Scoreboard(Vector2 pos = { 10, 10 }, int fontSize = 20,
        unsigned int numRounds = MAX_ROUNDS);

    void draw() override;
    void update() override; 
    void addScoreP1();
    void addScoreP2();
    void resetScore();
    void testUI();

    int getScore1() const;
    int getScore2() const;
    unsigned int foundWinner() const;

};