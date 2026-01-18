#include "game.h"
#include "levels.h"
#include "ui.h"
#include "raylib.h"
#include <algorithm>
#include <cmath>
#include <vector>

Game::Game(int screenW, int screenH) : m_w(screenW), m_h(screenH) {}

void Game::Init() {
    m_totalLevels = (int)GetAllLevels().size();
    LoadLevel(0);
    StartTransition(GameState::MainMenu);
}

void Game::LoadLevel(int index) {
    m_levelIndex = std::clamp(index, 0, std::max(0, m_totalLevels - 1));
    const LevelDef& lvl = GetAllLevels().at(m_levelIndex);

    int gridPx = lvl.n * lvl.tileSize;
    int originX = (m_w - gridPx) / 2;
    int originY = (m_h - gridPx) / 2 + 40;

    m_grid.ApplyLevel(lvl.n, lvl.tileSize, originX, originY, lvl.correct, lvl.start);

    // --- NEW: per-level rule state reset ---
    m_moves = 0;
    m_moveLimit = -1;
    m_limitMsgT = 0.0f;

    // Helper for (r,c) -> index
    auto idx = [&](int r, int c) { return r * lvl.n + c; };

    // --- NEW: Level 4 rule (locked tiles introduced) ---
    // Level numbers are 1-based in UI, but m_levelIndex is 0-based.
    if (m_levelIndex == 3) { // Level 4
        int n = lvl.n; // expected 6
        int mid1 = n / 2 - 1;
        int mid2 = n / 2;

        std::vector<int> locks = {
            idx(0,0), idx(0,n-1), idx(n-1,0), idx(n-1,n-1),     // corners
            idx(mid1,mid1), idx(mid1,mid2), idx(mid2,mid1), idx(mid2,mid2) // center 2x2
        };

        m_grid.SetLocked(locks, true);
    }

    // --- NEW: Level 5 rule (final test: move limit) ---
    if (m_levelIndex == 4) { // Level 5
        m_moveLimit = lvl.n * lvl.n * 2; // e.g., 7*7*2 = 98
        m_showHint = false;              // start harder; player can toggle with H
    }
}

void Game::ResetLevel() {
    LoadLevel(m_levelIndex);
}

void Game::NextLevel() {
    int next = m_levelIndex + 1;
    if (next >= m_totalLevels) {
        StartTransition(GameState::MainMenu);
        LoadLevel(0);
        return;
    }
    LoadLevel(next);
    StartTransition(GameState::Playing);
}

void Game::Update(float dt) {
    UpdateTransition(dt);

    if (!m_inTransition) {
        switch (m_state) {
            case GameState::MainMenu:      UpdateMainMenu(); break;
            case GameState::Playing:       UpdatePlaying(dt); break;
            case GameState::LevelComplete: UpdateLevelComplete(); break;
        }
    } else {
        if (m_state == GameState::Playing) m_grid.Update(dt);
    }
}

void Game::UpdateMainMenu() {
    Rectangle btn = { (float)m_w/2 - 140, (float)m_h/2 - 20, 280, 56 };

    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        Vector2 mp = GetMousePosition();
        if (CheckCollisionPointRec(mp, btn)) StartTransition(GameState::Playing);
    }
    if (IsKeyPressed(KEY_ENTER) || IsKeyPressed(KEY_SPACE)) StartTransition(GameState::Playing);
}

void Game::UpdatePlaying(float dt) {
    m_grid.Update(dt);

    // NEW: message timer decay
    if (m_limitMsgT > 0.0f) {
        m_limitMsgT -= dt;
        if (m_limitMsgT < 0.0f) m_limitMsgT = 0.0f;
    }

    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        int idx = m_grid.PickTile(GetMousePosition());
        if (idx != -1) m_grid.Select(idx);
    }

    if (IsKeyPressed(KEY_R)) {
        if (m_grid.RotateSelected()) {
            m_moves++;

            // NEW: Level 5 move limit enforcement
            if (m_moveLimit > 0 && m_moves > m_moveLimit) {
                ResetLevel();
                m_limitMsgT = 1.6f; // show warning after reset
            }
        }
    }

    if (IsKeyPressed(KEY_BACKSPACE)) {
        ResetLevel();
        m_limitMsgT = 0.0f;
    }

    if (IsKeyPressed(KEY_H)) {
        m_showHint = !m_showHint;
    }

    if (m_grid.IsSolved()) {
        StartTransition(GameState::LevelComplete);
    }
}

