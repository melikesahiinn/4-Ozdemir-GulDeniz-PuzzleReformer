#pragma once
#include "raylib.h"
#include <vector>

struct Tile {
    int rotation = 0;        // 0..3
    int correctRotation = 0; // 0..3
    bool selected = false;

    // simple rotate animation
    float animT = 1.0f; // 0..1
    int animFrom = 0;
    int animTo = 0;
};

class Grid {
public:
    Grid() = default;
    Grid(int n, int tileSize, int originX, int originY);

    void ApplyLevel(int n, int tileSize, int originX, int originY,
                    const std::vector<int>& correct, const std::vector<int>& start);

    void Update(float dt);
    void Draw(bool showHint) const;

    int PickTile(Vector2 mousePos) const;
    void Select(int index);
    bool RotateSelected(); // returns true if rotated
    bool IsSolved() const;

private:
    Rectangle TileRect(int index) const;
    Vector2 TileCenter(int index) const;

private:
    int m_n = 0;
    int m_tileSize = 0;
    int m_originX = 0;
    int m_originY = 0;

    int m_selectedIndex = -1;
    std::vector<Tile> m_tiles;
};
