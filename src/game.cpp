#include "game.hpp"
#include "raylib.h"
#include "raymath.h"
#include <cmath>

Game::Game() {
    playerPos = {};
    // Initialization code (but do not initialize Raylib here)
}

Game::~Game() {
    // Cleanup code
}

void Game::Start(int fps, int width, int height) {
    TraceLog(LOG_INFO, TextFormat("Screen Size at Game::Start(): (%f, %f)", width, height));
    playerPos = {width * 0.5f, height * 0.5f};
    SetTargetFPS(fps);
}

void Game::Update() {
    // Update logic that uses Raylib functions
    DrawFPS(1800, 10);
    Vector2 input = {
        (float)(IsKeyDown(KEY_D) - IsKeyDown(KEY_A)),
        (float)(IsKeyDown(KEY_S) - IsKeyDown(KEY_W))
    };
    DrawText(TextFormat("Player Position: (%f, %f)", playerPos.x, playerPos.y), round(GetScreenWidth() * 0.8f), 10, 10, GREEN);
    input = Vector2Normalize(input);
    input = Vector2Scale(input, 175.0f * GetFrameTime());
    playerPos = Vector2Add(playerPos, input);
    // playerPos.x += input.x;
    // playerPos.y += input.y;
    DrawCircleV({playerPos.x, playerPos.y}, 40.0f, GREEN);
    // DrawRectangle(100, 10, 100, 100, RED);
}

void Game::Exit() {
    // Cleanup code
}

EXTERNAL Game* CreateGame() {
    return new Game();
}

EXTERNAL void StartGame(Game* game, int targetFPS, int width, int height) {
    game->Start(targetFPS, width, height);
}

EXTERNAL void UpdateGame(Game *game) {
    game->Update();
}

EXTERNAL void DestroyGame(Game* game) {
    delete game;
}
