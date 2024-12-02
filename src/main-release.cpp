#include "game.hpp"
#include "raylib.h"

int main() {
    Game game = Game();
    InitWindow(0, 0, "Raylib"); // Gives default of max screen size, will scale later
    int monitor = GetCurrentMonitor();
    int screenWidth = GetMonitorWidth(monitor) > 1920 ? 1920 : 1260;
    int screenHeight = GetMonitorHeight(monitor) > 1080 ? 1080 : 720;
    SetWindowSize(screenWidth, screenHeight);
    SetWindowPosition(GetMonitorWidth(monitor) / 2 - screenWidth / 2, GetMonitorHeight(monitor) / 2 - screenHeight / 2);
    game.Start(144, screenWidth, screenHeight);
    // Main game loop
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BLACK);
        game.Update();
        EndDrawing();
    }
    game.Exit();
    CloseWindow();
}
