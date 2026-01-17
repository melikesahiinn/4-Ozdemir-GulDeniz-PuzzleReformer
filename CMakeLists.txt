cmake_minimum_required(VERSION 3.16)
project(TileRotationPuzzle LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(raylib REQUIRED)

add_executable(TileRotationPuzzle
    src/main.cpp
    src/game.cpp
    src/grid.cpp
    src/levels.cpp
    src/ui.cpp
    src/audio.cpp
)

target_include_directories(TileRotationPuzzle PRIVATE src)
target_link_libraries(TileRotationPuzzle PRIVATE raylib)

if(APPLE)
  target_link_libraries(TileRotationPuzzle PRIVATE "-framework IOKit" "-framework Cocoa" "-framework OpenGL" "-framework CoreVideo")
endif()

add_custom_command(TARGET TileRotationPuzzle POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${CMAKE_SOURCE_DIR}/assets
            $<TARGET_FILE_DIR:TileRotationPuzzle>/assets
)
