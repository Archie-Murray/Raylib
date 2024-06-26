#ifndef GAME_HPP
#define GAME_HPP

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

EXTERNAL class GAME_API Game {
public:
    Game();
    ~Game();
    void Start(int fps);
    void Update();
    void Exit();
};

EXTERNAL GAME_API Game* CreateGame();
EXTERNAL GAME_API void DestroyGame(Game* game);
EXTERNAL GAME_API void UpdateGame(Game* game);
#endif // GAME_HPP
