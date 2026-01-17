#include "raylib.h"
#include "game.h"

int main() {
    const int W = 1000;
    const int H = 700;

    InitWindow(W, H, "Tile Rotation Puzzle");
    SetTargetFPS(60);

    Game game(W, H);
    game.Init();

    while (!WindowShouldClose()) {
        float dt = GetFrameTime();
        game.Update(dt);

        BeginDrawing();
        ClearBackground(RAYWHITE);
        game.Draw();
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
