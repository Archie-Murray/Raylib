#include "raylib.h"
#include "platform.cpp"

int screenWidth = 1920;
int screenHeight = 1080;

int main() {
    int reloadCount = 0;
    GameAPI gameAPI = {};
    GameLib gameLib = LoadGameLibrary(&gameAPI, reloadCount);
    if (gameLib == nullptr) {
        TraceLog(LOG_ERROR, "Could not load game API");
        return -1;
    }
    reloadCount++;
    Game* game = gameAPI.createGame();
    if (!game) {
        TraceLog(LOG_ERROR, "Could not create game!");
        FreeGameLibrary(gameLib);
        return -1;
    }
    InitWindow(screenWidth, screenHeight, "Raylib");
    SetTargetFPS(144);
    // Main game loop
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(WHITE);
        if (IsKeyPressed(KEY_R)) {
          FreeGameLibrary(gameLib);
          gameLib = LoadGameLibrary(&gameAPI, reloadCount);
          reloadCount++;
        }
        if (IsWindowReady()) {
          gameAPI.updateGame(game);
        } else {
          TraceLog(LOG_ERROR, "Window not ready!");
        }
        EndDrawing();
    }

    gameAPI.destroyGame(game);
    FreeGameLibrary(gameLib);
}

