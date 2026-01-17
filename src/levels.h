#pragma once
#include <vector>

struct LevelDef {
    int n = 3;
    int tileSize = 100;
    std::vector<int> correct; // size n*n, each 0..3
    std::vector<int> start;   // size n*n, each 0..3
};

const std::vector<LevelDef>& GetAllLevels();
