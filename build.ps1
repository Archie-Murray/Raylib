echo "Compile Started at:"
Get-Date -Format "HH:mm:ss"
dev-shell
cmake -S . -B ./build/ -GNinja
set-location ./build/
cp ./_deps/raylib-build/raylib/raylib.dll .
ninja
cp ./compile_commands.json ../
set-location ../
.\build\Raylib.exe
