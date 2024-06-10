#include "platform.hpp"
#ifdef _WIN32
GameLib LoadGameLibrary(GameAPI* gameAPI) {
    GameLib gameLib = (GameLib) LoadLibraryA("game.dll");
    if (!gameLib) {
        // Handle error
        return nullptr;
    }
  
    gameAPI->createGame = (CreateGameFunc)GetProcAddress(gameLib, "CreateGame");
    gameAPI->updateGame = (UpdateGameFunc)GetProcAddress(gameLib, "UpdateGame");
    gameAPI->destroyGame = (DestroyGameFunc)GetProcAddress(gameLib, "DestroyGame");
    if (!gameAPI->createGame || !gameAPI->updateGame || !gameAPI->destroyGame) {
      return nullptr;
    } else {
      return gameLib;
    }
}

void FreeGameLibrary(GameLib gameLib) {
    FreeLibrary(gameLib);
}
#else
GameLib LoadGameLibrary(GameAPI* gameAPI) {
    GameLib gameLib = (GameLib) dlopen("game.so");
    if (!gameLib) {
        // Handle error
        return gameLib;
    }
  
    gameAPI->createGame = (CreateGameFunc)dysm(gameLib, "CreateGame");
    gameAPI->updateGame = (UpdateGameFunc)dysm(gameLib, "UpdateGame");
    gameAPI->destroyGame = (DestroyGameFunc)dysm(gameLib, "DestroyGame");
    if (!gameAPI->createGame || !gameAPI->updateGame || !gameAPI->destroyGame) {
      return nullptr;
    } else {
      return gameLib;
    }
}

void FreeGameLibrary(GameLib gameLib) {
    FreeLibrary(gameLib);
}
#endif

