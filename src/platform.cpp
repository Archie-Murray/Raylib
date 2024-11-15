#include "platform.hpp"
#include "raylib.h"
#include <filesystem>
#include <format>
#include <iostream>
#include <string>

static std::string currentFile = std::string();
static std::string path = std::filesystem::current_path().string();

#ifdef _WIN32
std::string FileTimeStamp() {
  SYSTEMTIME time;
  GetLocalTime(&time);
  char buffer[20];
  snprintf(buffer, sizeof(buffer), "%04d-%02d-%02d_%02d-%02d-%02d", time.wYear,
           time.wMonth, time.wDay, time.wHour, time.wMinute, time.wSecond);

  return std::string(buffer);
}
void copyLib() {
  std::string lastFile = std::string(currentFile);

  currentFile = std::format("game{}.dll", FileTimeStamp().c_str());
  try {
    std::filesystem::copy_file("game.dll", currentFile.c_str());
    if (!lastFile.empty()) {
      std::filesystem::remove(lastFile);
    }
  } catch (std::filesystem::filesystem_error &e) {
    std::cout << e.what() << "\n";
  }
}

#else
#include <dlfcn.h>
std::string FileTimeStamp() {
  time_t t = time(nullptr);
  struct tm *timeinfo = localtime(&t);

  char buffer[20];
  snprintf(buffer, sizeof(buffer), "%04d-%02d-%02d_%02d-%02d-%02d",
           timeinfo->tm_year + 1900, timeinfo->tm_mon + 1, timeinfo->tm_mday,
           timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec);

  return std::string(buffer);
}

void copyLib() {
  std::string lastFile = std::string(currentFile);

  currentFile =
      std::string(TextFormat("libgame%s.so", FileTimeStamp().c_str()));
  try {
    std::filesystem::copy_file("libgame.so", currentFile.c_str());
    TraceLog(LOG_INFO, TextFormat("Copied new lib: %s", currentFile.c_str()));
    if (!lastFile.empty()) {
      std::filesystem::remove(lastFile);
    }
  } catch (std::filesystem::filesystem_error &e) {
    TraceLog(LOG_ERROR, e.what());
  }
}

#endif

#ifdef _WIN32

GameLib LoadGameLibrary(GameAPI *gameAPI) {
  copyLib();
  GameLib gameLib = LoadLibraryA(currentFile.c_str());
  if (!gameLib) {
    // Handle error
    return nullptr;
  }

  gameAPI->createGame = (CreateGameFunc)GetProcAddress(gameLib, "CreateGame");
  gameAPI->startGame = (StartGameFunc)GetProcAddress(gameLib, "StartGame");
  gameAPI->updateGame = (UpdateGameFunc)GetProcAddress(gameLib, "UpdateGame");
  gameAPI->destroyGame =
      (DestroyGameFunc)GetProcAddress(gameLib, "DestroyGame");
  if (!gameAPI->createGame || !gameAPI->updateGame || !gameAPI->destroyGame ||
      !gameAPI->startGame) {
    return nullptr;
  } else {
    return gameLib;
  }
}

void FreeGameLibrary(GameLib gameLib) { FreeLibrary(gameLib); }

void DestroyLibraryFile() {
  TraceLog(LOG_INFO, std::format("Deleting file {}", currentFile).c_str());
  try {
    std::filesystem::remove(currentFile);
  } catch (std::filesystem::filesystem_error &e) {
    TraceLog(LOG_ERROR, e.what());
  }
}
#else
GameLib LoadGameLibrary(GameAPI *gameAPI) {
  copyLib();
  if (std::filesystem::exists(currentFile.c_str())) {
      TraceLog(LOG_INFO, "Lib file exists!");
  }
  GameLib gameLib = (GameLib)dlopen(currentFile.c_str(), RTLD_NOW);
  if (!gameLib) {
    TraceLog(LOG_ERROR,
             TextFormat("Could not load files because: %s", dlerror()));
    return nullptr;
  }

  gameAPI->createGame = (CreateGameFunc)dlsym(gameLib, "CreateGame");
  gameAPI->startGame = (StartGameFunc)dlsym(gameLib, "StartGame");
  gameAPI->updateGame = (UpdateGameFunc)dlsym(gameLib, "UpdateGame");
  gameAPI->destroyGame = (DestroyGameFunc)dlsym(gameLib, "DestroyGame");
  if (!gameAPI->createGame || !gameAPI->updateGame || !gameAPI->destroyGame) {
    return nullptr;
  } else {
    return gameLib;
  }
}

void FreeGameLibrary(GameLib gameLib) {
  if (!gameLib) {
    TraceLog(LOG_ERROR, "Tried to unload null library");
  }
  int close = dlclose(gameLib);
  if (close) {
    TraceLog(
        LOG_ERROR,
        TextFormat("Could not unload library %s, because: %s (error code %d)",
                   currentFile.c_str(), dlerror(), close));
  }
}

void DestroyLibraryFile() {
  TraceLog(LOG_INFO, std::format("Deleting file {}", currentFile).c_str());
  try {
    std::filesystem::remove(currentFile);
  } catch (std::filesystem::filesystem_error &e) {
    TraceLog(LOG_ERROR, e.what());
  }
}
#endif
