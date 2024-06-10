cmake_minimum_required(VERSION 3.24) # FetchContent is available in 3.11+
project(Raylib)

# Generate compile_commands.json
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON CACHE INTERNAL "") # works
set(CMAKE_CXX_STANDARD 20)
# Dependencies
set(RAYLIB_VERSION 5.0)
find_package(raylib ${RAYLIB_VERSION} QUIET) # QUIET or REQUIRED
if (NOT raylib_FOUND) # If there's none, fetch and build raylib
  include(FetchContent)
  FetchContent_Declare(
    raylib
    DOWNLOAD_EXTRACT_TIMESTAMP OFF
    URL https://github.com/raysan5/raylib/archive/refs/tags/${RAYLIB_VERSION}.tar.gz
  )
  FetchContent_GetProperties(raylib)
  if (NOT raylib_POPULATED) # Have we downloaded raylib yet?
    set(FETCHCONTENT_QUIET NO)
    FetchContent_Populate(raylib)
    set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE) # don't build the supplied examples
    add_subdirectory(${raylib_SOURCE_DIR} ${raylib_BINARY_DIR})
  endif()
endif()

# Windows moment
if (CMAKE_SYSTEM_NAME STREQUAL "Windows")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -I\"C:/Program Files (x86)/Windows Kits/10/Include/10.0.22621.0/um\"")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -I\"C:/Program Files (x86)/Windows Kits/10/Include/10.0.22621.0/shared\"")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -I\"C:/Program Files (x86)/Windows Kits/10/Include/10.0.22621.0/ucrt\"")
endif()
# Our Project
add_executable(${PROJECT_NAME} ./src/main.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE raylib game)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

# Game dynamic library for hot reloading
add_library(game SHARED ./src/game.cpp)
target_compile_definitions(game PRIVATE GAME_EXPORTS)
target_link_libraries(game PRIVATE raylib)


