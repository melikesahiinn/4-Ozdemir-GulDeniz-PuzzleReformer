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
};
