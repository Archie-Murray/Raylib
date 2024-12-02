## COMPIILE MAIN:
```sh
clang++ -o main.exe .\src\main-release.cpp .\src\game.cpp -I .\raylib-win\include\ .\raylib-win\lib\raylib.lib -lmsvcrt -lshell32 -luser32 -lopengl32 -lwinmm -lgdi32 -nostdlib -std=c++20 -O3 -w
```

## COMPILE MAIN DEBUG:
```sh
clang++ -o main.exe .\src\main.cpp .\src\platform.cpp -I .\raylib-win\include\ .\raylib-win\lib\raylibdll.lib -lmsvcrt -lshell32 -luser32 -lopengl32 -lwinmm -lgdi32 -nostdlib -std=c++20
```

## COMPILE GAME LIB
```sh
clang++ -o game.dll -shared -v .\src\game.cpp -I .\raylib-win\include\ .\raylib-win\lib\raylibdll.lib -lmsvcrt -lshell32 -luser32 -lopengl32 -lwinmm -lgdi32 -nostdlib -std=c++20 -DGAME_EXPORTS
```
