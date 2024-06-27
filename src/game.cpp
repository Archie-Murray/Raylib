#include "game.hpp"
#include "raylib.h"

Game::Game() {
    // Initialization code (but do not initialize Raylib here)
}

Game::~Game() {
    // Cleanup code
}

void Game::Start(int fps) {
    // SetTargetFPS(fps);
}

void Game::Update() {
    // Update logic that uses Raylib functions
    DrawFPS(10, 10);
    DrawRectangle(1700, 100, 200, 400, GREEN);
    DrawRectangle(100, 100, 200, 400, BLUE);
}

void Game::Exit() {
    // Cleanup code
}

EXTERNAL Game* CreateGame() {
    return new Game();
}

EXTERNAL void UpdateGame(Game *game) {
    game->Update();
}

EXTERNAL void DestroyGame(Game* game) {
    delete game;
}
