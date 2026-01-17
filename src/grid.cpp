#include "grid.h"
#include <cmath>

static float Lerp(float a, float b, float t) { return a + (b - a) * t; }

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
        m_tiles[i].correctRotation = correct[i] % 4;
        m_tiles[i].rotation = start[i] % 4;
        m_tiles[i].selected = false;
        m_tiles[i].animT = 1.0f;
        m_tiles[i].animFrom = m_tiles[i].rotation;
        m_tiles[i].animTo = m_tiles[i].rotation;
    }
}

void Grid::Update(float dt) {
    for (auto& t : m_tiles) {
        if (t.animT < 1.0f) {
            t.animT += dt * 10.0f; // animation speed
            if (t.animT > 1.0f) t.animT = 1.0f;
        }
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

Vector2 Grid::TileCenter(int index) const {
    Rectangle rc = TileRect(index);
    return Vector2{ rc.x + rc.width/2.0f, rc.y + rc.height/2.0f };
}

int Grid::PickTile(Vector2 mousePos) const {
    for (int i = 0; i < (int)m_tiles.size(); i++) {
        if (CheckCollisionPointRec(mousePos, TileRect(i))) return i;
    }
    return -1;
}

void Grid::Select(int index) {
    if (index < 0 || index >= (int)m_tiles.size()) return;

    if (m_selectedIndex != -1) m_tiles[m_selectedIndex].selected = false;
    m_selectedIndex = index;
    m_tiles[m_selectedIndex].selected = true;
}

bool Grid::RotateSelected() {
    if (m_selectedIndex < 0 || m_selectedIndex >= (int)m_tiles.size()) return false;

    Tile& t = m_tiles[m_selectedIndex];
    int from = t.rotation;
    int to = (t.rotation + 1) % 4;
    t.rotation = to;

    t.animFrom = from;
    t.animTo = to;
    t.animT = 0.0f;
    return true;
}

bool Grid::IsSolved() const {
    for (const auto& t : m_tiles) {
        if ((t.rotation % 4) != (t.correctRotation % 4)) return false;
    }
    return true;
}

void Grid::Draw(bool showHint) const {
    for (int i = 0; i < (int)m_tiles.size(); i++) {
        const Tile& t = m_tiles[i];
        Rectangle rc = TileRect(i);

        bool correct = (t.rotation == t.correctRotation);

        DrawRectangleRec(rc, Fade(LIGHTGRAY, 0.6f));

        if (correct) DrawRectangleLinesEx(rc, 3, Fade(GREEN, 0.65f));
        else         DrawRectangleLinesEx(rc, 2, Fade(GRAY, 0.55f));

        if (t.selected) DrawRectangleLinesEx(rc, 4, Fade(BLUE, 0.85f));

        // animated rotation marker
        Vector2 center = TileCenter(i);

        float fromAngle = (float)t.animFrom * 90.0f;
        float toAngle   = (float)t.animTo * 90.0f;
        if (t.animFrom == 3 && t.animTo == 0) toAngle = 360.0f;

        float angle = Lerp(fromAngle, toAngle, t.animT);
        float rad = angle * (PI / 180.0f);

        Vector2 dir = { sinf(rad), -cosf(rad) }; // points up at 0deg
        float len = rc.width * 0.30f;
        Vector2 tip = { center.x + dir.x * len, center.y + dir.y * len };

        DrawLineEx(center, tip, 6.0f, DARKGRAY);
        DrawCircleV(tip, 6.0f, DARKGRAY);

        if (showHint) {
            DrawText(TextFormat("%d", t.correctRotation), (int)rc.x + 6, (int)rc.y + 6, 18, Fade(BLACK, 0.45f));
        }
    }

    Rectangle border = { (float)m_originX, (float)m_originY, (float)(m_n*m_tileSize), (float)(m_n*m_tileSize) };
    DrawRectangleLinesEx(border, 2, Fade(BLACK, 0.25f));
}