void Game::UpdateLevelComplete() {
    if (IsKeyPressed(KEY_SPACE) || IsKeyPressed(KEY_ENTER)) NextLevel();
    if (IsKeyPressed(KEY_BACKSPACE)) {
        ResetLevel();
        StartTransition(GameState::Playing);
    }
    if (IsKeyPressed(KEY_ESCAPE)) {
        StartTransition(GameState::MainMenu);
    }
}

void Game::Draw() {
    switch (m_state) {
        case GameState::MainMenu:      DrawMainMenu(); break;
        case GameState::Playing:       DrawPlaying(); break;
        case GameState::LevelComplete: DrawLevelComplete(); break;
    }

    DrawText(TextFormat("FPS: %d", GetFPS()), 10, 10, 20, DARKGRAY);
    DrawFadeOverlay();
}

void Game::DrawMainMenu() {
    DrawText("TILE ROTATION PUZZLE", m_w/2 - 220, 120, 42, BLACK);
    DrawText("Click PLAY or press Enter", m_w/2 - 165, 180, 22, DARKGRAY);

    Rectangle btn = { (float)m_w/2 - 140, (float)m_h/2 - 20, 280, 56 };
    DrawButton(btn, "PLAY (Enter)", 26);

    DrawText("Controls:", 40, m_h - 140, 22, BLACK);
    DrawText("- Mouse Left: Select tile", 40, m_h - 110, 20, DARKGRAY);
    DrawText("- R: Rotate selected tile", 40, m_h - 85, 20, DARKGRAY);
    DrawText("- Backspace: Reset level", 40, m_h - 60, 20, DARKGRAY);
    DrawText("- H: Toggle hint", 40, m_h - 35, 20, DARKGRAY);
}

void Game::DrawPlaying() {
    DrawText(TextFormat("Level %d / %d", m_levelIndex + 1, m_totalLevels), 20, 40, 26, BLACK);
    DrawText("R: rotate | Backspace: reset | H: hint", 20, 70, 18, DARKGRAY);

    // NEW: move counter display
    if (m_moveLimit > 0) {
        DrawText(TextFormat("Moves: %d / %d", m_moves, m_moveLimit), 20, 95, 18, DARKGRAY);
    } else {
        DrawText(TextFormat("Moves: %d", m_moves), 20, 95, 18, DARKGRAY);
    }

    if (m_limitMsgT > 0.0f) {
        DrawText("Move limit exceeded! Level reset.", 20, 120, 18, RED);
    }

    m_grid.Draw(m_showHint);
}

void Game::DrawLevelComplete() {
    DrawPlaying();

    Rectangle panel = { (float)m_w/2 - 230, (float)m_h/2 - 95, 460, 190 };

    float t = (float)GetTime();
    float s = 1.0f + 0.02f * sinf(t * 8.0f);
    Vector2 center = { panel.x + panel.width/2, panel.y + panel.height/2 };
    Rectangle p2 = { center.x - panel.width*s/2, center.y - panel.height*s/2, panel.width*s, panel.height*s };

    DrawRectangleRounded(p2, 0.15f, 12, Fade(BLACK, 0.12f));
    DrawRectangleRoundedLines(p2, 0.15f, 12, Fade(BLACK, 0.25f));

    DrawText("LEVEL COMPLETE!", (int)panel.x + 85, (int)panel.y + 30, 32, BLACK);
    DrawText("Space/Enter: Next Level", (int)panel.x + 105, (int)panel.y + 85, 20, DARKGRAY);
    DrawText("Backspace: Restart", (int)panel.x + 135, (int)panel.y + 115, 20, DARKGRAY);
    DrawText("Esc: Main Menu", (int)panel.x + 155, (int)panel.y + 145, 20, DARKGRAY);
}

void Game::StartTransition(GameState next) {
    m_inTransition = true;
    m_nextState = next;
    m_fadeOut = true;
    m_fade = 0.0f;
}

void Game::UpdateTransition(float dt) {
    if (!m_inTransition) return;

    if (m_fadeOut) {
        m_fade += dt * m_fadeSpeed;
        if (m_fade >= 1.0f) {
            m_fade = 1.0f;
            // swap state at full black
            m_state = m_nextState;
            m_fadeOut = false;
        }
    } else {
        m_fade -= dt * m_fadeSpeed;
        if (m_fade <= 0.0f) {
            m_fade = 0.0f;
            m_inTransition = false;
        }
    }
}

void Game::DrawFadeOverlay() const {
    if (m_fade <= 0.0f) return;
    DrawRectangle(0, 0, m_w, m_h, Fade(BLACK, m_fade));
}
