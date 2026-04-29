#pragma once
#include "entity.hpp"
#include <string>

#define MAX_ROUNDS 15
constexpr const char* FIRE_SOUND_PATH = "smoke.wav";
constexpr const char* DESTROYED_SOUND_PATH = "destroyed.wav";

class Scoreboard : public RectangleEntity
{
private:
    int score1;
    int score2;
    int fontSize;
    Color textColor;
    unsigned int numRounds;
    Sound fire;
    Sound destroyed;
    const char* firePath;
    const char* destroyedPath;
    bool soundsLoaded;
public:
    Scoreboard(Vector2 pos = { 10, 10 }, int fontSize = 20,
        unsigned int numRounds = MAX_ROUNDS, 
        const char* fire = FIRE_SOUND_PATH, 
        const char* destroyed = DESTROYED_SOUND_PATH);
    ~Scoreboard();

    void loadSounds();
    void draw() override;
    void update() override; 
    void addScoreP1();
    void addScoreP2();
    void resetScore();
    void testUI();
    void playFire();
    void playDestroyed();


    int getScore1() const;
    int getScore2() const;
    unsigned int foundWinner() const;

};