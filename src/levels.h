#pragma once
#include <vector>

struct LevelDef {
    int n = 3;
    int tileSize = 100;

    std::vector<int> correct; 
    std::vector<int> start;  

    std::vector<int> lockedTiles; /
    int moveLimit = -1;        
    bool hintEnabled = true;    
};
const std::vector<LevelDef>& GetAllLevels();
