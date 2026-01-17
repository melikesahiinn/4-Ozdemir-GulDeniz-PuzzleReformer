#include "levels.h"

static LevelDef MakeLevel(int n, int tileSize, std::vector<int> correct, std::vector<int> start) {
    LevelDef lvl;
    lvl.n = n;
    lvl.tileSize = tileSize;
    lvl.correct = std::move(correct);
    lvl.start = std::move(start);
    return lvl;
}

const std::vector<LevelDef>& GetAllLevels() {
    static std::vector<LevelDef> levels = {
        // Level 1 (3x3)
        MakeLevel(3, 120,
            {0,1,2, 1,2,3, 2,3,0},
            {1,1,2, 0,3,3, 2,0,1}
        ),
        // Level 2 (4x4)
        MakeLevel(4, 90,
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
        // Level 3 (5x5)
        MakeLevel(5, 75,
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
        )
    };
    return levels;
}
