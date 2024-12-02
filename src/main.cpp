#include "platform.hpp"
#include "raylib.h"

int main() {
    GameAPI gameAPI = {};
    GameLib gameLib = LoadGameLibrary(&gameAPI);
    if (!gameLib) {
        TraceLog(LOG_ERROR, "Could not load game API");
        return -1;
    }
    Game* game = gameAPI.createGame();
    if (!game) {
        TraceLog(LOG_ERROR, "Could not create game!");
        FreeGameLibrary(gameLib);
        return -1;
    }
    InitWindow(0, 0, "Raylib"); // Gives default of max screen size, will scale later
    int monitor = GetCurrentMonitor();
    int screenWidth = GetMonitorWidth(monitor) > 1920 ? 1920 : 1260;
    int screenHeight = GetMonitorHeight(monitor) > 1080 ? 1080 : 720;
    SetWindowSize(screenWidth, screenHeight);
    SetWindowPosition(GetMonitorWidth(monitor) / 2 - screenWidth / 2, GetMonitorHeight(monitor) / 2 - screenHeight / 2);
    gameAPI.startGame(game, 144, screenWidth, screenHeight);
    // Main game loop
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BLACK);
        bool doReload = IsKeyPressed(KEY_SPACE);
        DrawText(doReload ? "Reload pressed" : "Not reloading", 10, 10, 10, doReload ? RED : GREEN);
        if (doReload) {
            FreeGameLibrary(gameLib);
            TraceLog(LOG_INFO, "Reloading game lib...");
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
