#include "grid.h"

Grid::Grid(int n, int tileSize, int originX, int originY)
: m_n(n), m_tileSize(tileSize), m_originX(originX), m_originY(originY) {
    m_tiles.resize(m_n * m_n);
}

void Grid::ApplyLevel(int n, int tileSize, int originX, int originY,
                      const std::vector<int>& correct, const std::vector<int>& start) {
    m_n = n;
    m_tileSize = tileSize;
    m_originX = originX;
    m_originY = originY;

    m_tiles.assign(m_n * m_n, Tile{});
    m_selectedIndex = -1;

    for (int i = 0; i < (int)m_tiles.size(); i++) {
        m_tiles[i].Reset(correct[i], start[i]);
        m_tiles[i].locked = false; // NEW: default unlocked each level
    }
}

void Grid::Update(float dt) {
    for (auto& t : m_tiles) {
        t.Update(dt);
    }
}

Rectangle Grid::TileRect(int index) const {
    int r = index / m_n;
    int c = index % m_n;
    return Rectangle{
        (float)(m_originX + c * m_tileSize),
        (float)(m_originY + r * m_tileSize),
        (float)m_tileSize,
        (float)m_tileSize
    };
}

int Grid::PickTile(Vector2 mousePos) const {
    for (int i = 0; i < (int)m_tiles.size(); i++) {
        if (CheckCollisionPointRec(mousePos, TileRect(i))) return i;
    }
    return -1;
}

void Grid::Select(int index) {
    if (index < 0 || index >= (int)m_tiles.size()) return;

    // NEW: do not allow selecting locked tiles
    if (m_tiles[index].locked) return;

    if (m_selectedIndex != -1) m_tiles[m_selectedIndex].selected = false;
    m_selectedIndex = index;
    m_tiles[m_selectedIndex].selected = true;
}

bool Grid::RotateSelected() {
    if (m_selectedIndex < 0 || m_selectedIndex >= (int)m_tiles.size()) return false;

    // NEW: cannot rotate locked tile
    if (m_tiles[m_selectedIndex].locked) return false;

    m_tiles[m_selectedIndex].StartRotateCW();
    return true;
}

bool Grid::IsSolved() const {
    for (const auto& t : m_tiles) {
        if (!t.IsCorrect()) return false;
    }
    return true;
}

// NEW: lock/unlock specific tiles (Level 4 rule)
void Grid::SetLocked(const std::vector<int>& indices, bool locked) {
    for (int idx : indices) {
        if (idx < 0 || idx >= (int)m_tiles.size()) continue;

        m_tiles[idx].locked = locked;

        // If locked, force correct orientation so puzzle remains solvable
        if (locked) {
            m_tiles[idx].rotation = m_tiles[idx].correctRotation;
            m_tiles[idx].animFrom = m_tiles[idx].rotation;
            m_tiles[idx].animTo   = m_tiles[idx].rotation;
            m_tiles[idx].animT    = 1.0f;
            m_tiles[idx].selected = false;
            if (m_selectedIndex == idx) m_selectedIndex = -1;
        }
    }
}

void Grid::Draw(bool showHint) const {
    for (int i = 0; i < (int)m_tiles.size(); i++) {
        const Tile& t = m_tiles[i];
        Rectangle rc = TileRect(i);

        t.Draw(rc, showHint);

        // NEW: overlay for locked tiles
        if (t.locked) {
            DrawRectangleRec(rc, Fade(RED, 0.10f));
            DrawLineEx({rc.x + 10, rc.y + 10}, {rc.x + rc.width - 10, rc.y + rc.height - 10}, 4.0f, Fade(RED, 0.70f));
            DrawLineEx({rc.x + rc.width - 10, rc.y + 10}, {rc.x + 10, rc.y + rc.height - 10}, 4.0f, Fade(RED, 0.70f));
        }
    }

    Rectangle border = { (float)m_originX, (float)m_originY,
                         (float)(m_n*m_tileSize), (float)(m_n*m_tileSize) };
    DrawRectangleLinesEx(border, 2, Fade(BLACK, 0.25f));
}
