#include "raylib.h"

int screenWidth = 1920;
int screenHeight = 1080;

int main() {
  InitWindow(screenWidth, screenHeight, "Raylib");
  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(RED);
    EndDrawing();
  }
  CloseWindow();
  return 0;
}
