#include "platform.hpp"
#include <format>
#include <iostream>
#include <filesystem>
#include <string>

static std::string currentFile = std::string();
static std::string path = std::filesystem::current_path().string();

void copyLib() {
    time_t now;
    time(&now);
    std::tm _tm;
    char buf[sizeof "2024-06-11T00-56-02"];
    gmtime_s(&_tm, &now);
    strftime(buf, sizeof buf, "%FT%H-%M-%S", &_tm);
    std::string lastFile = std::string(currentFile);
    
    currentFile = std::format("game{}.dll", buf);
    try {
      std::filesystem::copy_file("game.dll", currentFile.c_str());
      if (!lastFile.empty()) {
          std::filesystem::remove(lastFile);
      }
    } catch (std::filesystem::filesystem_error& e) {
      std::cout << e.what() << "\n";
    }
}

#ifdef _WIN32

GameLib LoadGameLibrary(GameAPI* gameAPI) {
    copyLib();
    GameLib gameLib = LoadLibraryA(currentFile.c_str());
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
