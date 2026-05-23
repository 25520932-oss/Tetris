#ifndef UI_H
#define UI_H

#include "../sfml/include/SFML/Graphics.hpp"
#include <vector>
#include <string>
#include <algorithm>

enum class GameState {
    MainMenu,
    Gameplay,
    Settings,
    Pause,
    GameOver
};

struct Button {
    sf::RectangleShape shape;
    sf::Text text;
    bool isSelected;

    // Trở về hàm tạo mặc định bình thường của SFML 2.x
    Button() : isSelected(false) {}
};

class UIManager {
private:
    sf::Font font;
    GameState currentState;
    GameState previousState;

    std::vector<Button> mainMenuButtons;
    std::vector<Button> pauseButtons;
    std::vector<Button> settingsButtons;
    std::vector<Button> gameOverButtons;

    int currentMenuIdx;
    int currentPauseIdx;
    int currentSettingsIdx;
    int currentGameOverIdx;

    float bgmVolume;
    float sfxVolume;
    int selectedVolumeBar;

    int score;
    sf::Text scoreText;
    sf::Text gameOverTitle;

    bool isTransitioning;
    sf::RectangleShape transitionOverlay;
    float transitionAlpha;
    GameState nextState;

    Button createButton(std::string textStr, sf::Vector2f position, sf::Vector2f size);
    void updateButtonSelection(std::vector<Button>& buttons, int& currentIdx, int direction);

public:
    UIManager();
    bool init(const std::string& fontPath, sf::RenderWindow& window);

    void setScore(int s);
    void triggerTransition(GameState targetState);

    // Bản 2.x truyền tham chiếu sf::Event thông thường
    void handleEvent(const sf::Event& event, sf::RenderWindow& window);
    void update(float deltaTime);
    void draw(sf::RenderWindow& window);

    GameState getCurrentState() const { return currentState; }
    void setCurrentState(GameState state) { currentState = state; }
    float getBGMVolume() const { return bgmVolume; }
    float getSFXVolume() const { return sfxVolume; }
};

#endif
