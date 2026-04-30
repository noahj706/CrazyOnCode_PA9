#include "raylib.h"

// Note: AtariWood.png must be in the working directory
Texture2D drawWood() 
{
    // LoadTexture must be called AFTER InitWindow()
    Texture2D background = LoadTexture("AtariPool.png");
    // Draw texture at specific coordinates (x, y, tint)
    DrawTexture(background, 1600, 900, WHITE);
    return background;
}

bool unloadWood(Texture2D background) 
{
    UnloadTexture(background); // Free GPU VRAM
    return true;
}