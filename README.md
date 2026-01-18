# Tile Rotation Puzzle

A 2D grid-based puzzle game developed with **Raylib (C++)** for the **SENG479 Game Programming** course.

---

## Gameplay
The player rotates tiles on a grid to match their correct orientations.  
When all tiles are aligned correctly, the level is completed and the next level unlocks.

---

## Controls
| Input | Action |
|------|--------|
| Mouse Left | Select tile |
| R | Rotate selected tile (90°) |
| Enter / Space | Start game / Next level |
| Backspace | Reset level |
| H | Toggle hint |
| Esc | Return to main menu |

---

## Levels
- **Level 1:** 3×3 grid (tutorial)
- **Level 2:** 4×4 grid
- **Level 3:** 5×5 grid
- **Level 4:** 6x6 grid (locked tiles introduced)
- **Level 5:** 7x7 grid (move-limit final challenge)

Difficulty increases by grid size and number of tiles.

---

##  Features
- Grid & Tile system (select / rotate / draw)
- Smooth 90° rotation animation
- Correct-orientation validation (solve check)
- Visual feedback (selected tile + correct tiles)
- Hint toggle (show correct rotations)
- Modular C++ architecture (separate game/grid/tile modules)
- Level progression (3x3 to 4x4 to 5x5 to 6x6 to 7x7)
- Level 4 rule: Locked tiles (cannot be selected/rotated, shown with red X)
- Level 5 rule: Move limit (exceeding the limit resets the level)
- 60 FPS fixed game loop
---

## Build & Run Instructions

### macOS
```bash
brew install raylib cmake
cmake -S . -B build
cmake --build build
./build/TileRotationPuzzle
```

### Windows (MSYS2 MinGW64)
```bash 
# In the MSYS2 MinGW64 terminal
pacman -S --needed mingw-w64-x86_64-toolchain mingw-w64-x86_64-cmake mingw-w64-x86_64-raylib

cmake -S . -B build -G "MinGW Makefiles"
cmake --build build
./build/TileRotationPuzzle.exe
```


---

## Development Notes
This project was developed incrementally with frequent Git commits to reflect a clean and traceable development process.  
The codebase is modular and organized across multiple source files following course guidelines.

---

### Architecture Overview
- Tile: Handles individual tile rotation state and correctness checks.
- Grid: Manages tile layout, user interaction, and grid-level validation.
- Puzzle: Evaluates the win condition by querying the Grid and determining
  whether the puzzle is solved.
- Game / UI: Handles game states, rendering, and player feedback.