cmake_minimum_required(VERSION 3.24) # FetchContent is available in 3.11+
project(Raylib)

if (CMAKE_SYSTEM_NAME STREQUAL "Darwin")
  error("MacOS is not supported")
endif()

# Generate compile_commands.json
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON CACHE INTERNAL "") # works
set(CMAKE_CXX_STANDARD 20)

# Set Raylib to be built as a shared library globally
set(BUILD_SHARED_LIBS FORCE ON)
set(FETCHCONTENT_QUIET OFF)
# Find or Fetch Raylib
if(NOT TARGET raylib)
    include(FetchContent)
    FetchContent_Declare(
        raylib
        GIT_REPOSITORY https://github.com/raysan5/raylib.git
        GIT_TAG 5.0 # Replace with the desired version
    )
    # Fetch Raylib
    FetchContent_MakeAvailable(raylib)
endif()

# Windows
if (CMAKE_SYSTEM_NAME STREQUAL "Windows")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -I\"C:/Program Files (x86)/Windows Kits/10/Include/10.0.22621.0/um\"")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -I\"C:/Program Files (x86)/Windows Kits/10/Include/10.0.22621.0/shared\"")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -I\"C:/Program Files (x86)/Windows Kits/10/Include/10.0.22621.0/ucrt\"")
elseif (UNIX AND NOT APPLE)
    target_compile_definitions(game_only PRIVATE PLATFORM_LINUX)
    target_compile_definitions(${PROJECT_NAME} PRIVATE PLATFORM_LINUX)
    target_link_libraries(game_only PRIVATE pthread)
    target_link_libraries(${PROJECT_NAME} PRIVATE pthread)
endif()

# Main
add_executable(${PROJECT_NAME} ./src/main.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE raylib)

# Game dynamic library for hot reloading
add_library(game SHARED ./src/game.cpp)
target_compile_definitions(game PRIVATE GAME_EXPORTS)
target_link_libraries(game PRIVATE raylib)

# Custom post-build step for copying Raylib shared library after building the main project (MyGame)
if(WIN32)
    # Path to the compiled Raylib DLL on Windows
    set(RAYLIB_DLL_PATH "${CMAKE_BINARY_DIR}/_deps/raylib-build/raylib/raylib.dll")

    # Copy Raylib DLL after building the main project (MyGame)
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${RAYLIB_DLL_PATH}"
        "${CMAKE_BINARY_DIR}"
        COMMENT "Copying Raylib DLL to ${CMAKE_BINARY_DIR} executable directory"
    )
elseif(UNIX)
    # Path to the compiled Raylib shared library on Linux
    set(RAYLIB_SO_PATH "${CMAKE_BINARY_DIR}/_deps/raylib-build/raylib/libraylib.so")

    # Copy Raylib shared library after building the main project (MyGame)
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${RAYLIB_SO_PATH}"
        "${CMAKE_BINARY_DIR}"
        COMMENT "Copying Raylib shared library to ${CMAKE_BINARY_DIR} executable directory"
    )
endif()

# Custom target to build only the game library
add_custom_target(game_only
  DEPENDS game
  COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR} --target game
)
