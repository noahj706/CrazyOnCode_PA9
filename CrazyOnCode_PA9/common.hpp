// Hewwo, this is misc. stuff that give the game some sound and more visuals so backgrounds,
// sound effects, background music, and maybe menu system...we'll see
// In the process of testing all assets, and organizing if working
// Author: Angelo Reyes


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
    std::vector<Texture2D> wallTextures;  // Multi-use textures
    Texture2D wallTexture;         // Single-use texture
    std::string currentMapName;

public:
    Stage() : currentBackground{ 0 }, wallTexture{ 0 }, currentMapName(" ") {}

    ~Stage() 
    {
        if (currentBackground.id != 0) UnloadTexture(currentBackground);
        if (wallTexture.id != 0) UnloadTexture(wallTexture);
        for (auto& texture : wallTextures) 
        {
            if (texture.id != 0) UnloadTexture(texture);
        }
    }

    Texture2D getWallTexture() const 
    {
        return wallTexture;
    }

    Texture2D getRandomWallTexture() 
    {
        if (wallTextures.empty()) 
        {
            return wallTexture;
        }
        return wallTextures[rand() % wallTextures.size()];
    }

    Texture2D getPrimaryWallTexture() const 
    {
        return wallTexture;
    }

    void loadTheme(const std::string& mapName) 
    {
        // Unload previous textures
        if (currentBackground.id != 0) UnloadTexture(currentBackground);
        if (wallTexture.id != 0) UnloadTexture(wallTexture);
        for (auto& texture : wallTextures) 
        {
            if (texture.id != 0) UnloadTexture(texture);
        }
        wallTextures.clear();

        // Map selection
        // Assigns each stage their respesctive textures
        currentMapName = mapName;

        if (mapName.find("pooltwo") != std::string::npos ||
            mapName.find("pool2") != std::string::npos) 
        {
            currentBackground = LoadTexture("assets/pool2.png");
            wallTexture = LoadTexture("assets/ping_pong.png");
        }
        else if (mapName.find("pool") != std::string::npos) 
        {
            currentBackground = LoadTexture("assets/pool.png");
            wallTextures.push_back(LoadTexture("assets/pool_balls00.png"));
            wallTextures.push_back(LoadTexture("assets/pool_balls01.png"));
            wallTextures.push_back(LoadTexture("assets/pool_balls02.png"));
            wallTextures.push_back(LoadTexture("assets/pool_balls03.png"));
            wallTextures.push_back(LoadTexture("assets/pool_balls04.png"));
            wallTextures.push_back(LoadTexture("assets/pool_balls05.png"));
            wallTextures.push_back(LoadTexture("assets/pool_balls06.png"));
            wallTextures.push_back(LoadTexture("assets/pool_balls07.png"));
            wallTextures.push_back(LoadTexture("assets/pool_balls08.png"));
            wallTextures.push_back(LoadTexture("assets/pool_balls09.png"));
            wallTextures.push_back(LoadTexture("assets/pool_balls10.png"));
            wallTextures.push_back(LoadTexture("assets/pool_balls11.png"));
            wallTextures.push_back(LoadTexture("assets/pool_balls12.png"));
            wallTextures.push_back(LoadTexture("assets/pool_balls13.png"));
            wallTextures.push_back(LoadTexture("assets/pool_balls14.png"));
            wallTextures.push_back(LoadTexture("assets/pool_balls15.png"));

            wallTextures.push_back(LoadTexture("assets/pool_ball.png"));
            wallTextures.push_back(LoadTexture("assets/poolball2.png"));
            wallTextures.push_back(LoadTexture("assets/poolball3.png"));
            wallTextures.push_back(LoadTexture("assets/poolball4.png"));
            wallTextures.push_back(LoadTexture("assets/poolball5.png"));
        }
        else if (mapName.find("wii") != std::string::npos) 
        {
            currentBackground = LoadTexture("assets/wii3.png");
            wallTexture = LoadTexture("assets/woodblock.png");
        }
        else if (mapName.find("atari2") != std::string::npos)
        {
            currentBackground = LoadTexture("assets/3A.png");
            wallTexture = LoadTexture("assets/ataritext.png");
        }
        else 
        {
            currentBackground = LoadTexture("assets/wii2.png");
            wallTexture = LoadTexture("assets/seashell1.png");
        }
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
        for (auto& texture : wallTextures) 
        {
            if (texture.id != 0) UnloadTexture(texture);
        }
        wallTextures.clear();
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

    bool isMusicEnabled() const 
    { 
        return musicEnabled; 
    }
    bool isMusicLoaded() const 
    { 
        return musicLoaded; 
    }

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