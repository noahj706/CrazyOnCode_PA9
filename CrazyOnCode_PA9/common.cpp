#include "common.hpp"

// Used before game loop
Texture2D drawWood()
{
    return LoadTexture("AtariWood.png");
}
Texture2D drawPool()
{
    return LoadTexture("AtariPool.png");
}

// Frees GPU VRAM, should be placed after game loop
void unloadWood(Texture2D background)
{
    UnloadTexture(background); 
}
void unloadPool(Texture2D background2)
{
    UnloadTexture(background2);
}