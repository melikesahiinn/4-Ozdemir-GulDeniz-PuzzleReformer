#include "ui.h"
#include "raylib.h"

void DrawButton(Rectangle r, const char* text, int fontSize) {
    Vector2 mp = GetMousePosition();
    bool hover = CheckCollisionPointRec(mp, r);

    DrawRectangleRounded(r, 0.2f, 10, hover ? Fade(BLACK, 0.12f) : Fade(BLACK, 0.08f));
    DrawRectangleRoundedLines(r, 0.2f, 10, Fade(BLACK, hover ? 0.35f : 0.25f));

    int textW = MeasureText(text, fontSize);
    DrawText(text, (int)(r.x + (r.width - textW)/2), (int)(r.y + (r.height - fontSize)/2), fontSize, BLACK);
}
