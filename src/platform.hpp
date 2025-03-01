#ifdef _WIN32
#define NOGDI  // All GDI defines and routines
#define NOUSER // All USER defines and routines
#undef near
#undef far

#define WIN32_LEAN_AND_MEAN
#include "Windows.h"
typedef HMODULE GameLib;
#else
#include <ctime>
#include <dlfcn.h>
typedef void* GameLib;
#endif

#include "game.hpp"

typedef Game *(*CreateGameFunc)();
typedef void (*StartGameFunc)(Game *, int, int, int);
typedef void (*UpdateGameFunc)(Game *);
typedef void (*DestroyGameFunc)(Game *);

struct GameAPI {
    CreateGameFunc createGame;
    StartGameFunc startGame;
    UpdateGameFunc updateGame;
    DestroyGameFunc destroyGame;
};

GameLib LoadGameLibrary(GameAPI *gameAPI);
void FreeGameLibrary(GameLib gameLib);
void DestroyLibraryFile();
