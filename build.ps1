echo "Compile Started at:"
Get-Date -Format "HH:mm:ss"
dev-shell
cmake -S . -B ./build/ -GNinja
cp ./build/_deps/raylib-build/raylib/raylib.dll .
set-location ./build/
ninja
cp ./compile_commands.json ../
set-location ../
.\build\Raylib.exe
