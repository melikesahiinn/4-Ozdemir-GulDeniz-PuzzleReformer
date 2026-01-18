#pragma once
#include "raylib.h"

struct Tile {
    int rotation = 0;        // 0..3
    int correctRotation = 0; // 0..3
    bool selected = false;

    bool locked = false;

    // simple rotate animation
    float animT = 1.0f; // 0..1
    int animFrom = 0;
    int animTo = 0;

    void Reset(int correctRot, int startRot);
    bool IsCorrect() const;
    void StartRotateCW();
    void Update(float dt);

    // Draws the tile visuals inside rc. showHint prints correctRotation.
    void Draw(const Rectangle& rc, bool showHint) const;
};
