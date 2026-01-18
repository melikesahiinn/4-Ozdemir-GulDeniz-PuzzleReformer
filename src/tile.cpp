#include "tile.h"
#include <cmath>

static float Lerp(float a, float b, float t) { return a + (b - a) * t; }

void Tile::Reset(int correctRot, int startRot) {
    correctRotation = correctRot % 4;
    rotation = startRot % 4;
    selected = false;

    animT = 1.0f;
    animFrom = rotation;
    animTo = rotation;
}

bool Tile::IsCorrect() const {
    return (rotation % 4) == (correctRotation % 4);
}

void Tile::StartRotateCW() {
    int from = rotation;
    int to = (rotation + 1) % 4;
    rotation = to;

    animFrom = from;
    animTo = to;
    animT = 0.0f;
}

void Tile::Update(float dt) {
    if (animT < 1.0f) {
        animT += dt * 10.0f; // animation speed
        if (animT > 1.0f) animT = 1.0f;
    }
}

void Tile::Draw(const Rectangle& rc, bool showHint) const {
    const bool correct = IsCorrect();

    DrawRectangleRec(rc, Fade(LIGHTGRAY, 0.6f));

    if (correct) DrawRectangleLinesEx(rc, 3, Fade(GREEN, 0.65f));
    else         DrawRectangleLinesEx(rc, 2, Fade(GRAY, 0.55f));

    if (selected) DrawRectangleLinesEx(rc, 4, Fade(BLUE, 0.85f));

    // animated rotation marker
    Vector2 center = { rc.x + rc.width * 0.5f, rc.y + rc.height * 0.5f };

    float fromAngle = (float)animFrom * 90.0f;
    float toAngle   = (float)animTo * 90.0f;
    if (animFrom == 3 && animTo == 0) toAngle = 360.0f;

    float angle = Lerp(fromAngle, toAngle, animT);
    float rad = angle * (PI / 180.0f);

    Vector2 dir = { sinf(rad), -cosf(rad) }; // points up at 0deg
    float len = rc.width * 0.30f;
    Vector2 tip = { center.x + dir.x * len, center.y + dir.y * len };

    DrawLineEx(center, tip, 6.0f, DARKGRAY);
    DrawCircleV(tip, 6.0f, DARKGRAY);

    if (showHint) {
        DrawText(TextFormat("%d", correctRotation),
                 (int)rc.x + 6, (int)rc.y + 6, 18, Fade(BLACK, 0.45f));
    }
}
