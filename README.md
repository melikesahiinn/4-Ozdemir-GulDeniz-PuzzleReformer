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

Difficulty increases by grid size and number of tiles.

---

##  Features
- Grid-based rotation puzzle system
- Multiple difficulty levels
- Smooth tile rotation animation
- Visual feedback for correct tiles
- Move counter and hint system
- Modular C++ architecture
- 60 FPS fixed game loop
---

## Build & Run Instructions

### macOS
```bash
brew install raylib cmake
cmake -S . -B build
cmake --build build
./build/TileRotationPuzzle

---

## Development Notes
This project was developed incrementally with frequent Git commits to reflect a clean and traceable development process.  
The codebase is modular and organized across multiple source files following course guidelines.