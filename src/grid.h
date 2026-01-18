#pragma once
#include "raylib.h"
#include <vector>
#include "tile.h"

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

    // NEW: lock/unlock specific tiles by indices (used in Level 4)
    void SetLocked(const std::vector<int>& indices, bool locked = true);

private:
    Rectangle TileRect(int index) const;

private:
    int m_n = 0;
    int m_tileSize = 0;
    int m_originX = 0;
    int m_originY = 0;

    int m_selectedIndex = -1;
    std::vector<Tile> m_tiles;
};
