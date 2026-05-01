// Hewwo, this is misc. stuff that give the game some sound and more visuals so backgrounds,
// sound effects, background music, and maybe menu system...we'll see
// In the process of testing all assets, and organizing if working

#ifndef COMMON_HPP
#define COMMON_HPP
#include "raylib.h"
#include <string>
#include <vector>
#define SCREENWIDTH 1600
#define SCREENHEIGHT 900
#define BG_COLOR {137, 195, 71, 255}
// UI Bar in pixels
#define UI_BAR_HEIGHT 68;
// Arena height in tiles
#define PLAY_TILE_HEIGHT 13;
// Arena width in tiles
#define PLAY_TILE_WIDTH 25;
// Recall tiles take up 64 x 64 pixels


class Stage
{
private:
    Texture2D currentBackground;
    Texture2D wallTexture;
    std::string currentMapName;

public:
    Stage() : currentBackground{ 0 }, wallTexture{ 0 }, currentMapName("") {}

    ~Stage()
    {
        if (currentBackground.id != 0) UnloadTexture(currentBackground);
        if (wallTexture.id != 0) UnloadTexture(wallTexture);
    }

    // Load background based on map name
    void loadTheme(const std::string& mapName)
    {
        // Unload previous textures
        if (currentBackground.id != 0) UnloadTexture(currentBackground);
        if (wallTexture.id != 0) UnloadTexture(wallTexture);

        currentMapName = mapName;

        // Load appropriate theme based on map name
        if (mapName.find("pool") != std::string::npos)
        {
            currentBackground = LoadTexture("assets/pool.png");
            wallTexture = LoadTexture("assets/pool_ball.png");  // Pool ball for obstacles
        }
        else if (mapName.find("wii") != std::string::npos)
        {
            currentBackground = LoadTexture("assets/wii3.png");
            wallTexture = LoadTexture("assets/wii_block.png");  // Wii block for obstacles
        }
        else if (mapName.find("pingpong") != std::string::npos)
        {
            currentBackground = LoadTexture("assets/pool2.png");
            wallTexture = LoadTexture("assets/pingpong_ball.png");  // Ping pong ball
        }
        else  // Default theme
        {
            currentBackground = LoadTexture("assets/wii.png");
            wallTexture = LoadTexture("assets/brick.png");  // Brick texture
        }
    }

    Texture2D getWallTexture() const 
    { 
        return wallTexture; 
    }

    void drawBackground()
    {
        if (currentBackground.id != 0)
        {
            DrawTexturePro(currentBackground,
                { 0, 0, (float)currentBackground.width, (float)currentBackground.height },
                { 0, 0, (float)SCREENWIDTH, (float)SCREENHEIGHT },
                { 0, 0 }, 0, WHITE);
        }
        else
        {
            ClearBackground(BG_COLOR);
        }
    }

    void unload()
    {
        if (currentBackground.id != 0) UnloadTexture(currentBackground);
        if (wallTexture.id != 0) UnloadTexture(wallTexture);
    }
};

// Sound Manager class

class SoundManager
{
private:
    Sound shootSound;
    Sound explodeSound;
    Sound bounceSound;
    Sound shootv2Sound;
    Music backgroundMusic;
    bool musicEnabled;
    bool musicLoaded;  // Track if music is loaded

public:
    SoundManager() : musicEnabled(true), musicLoaded(false) {}

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

    // Load music separately (call this when ready)
    void loadMusic(const char* musicPath)
    {
        if (musicLoaded)
        {
            UnloadMusicStream(backgroundMusic);
        }
        backgroundMusic = LoadMusicStream(musicPath);
        musicLoaded = true;

        if (musicEnabled)
        {
            PlayMusicStream(backgroundMusic);
        }
    }

    void playFire() { PlaySound(shootSound); }
    void playExplosion() { PlaySound(explodeSound); }
    void playBounce() { PlaySound(bounceSound); }
    void playBulletHit() { PlaySound(shootv2Sound); }

    void updateMusic()
    {
        if (musicLoaded && musicEnabled)
        {
            UpdateMusicStream(backgroundMusic);
        }
    }

    void toggleMusic()
    {
        if (!musicLoaded) return;

        musicEnabled = !musicEnabled;
        if (musicEnabled)
        {
            ResumeMusicStream(backgroundMusic);
        }
        else
        {
            PauseMusicStream(backgroundMusic);
        }
    }

    void setMusicEnabled(bool enabled)
    {
        if (!musicLoaded) return;

        musicEnabled = enabled;
        if (musicEnabled)
        {
            ResumeMusicStream(backgroundMusic);
        }
        else
        {
            PauseMusicStream(backgroundMusic);
        }
    }

    bool isMusicEnabled() const { return musicEnabled; }
    bool isMusicLoaded() const { return musicLoaded; }

    void unload()
    {
        UnloadSound(shootSound);
        UnloadSound(explodeSound);
        UnloadSound(bounceSound);
        UnloadSound(shootv2Sound);
        if (musicLoaded)
        {
            UnloadMusicStream(backgroundMusic);
        }
        CloseAudioDevice();
    }
};

#endif