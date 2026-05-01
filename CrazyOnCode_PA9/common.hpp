// Hewwo, this is misc. stuff that give the game some sound and more visuals so backgrounds,
// sound effects, background music, and maybe menu system...we'll see
// In the process of testing all assets, and organizing if working

#ifndef COMMON_HPP
#define COMMON_HPP

//constexpr const char* FIRE_SOUND_PATH = "assets/shoot.wav";
//constexpr const char* DESTROYED_SOUND_PATH = "assets/explode.wav";

#include "raylib.h"
// UI Bar in pixels
#define UI_BAR_HEIGHT 68;
// Arena height in tiles
#define PLAY_TILE_HEIGHT 13;
// Arena width in tiles
#define PLAY_TILE_WIDTH 25;
// Recall tiles take up 64 x 64 pixels

/*

class Stage 
{
private:
    Texture2D currentBackground;

public:
    Stage();

    Texture2D drawWii();
    // Texture2D drawWII();
    Texture2D drawPool();
    // Texture2D drawPOOL();
    // Texture2D drawAtari();
    // Texture2D drawATARI();

    void unloadWii(Texture2D background);
    // void unloadWII(Texture2D background3);
    void unloadPool(Texture2D background2);
    // void unloadPOOL(Texture2D background4);
    // void unloadAtari(Texture background5);
    // void unloadATARI(Texture background6);

};
*/
// Sound Manager class

class SoundManager
{
private:
    Sound shootSound;
    Sound explodeSound;
    Sound bounceSound;
    Sound shootv2Sound;

public:
    void init()
    {
        InitAudioDevice();
        if (IsAudioDeviceReady()) 
        {
            shootSound = LoadSound("assets/shoot.wav");
            explodeSound = LoadSound("assets/explode.wav");
            bounceSound = LoadSound("assets/bounce.wav");
            shootv2Sound = LoadSound("assets/shootv2.wav");
        }
    }

    void playFire() 
    { 
        PlaySound(shootSound); 
    }
    void playExplosion() 
    { 
        PlaySound(explodeSound); 
    }
    void playBounce() 
    { 
        PlaySound(bounceSound); 
    }
    void playBulletHit() 
    { 
        PlaySound(shootv2Sound); 
    }

    void unload()
    {
        UnloadSound(shootSound);
        UnloadSound(explodeSound);
        UnloadSound(bounceSound);
        UnloadSound(shootv2Sound);
        CloseAudioDevice();
    }


};


#endif