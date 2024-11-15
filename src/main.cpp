#include "platform.cpp"
#include "raylib.h"

int screenWidth = 1920;
int screenHeight = 1080;

int main() {
    GameAPI gameAPI = {};
    GameLib gameLib = LoadGameLibrary(&gameAPI);
    if (gameLib == nullptr) {
        TraceLog(LOG_ERROR, "Could not load game API");
        return -1;
    }
    Game *game = gameAPI.createGame();
    if (!game) {
        TraceLog(LOG_ERROR, "Could not create game!");
        FreeGameLibrary(gameLib);
        return -1;
    }
    InitWindow(screenWidth, screenHeight, "Raylib");
    gameAPI.startGame(game, 144);
    // Main game loop
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BLACK);
        if (IsKeyPressed(KEY_R)) {
            FreeGameLibrary(gameLib);
            gameLib = LoadGameLibrary(&gameAPI);
        }
        gameAPI.updateGame(game);
        EndDrawing();
    }
    gameAPI.destroyGame(game);
    FreeGameLibrary(gameLib);
    DestroyLibraryFile();
    CloseWindow();
}
