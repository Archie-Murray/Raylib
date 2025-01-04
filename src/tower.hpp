#pragma once
#include "raylib.h"
#include "sprites.hpp"

class Game;

class Tower {
    float attackTime = 0.5f;
    float attackTimer = 0.0f;
    SpriteID sprite = SpriteID::Tower;
    Vector2 position;
    Vector2 scale = { 1, 1 };
    float rotation;

public:
    Tower() { position = { (float) GetScreenWidth() * 0.5f, (float) GetScreenHeight() * 0.25f }; };
    virtual void Init();
    virtual void Update();
    virtual void Render(Game* game);
    virtual void Destroy();
};
