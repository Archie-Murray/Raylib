dev-shell
cmake -S . -B ./build/ -GNinja
set-location ./build/
ninja
cp ./compile_commands.json ../
set-location ../
.\build\Raylib.exe
