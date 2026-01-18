# Game Design Document (GDD)
## Tile Rotation Puzzle

---

## 1. Game Overview
**Tile Rotation Puzzle** is a 2D grid-based puzzle game developed using Raylib (C++).
The player rotates tiles to match their correct orientations and complete each level.
The game focuses on logical thinking and pattern recognition.
Later levels introduce special constraints such as locked tiles and a move limit.

---

## 2. Genre
Puzzle

---

## 3. Target Platform
- Desktop (macOS, Windows)
- Keyboard + Mouse input

---

## 4. Core Gameplay Mechanics

### 4.1 Tile Selection
- Player selects a tile using the mouse.
- Selected tile is highlighted with a blue border.

### 4.2 Tile Rotation
- Pressing **R** rotates the selected tile by 90 degrees clockwise.
- Rotation includes a small animation for visual feedback.

### 4.3 Correct Orientation Check
- Each tile has a predefined correct rotation.
- When all tiles match their correct orientation, the level is completed.
- Hint mode (**H**) can optionally display each tile’s correct rotation for assistance/debugging.

### 4.4 Win Condition
- All tiles must be aligned correctly to finish the level.
- Completion triggers the Level Complete screen.

### 4.5 Locked Tiles (Level 4)
- Some tiles are locked and cannot be selected or rotated.
- Locked tiles are displayed with a red X overlay and are pre-aligned correctly.

### 4.6 Move Limit (Level 5)
- Level 5 introduces a move limit.
- Exceeding the move limit resets the level.

---

## 5. Game States
The game uses a state machine system:

- **Main Menu:** Start the game
- **Playing:** Active gameplay
- **Level Complete:** Level summary and progression

---

## 6. Level Design

### Level Progression
| Level | Grid Size | Difficulty |
|------|----------|------------|
| 1 | 3×3 | Easy (tutorial) |
| 2 | 4×4 | Medium |
| 3 | 5×5 | Hard |
| 4 | 6×6 | Hard+ (locked tiles introduced) |
| 5 | 7×7 | Final (move limit challenge) |

Difficulty increases with grid size and number of tiles.

---

## 7. Controls

| Input | Action |
|------|--------|
| Mouse Left | Select tile |
| R | Rotate tile |
| Enter / Space | Start / Next level |
| Backspace | Reset level |
| H | Toggle hint |
| Esc | Return to menu |

---

## 8. Visual and Audio Style
- Minimalist 2D design
- Clean geometric shapes
- Subtle animations for tile rotation
- Color feedback for correct/incorrect tiles
- (Optional) Sound effects for rotation and level completion

---

## 9. Technical Implementation
- Language: C++
- Framework: Raylib
- Build system: CMake
- Architecture: Modular multi-file structure
- Frame rate: Fixed at 60 FPS
- Version control: GitHub with incremental commits
- Grid system: **grid.h / grid.cpp** manages grid layout, selection logic, rotation calls, drawing, and solve-check iteration.
- Tile system: **tile.h / tile.cpp** defines tile data (current/correct rotation, selection state) and supports animated 90° rotation rendering.
- Special level rules: Level 4 uses locked tile indices; Level 5 enforces a move counter and move limit in the game loop.

---

## 10. Progression and Goals
The player's goal is to solve all levels with the minimum number of moves.
Each level increases complexity and encourages more efficient problem-solving.

---

## 11. Design Challenges and Solutions

### Challenge
Managing tile rotation states and detecting level completion efficiently.

### Solution
Each tile stores both current and correct rotation values.
A simple comparison loop checks for win condition after each move.
This approach ensures deterministic and fast validation without complex collision or physics systems.

---

## 12. Risks and Constraints
- Low technical risk (no physics, no AI, no collision detection)
- Deterministic gameplay logic
- High performance and stable FPS
- Simple input system reduces bugs

---

## 13. Future Improvements
- Additional levels
- Different tile themes (pipes, circuits, gears)
- Timer-based challenge mode
- Scoring system
- Sound and music polish
