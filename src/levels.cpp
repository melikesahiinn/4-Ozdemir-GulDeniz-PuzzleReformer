#include "levels.h"

static LevelDef MakeLevel(
    int n,
    int tileSize,
    std::vector<int> correct,
    std::vector<int> start,
    std::vector<int> locked = {},
    int moveLimit = -1,
    bool hintEnabled = true
) {
    LevelDef lvl;
    lvl.n = n;
    lvl.tileSize = tileSize;
    lvl.correct = std::move(correct);
    lvl.start = std::move(start);
    lvl.lockedTiles = std::move(locked);
    lvl.moveLimit = moveLimit;
    lvl.hintEnabled = hintEnabled;
    return lvl;
}

const std::vector<LevelDef>& GetAllLevels() {
    static std::vector<LevelDef> levels = {

        MakeLevel(
            3, 120,
            {0,1,2, 1,2,3, 2,3,0},
            {1,1,2, 0,3,3, 2,0,1}
        ),

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
    
            {
                0, 5, 30, 35,     
                14, 15, 20, 21    
            },
            -1,
            true
        ),

        
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
            {},
            98,     
            false   
        )
    };

    return levels;
}
