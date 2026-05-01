#include "common.hpp"
/*
Stage::Stage()
{
    currentBackground = { 0 };
}

void Stage::drawWii()
{
    if (currentBackground.id != 0) 
    {
        UnloadTexture(currentBackground);
    }
    currentBackground = LoadTexture("WiiWood.png");
    DrawTexture(currentBackground, 0, 0, WHITE);   
}

void Stage::drawPool()
{
    if (currentBackground.id != 0) 
    {
        UnloadTexture(currentBackground);
    }
    currentBackground = LoadTexture("AtariPool.png");
    DrawTexture(currentBackground, 0, 0, WHITE);
}

void Stage::unloadWii()
{
    if (currentBackground.id != 0) 
    {
        UnloadTexture(currentBackground);
        currentBackground = { 0 };
    }
}

void Stage::unloadPool()
{
    if (currentBackground.id != 0) 
    {
        UnloadTexture(currentBackground);
        currentBackground = { 0 };
    }
}
*/

void playFire() 
{
    static Sound sound = LoadSound("assets/shoot.wav");
    PlaySound(sound);
}

void playDestroyed() 
{
    static Sound sound =  LoadSound("assets/explode.wav");
    PlaySound(sound);
}
