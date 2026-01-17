#include "game.h"
#include "levels.h"
#include "ui.h"
#include "raylib.h"
#include <algorithm>

Game::Game(int screenW, int screenH) : m_w(screenW), m_h(screenH) {}

void Game::Init() {
    m_totalLevels = (int)GetAllLevels().size();
    LoadLevel(0);
    m_state = GameState::MainMenu;
}

void Game::LoadLevel(int index) {
    m_levelIndex = std::clamp(index, 0, std::max(0, m_totalLevels - 1));
    const LevelDef& lvl = GetAllLevels().at(m_levelIndex);

    int gridPx = lvl.n * lvl.tileSize;
    int originX = (m_w - gridPx) / 2;
    int originY = (m_h - gridPx) / 2 + 40;

    m_grid.ApplyLevel(lvl.n, lvl.tileSize, originX, originY, lvl.correct, lvl.start);
}

void Game::ResetLevel() {
    LoadLevel(m_levelIndex);
}

void Game::NextLevel() {
    int next = m_levelIndex + 1;
    if (next >= m_totalLevels) {
        m_state = GameState::MainMenu;
        LoadLevel(0);
        return;
    }
    LoadLevel(next);
    m_state = GameState::Playing;
}

void Game::Update(float dt) {
    switch (m_state) {
        case GameState::MainMenu:      UpdateMainMenu(); break;
        case GameState::Playing:       UpdatePlaying(dt); break;
        case GameState::LevelComplete: UpdateLevelComplete(); break;
    }
}

void Game::UpdateMainMenu() {
    Rectangle btn = { (float)m_w/2 - 140, (float)m_h/2 - 20, 280, 56 };

    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        Vector2 mp = GetMousePosition();
        if (CheckCollisionPointRec(mp, btn)) m_state = GameState::Playing;
    }
    if (IsKeyPressed(KEY_ENTER) || IsKeyPressed(KEY_SPACE)) m_state = GameState::Playing;
}

void Game::UpdatePlaying(float dt) {
    m_grid.Update(dt);

    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        int idx = m_grid.PickTile(GetMousePosition());
        if (idx != -1) m_grid.Select(idx);
    }

    if (IsKeyPressed(KEY_R)) {
        m_grid.RotateSelected();
    }

    if (IsKeyPressed(KEY_BACKSPACE)) {
        ResetLevel();
    }

    if (IsKeyPressed(KEY_H)) {
        m_showHint = !m_showHint;
    }

    if (m_grid.IsSolved()) {
        m_state = GameState::LevelComplete;
    }
}

void Game::UpdateLevelComplete() {
    if (IsKeyPressed(KEY_SPACE) || IsKeyPressed(KEY_ENTER)) NextLevel();
    if (IsKeyPressed(KEY_BACKSPACE)) {
        ResetLevel();
        m_state = GameState::Playing;
    }
    if (IsKeyPressed(KEY_ESCAPE)) {
        m_state = GameState::MainMenu;
    }
}

void Game::Draw() {
    switch (m_state) {
        case GameState::MainMenu:      DrawMainMenu(); break;
        case GameState::Playing:       DrawPlaying(); break;
        case GameState::LevelComplete: DrawLevelComplete(); break;
    }

    DrawText(TextFormat("FPS: %d", GetFPS()), 10, 10, 20, DARKGRAY);
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

    m_grid.Draw(m_showHint);
}

void Game::DrawLevelComplete() {
    DrawPlaying();

    Rectangle panel = { (float)m_w/2 - 230, (float)m_h/2 - 95, 460, 190 };
    DrawRectangleRounded(panel, 0.15f, 12, Fade(BLACK, 0.12f));
    DrawRectangleRoundedLines(panel, 0.15f, 12, Fade(BLACK, 0.25f));

    DrawText("LEVEL COMPLETE!", (int)panel.x + 85, (int)panel.y + 30, 32, BLACK);
    DrawText("Space/Enter: Next Level", (int)panel.x + 105, (int)panel.y + 85, 20, DARKGRAY);
    DrawText("Backspace: Restart", (int)panel.x + 135, (int)panel.y + 115, 20, DARKGRAY);
    DrawText("Esc: Main Menu", (int)panel.x + 155, (int)panel.y + 145, 20, DARKGRAY);
}
