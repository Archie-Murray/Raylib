#ifndef GAME_HPP
#define GAME_HPP

#include "raylib.h"
#include <vector>
#define EXTERNAL extern "C"
#ifdef _WIN32
  #ifdef GAME_EXPORTS
    #define GAME_API __declspec(dllexport)
  #else
    #define GAME_API __declspec(dllimport)
  #endif
#else
  #define GAME_API
#endif

class Tower;
EXTERNAL class GAME_API Game {
public:
    Vector2 playerPos;
    Texture2D atlas;
    std::vector<class Tower*> towers;

    Game();
    ~Game();
    void Start(int fps, int width, int height);
    void Update();
    void Exit();
};

EXTERNAL GAME_API Game* CreateGame();
EXTERNAL GAME_API void StartGame(Game* game, int targetFPS, int width, int height);
EXTERNAL GAME_API void DestroyGame(Game* game);
EXTERNAL GAME_API void UpdateGame(Game* game);
#endif // GAME_HPP
