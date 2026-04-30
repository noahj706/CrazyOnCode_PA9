#pragma once
#include "entity.hpp"
#include <string>

#define MAX_ROUNDS 15
#define FONT_SIZE 100
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
    Scoreboard(Vector2 pos = { 10, 10 }, int fontSize = FONT_SIZE,
        unsigned int numRounds = MAX_ROUNDS, 
        const char* fire = FIRE_SOUND_PATH, 
        const char* destroyed = DESTROYED_SOUND_PATH);
    ~Scoreboard();

    void loadSounds();
    void draw() override;
    void update() override; 

    // Score methods
    void addScoreP1();
    void addScoreP2();
    void resetScore();

    // audio methods for playing sounds of your choice
    void playFire(); 
    void playDestroyed();

    // getters
    int getScore1() const;
    int getScore2() const;

    //void testUI();
    unsigned int foundWinner() const;

    // Dyanamic map switching method
    Texture2D chooseMap(Texture2D woodTex, Texture2D poolTex);

};