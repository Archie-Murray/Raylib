#include "game.hpp"
#include "raylib.h"
#include "raymath.h"

Game::Game() {
    playerPos = {};
    // Initialization code (but do not initialize Raylib here)
}

Game::~Game() {
    // Cleanup code
}

void Game::Start(int fps) {
    playerPos = {GetScreenWidth() * 0.5f, GetScreenHeight() * 0.5f};
    SetTargetFPS(fps);
}

void Game::Update() {
    // Update logic that uses Raylib functions
    DrawFPS(1800, 10);
    Vector2 input = {
        (float)(IsKeyDown(KEY_D) - IsKeyDown(KEY_A)),
        (float)(IsKeyDown(KEY_S) - IsKeyDown(KEY_W))
    };
    input = Vector2Normalize(input);
    input = Vector2Scale(input, 175.0f * GetFrameTime());
    playerPos = Vector2Add(playerPos, input);
    // playerPos.x += input.x;
    // playerPos.y += input.y;
    DrawRectangleRec({playerPos.x, playerPos.y, 40.0f, 40.0f}, RED);
}

void Game::Exit() {
    // Cleanup code
}

EXTERNAL Game* CreateGame() {
    return new Game();
}

EXTERNAL void StartGame(Game* game, int targetFPS) {
    game->Start(targetFPS);
}

EXTERNAL void UpdateGame(Game *game) {
    game->Update();
}

EXTERNAL void DestroyGame(Game* game) {
    delete game;
}
