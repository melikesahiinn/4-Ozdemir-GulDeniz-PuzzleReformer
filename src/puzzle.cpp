#include "puzzle.h"

bool Puzzle::CheckWin(const Grid& grid) {
    return grid.IsSolved();
}