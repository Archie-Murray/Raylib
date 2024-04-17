dev-shell
cmake -S . -B ./build/ -GNinja
set-location ./build/
ninja
set-location ../
.\build\Raylib.exe
