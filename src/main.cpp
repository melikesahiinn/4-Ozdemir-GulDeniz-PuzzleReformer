#include "raylib.h"

int main() {
    const int W = 1000;
    const int H = 700;

    InitWindow(W, H, "Tile Rotation Puzzle");
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawText("Raylib is working!", 40, 40, 30, DARKGRAY);
        DrawText(TextFormat("FPS: %d", GetFPS()), 40, 90, 22, GRAY);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
