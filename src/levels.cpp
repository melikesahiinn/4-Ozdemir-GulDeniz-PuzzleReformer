#include "levels.h"

// Yardımcı fonksiyon: Level oluşturma
static LevelDef MakeLevel(
    int n,
    int tileSize,
    std::vector<int> correct,
    std::vector<int> start,
    std::vector<int> lockedTiles = {},
    int moveLimit = -1,
    bool hintEnabled = true
) {
    LevelDef lvl;
    lvl.n = n;
    lvl.tileSize = tileSize;
    lvl.correct = std::move(correct);
    lvl.start = std::move(start);
    lvl.lockedTiles = std::move(lockedTiles);
    lvl.moveLimit = moveLimit;
    lvl.hintEnabled = hintEnabled;
    return lvl;
}

const std::vector<LevelDef>& GetAllLevels() {
    static std::vector<LevelDef> levels = {

        // -------- Level 1 (3x3) --------
        MakeLevel(
            3, 120,
            {0,1,2, 1,2,3, 2,3,0},
            {1,1,2, 0,3,3, 2,0,1}
        ),

        // -------- Level 2 (4x4) --------
        MakeLevel(
            4, 90,
            {
                0,1,2,3,
                1,2,3,0,
                2,3,0,1,
                3,0,1,2
            },
            {
                2,1,0,3,
                1,0,3,1,
                2,2,1,0,
                0,3,2,2
            }
        ),

        // -------- Level 3 (5x5) --------
        MakeLevel(
            5, 75,
            {
                0,1,2,3,0,
                1,2,3,0,1,
                2,3,0,1,2,
                3,0,1,2,3,
                0,1,2,3,0
            },
            {
                1,2,0,3,2,
                0,2,1,1,3,
                3,0,2,0,1,
                1,3,0,2,2,
                2,1,3,1,0
            }
        ),

        // -------- Level 4 (6x6 – Locked Tiles) --------
        MakeLevel(
            6, 65,
            {
                0,1,2,3,0,1,
                1,2,3,0,1,2,
                2,3,0,1,2,3,
                3,0,1,2,3,0,
                0,1,2,3,0,1,
                1,2,3,0,1,2
            },
            {
                2,0,1,3,2,1,
                1,3,0,2,1,0,
                0,2,3,1,0,2,
                3,1,2,0,3,1,
                1,0,3,2,1,3,
                2,3,1,0,2,0
            },
            // locked tiles: köşeler + orta 2x2
            { 0, 5, 30, 35, 14, 15, 20, 21 }
        ),

        // -------- Level 5 (7x7 – Move Limit) --------
        MakeLevel(
            7, 55,
            {
                0,1,2,3,0,1,2,
                1,2,3,0,1,2,3,
                2,3,0,1,2,3,0,
                3,0,1,2,3,0,1,
                0,1,2,3,0,1,2,
                1,2,3,0,1,2,3,
                2,3,0,1,2,3,0
            },
            {
                1,3,0,2,1,0,3,
                2,0,1,3,2,3,0,
                3,1,2,0,1,2,1,
                0,2,3,1,0,1,2,
                2,3,1,0,3,0,1,
                1,0,2,3,2,1,0,
                3,2,0,1,0,3,2
            },
            {},     // lockedTiles
            98,     // moveLimit
            false   // hintEnabled
        )
    };

    return levels;
}
