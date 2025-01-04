#pragma once
#include "tower.hpp"
#include "raylib.h"
#include "raymath.h"
#include "sprites.hpp"
#include "game.hpp"
#include <cmath>

Rectangle RectangleFromVector(const Vector2& position, const Vector2& size) {
    return Rectangle { position.x, position.y, size.x, size.y };
}

void Tower::Init() {

};

void Tower::Render(Game* game) {
    DrawTexturePro(
        game->atlas, 
        sprites[sprite], 
        RectangleFromVector(position, Vector2Multiply(scale, GetSpriteSize(sprite))),
        Vector2Scale(GetSpriteSize(sprite), 0.5f),
        rotation, 
        WHITE
    );
};

void Tower::Update() {
    attackTimer -= GetFrameTime();
    if (attackTimer < 0.0f) {
        attackTimer += attackTime;
    }
}

void Tower::Destroy() {

}
