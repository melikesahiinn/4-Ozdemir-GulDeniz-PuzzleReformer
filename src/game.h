#pragma once
#include "states.h"
#include "grid.h"

class Game {
public:
    Game(int screenW, int screenH);

    void Init();
    void Update(float dt);
    void Draw();

private:
    // --- polish: fade transition ---
    bool m_inTransition = false;
    GameState m_nextState = GameState::MainMenu;
    float m_fade = 0.0f;      // 0..1
    bool m_fadeOut = true;    // fade to black then back
    float m_fadeSpeed = 2.5f; // speed factor

    void StartTransition(GameState next);
    void UpdateTransition(float dt);
    void DrawFadeOverlay() const;

    void LoadLevel(int index);
    void ResetLevel();
    void NextLevel();

    void UpdateMainMenu();
    void UpdatePlaying(float dt);
    void UpdateLevelComplete();

    void DrawMainMenu();
    void DrawPlaying();
    void DrawLevelComplete();

private:
    int m_w, m_h;
    GameState m_state = GameState::MainMenu;

    int m_levelIndex = 0;
    int m_totalLevels = 0;

    Grid m_grid;

    bool m_showHint = true;

    // NEW: Level 5 "final test" rule (move limit)
    int m_moves = 0;
    int m_moveLimit = -1;   // -1 = unlimited
    float m_limitMsgT = 0.0f; // seconds to show "limit exceeded" message (optional)
};
