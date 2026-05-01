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
    std::string currentMapName;

public:
    Stage() : currentBackground{ 0 }, currentMapName("") {}

    ~Stage()
    {
        if (currentBackground.id != 0)
            UnloadTexture(currentBackground);
    }

    // Load background based on map name
    void loadBackgroundForMap(const std::string& mapName)
    {
        // Unload previous background
        if (currentBackground.id != 0)
        {
            UnloadTexture(currentBackground);
            currentBackground.id = 0; // Resets texture ID
        }

        currentMapName = mapName;

        // Load appropriate background based on map filename
        if (mapName.find("wii") != std::string::npos ||
            mapName.find("Wii") != std::string::npos)
        {
            currentBackground = LoadTexture("assets/Wii3.png");
        }
        else if (mapName.find("pool") != std::string::npos ||
            mapName.find("Pool") != std::string::npos)
        {
            currentBackground = LoadTexture("assets/pool.png");
        }
        else if (mapName.find("atari") != std::string::npos ||
            mapName.find("Atari") != std::string::npos)
        {
            currentBackground = LoadTexture("assets/pool2.png");
        }
        else
        {
            // Default background
            currentBackground.id = 0;
        }
    }

    void draw()
    {
        if (currentBackground.id != 0)
        {
            DrawTexturePro(
                currentBackground,
                Rectangle{ 0, 0, (float)currentBackground.width, (float)currentBackground.height },
                Rectangle{ 0, 0, (float)SCREENWIDTH, (float)SCREENHEIGHT},
                Vector2{ 0, 0 },
                0,
                WHITE
            );
        }
        else
        {
           // clear with background color if there is no texture
            ClearBackground(BG_COLOR);
        }
    }

    void unload()
    {
        if (currentBackground.id != 0)
        {
            UnloadTexture(currentBackground);
            currentBackground.id = 0;
        }
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