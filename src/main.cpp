#include "raylib.h"
#include "game.hpp"
#include "platform.cpp"

int screenWidth = 1920;
int screenHeight = 1080;

int main() {
    GameAPI gameAPI = {};
    GameLib gameLib = LoadGameLibrary(&gameAPI);
    if (gameLib == nullptr) {
        TraceLog(LOG_ERROR, "Could not load game API");
        return -1;
    }
    Game* game = CreateGame();
    if (!game) {
        TraceLog(LOG_ERROR, "Could not create game!");
        FreeGameLibrary(gameLib);
        return -1;
    }
    InitWindow(screenWidth, screenHeight, "Raylib");
    game->Start(144);

    // Main game loop
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(WHITE);
        if (IsWindowReady()) {
          gameAPI.updateGame(game);
        } else {
          TraceLog(LOG_ERROR, "Window not ready!");
        }
        EndDrawing();
    }

    game->Exit();
    DestroyGame(game);
    FreeGameLibrary(gameLib);
}

