#pragma once
#include "raylib.h"
enum SpriteID { Tower, Projectile, Count };

typedef Rectangle Sprite;
static Sprite sprites[Count] = {
    { 0, 0, 16, 16 },
    { 16, 0, 16, 16 } 
};

inline Vector2 GetSpriteSize(SpriteID sprite) {
    return Vector2 { sprites[sprite].width, sprites[sprite].height };
}
