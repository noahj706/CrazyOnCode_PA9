#pragma once
#include "entity.hpp"
#include <string>

#define MAX_ROUNDS 15
#define FONT_SIZE 100

class Scoreboard : public RectangleEntity
{
private:
    int score1;
    int score2;
    int fontSize;
    Color textColor;
    unsigned int numRounds;
public:
    Scoreboard(Vector2 pos = { 10, 10 }, int fontSize = FONT_SIZE,
        unsigned int numRounds = MAX_ROUNDS);
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

    // Dyanamic map switching method


};