#include "ui.h"
#include "audio.h"

UIManager::UIManager() {
    currentState = GameState::MainMenu;
    previousState = GameState::MainMenu;
    currentMenuIdx = 0;
    currentPauseIdx = 0;
    currentSettingsIdx = 0;
    currentGameOverIdx = 0;
    bgmVolume = 50.0f;
    sfxVolume = 50.0f;
    currentMusicVol = 5;
    currentSFXVol = 5;
    selectedVolumeBar = 0;
    score = 0;
    isTransitioning = false;
    transitionAlpha = 0.0f;
}

extern Audio gameAudio;

bool UIManager::init(const std::string& fontPath, sf::RenderWindow& window) {
    if (!font.loadFromFile(fontPath)) {
        return false;
    }

    sf::Vector2f winSize(static_cast<float>(window.getSize().x), static_cast<float>(window.getSize().y));

    // 1. Khởi tạo nút Main Menu
    mainMenuButtons.push_back(createButton("START", {winSize.x / 2, 220}, {220, 50}));
    mainMenuButtons.push_back(createButton("SETTINGS", {winSize.x / 2, 300}, {220, 50}));
    mainMenuButtons.push_back(createButton("QUIT", {winSize.x / 2, 380}, {220, 50}));
    mainMenuButtons[0].isSelected = true;

    // 2. Khởi tạo nút Pause
    pauseButtons.push_back(createButton("RESUME", {winSize.x / 2, 180}, {220, 50}));
    pauseButtons.push_back(createButton("RESTART", {winSize.x / 2, 260}, {220, 50}));
    pauseButtons.push_back(createButton("SETTINGS", {winSize.x / 2, 340}, {220, 50}));
    pauseButtons.push_back(createButton("QUIT", {winSize.x / 2, 420}, {220, 50}));
    pauseButtons[0].isSelected = true;

    // 3. Khởi tạo nút Settings
    settingsButtons.push_back(createButton("BACK", {winSize.x / 2, 420}, {220, 50}));

    // 4. Khởi tạo nút Game Over
    gameOverButtons.push_back(createButton("RETRY", {winSize.x / 2, 320}, {220, 50}));
    gameOverButtons.push_back(createButton("QUIT", {winSize.x / 2, 400}, {220, 50}));
    gameOverButtons[0].isSelected = true;

    gameOverTitle.setFont(font);
    gameOverTitle.setString("GAME OVER");
    gameOverTitle.setCharacterSize(50);
    gameOverTitle.setFillColor(sf::Color::Red);
    sf::FloatRect titleRect = gameOverTitle.getLocalBounds();
    gameOverTitle.setOrigin(titleRect.left + titleRect.width / 2.0f, titleRect.top + titleRect.height / 2.0f);
    gameOverTitle.setPosition(winSize.x / 2, 120);

    // Điểm số
    scoreText.setFont(font);
    scoreText.setCharacterSize(30);
    scoreText.setFillColor(sf::Color::Yellow);

    // Màn che chuyển cảnh
    transitionOverlay.setSize(winSize);
    transitionOverlay.setFillColor(sf::Color(0, 0, 0, 0));

    return true;
}

Button UIManager::createButton(std::string textStr, sf::Vector2f position, sf::Vector2f size) {
    Button b;
    b.shape.setSize(size);
    b.shape.setOrigin(size.x / 2.0f, size.y / 2.0f);
    b.shape.setPosition(position);
    b.shape.setFillColor(sf::Color(40, 40, 40));
    b.shape.setOutlineThickness(3);
    b.shape.setOutlineColor(sf::Color(150, 150, 150));

    b.text.setFont(font);
    b.text.setString(textStr);
    b.text.setCharacterSize(22);
    b.text.setFillColor(sf::Color::White);

    sf::FloatRect textRect = b.text.getLocalBounds();
    b.text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
    b.text.setPosition(position);

    return b;
}

void UIManager::updateButtonSelection(std::vector<Button>& buttons, int& currentIdx, int direction) {
    if (buttons.empty()) return;
    buttons[currentIdx].isSelected = false;
    currentIdx = (currentIdx + direction + buttons.size()) % buttons.size();
    buttons[currentIdx].isSelected = true;
}

void UIManager::setScore(int s) {
    score = s;
    scoreText.setString("YOUR SCORE: " + std::to_string(score));
    sf::FloatRect textRect = scoreText.getLocalBounds();
    scoreText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
    scoreText.setPosition(400.0f, 220.0f);
}

void UIManager::triggerTransition(GameState targetState) {
    if (!isTransitioning) {
        isTransitioning = true;
        transitionAlpha = 0.0f;
        nextState = targetState;
    }
}

void UIManager::handleEvent(const sf::Event& event, sf::RenderWindow& window) {
    if (isTransitioning) return;

    if (event.type == sf::Event::KeyPressed) {

        if (currentState == GameState::MainMenu) {
            if (event.key.code == sf::Keyboard::Up) updateButtonSelection(mainMenuButtons, currentMenuIdx, -1);
            if (event.key.code == sf::Keyboard::Down) updateButtonSelection(mainMenuButtons, currentMenuIdx, 1);

            if (event.key.code == sf::Keyboard::Return) { // Enter ở bản 2.x là Return
                if (currentMenuIdx == 0) triggerTransition(GameState::Gameplay);
                else if (currentMenuIdx == 1) { previousState = GameState::MainMenu; triggerTransition(GameState::Settings); }
                else if (currentMenuIdx == 2) window.close();
            }
        }
        else if (currentState == GameState::Pause) {
            if (event.key.code == sf::Keyboard::Up) updateButtonSelection(pauseButtons, currentPauseIdx, -1);
            if (event.key.code == sf::Keyboard::Down) updateButtonSelection(pauseButtons, currentPauseIdx, 1);

            if (event.key.code == sf::Keyboard::Return) {
                if (currentPauseIdx == 0) currentState = GameState::Gameplay;
                else if (currentPauseIdx == 1) triggerTransition(GameState::Gameplay);
                else if (currentPauseIdx == 2) { previousState = GameState::Pause; triggerTransition(GameState::Settings); }
                else if (currentPauseIdx == 3) triggerTransition(GameState::MainMenu);
            }
        }
        else if (currentState == GameState::Settings) {
            if (event.key.code == sf::Keyboard::Up) {
                selectedVolumeBar = (selectedVolumeBar - 1 + 3) % 3;
            }
            if (event.key.code == sf::Keyboard::Down) {
                selectedVolumeBar = (selectedVolumeBar + 1) % 3;
            }

            settingsButtons[0].isSelected = (selectedVolumeBar == 2);

            if (event.key.code == sf::Keyboard::Left) {

                if (selectedVolumeBar == 0)
                {
                    currentMusicVol--;
                    if (currentMusicVol < 0) currentMusicVol = 0;
                    gameAudio.setMusicVolume(currentMusicVol);
                    bgmVolume = std::max(0.0f, bgmVolume - 5.0f);
                }

                 
                if (selectedVolumeBar == 1)
                {
                    sfxVolume = std::max(0.0f, sfxVolume - 5.0f);
                    currentSFXVol--;
                    if (currentSFXVol < 0) currentSFXVol = 0;
                    gameAudio.setSFXVolume(currentSFXVol);
                    gameAudio.playSFX(SoundEffect::MOVE);
                }
            }
            if (event.key.code == sf::Keyboard::Right) {
                if (selectedVolumeBar == 0)
                {
                    bgmVolume = std::min(100.0f, bgmVolume + 5.0f);
                    currentMusicVol++;
                    if (currentMusicVol > 10) currentMusicVol = 10;
                    gameAudio.setMusicVolume(currentMusicVol);
                }
                if (selectedVolumeBar == 1)
                {
                    sfxVolume = std::min(100.0f, sfxVolume + 5.0f);
                    currentSFXVol++;
                    if (currentSFXVol > 10) currentSFXVol = 10;
                    gameAudio.setSFXVolume(currentSFXVol);
                    gameAudio.playSFX(SoundEffect::MOVE);
                }
            }

            if (event.key.code == sf::Keyboard::Return) {
                if (selectedVolumeBar == 2) {
                    triggerTransition(previousState);
                }
            }
        }
        else if (currentState == GameState::GameOver) {
            if (event.key.code == sf::Keyboard::Up) updateButtonSelection(gameOverButtons, currentGameOverIdx, -1);
            if (event.key.code == sf::Keyboard::Down) updateButtonSelection(gameOverButtons, currentGameOverIdx, 1);

            if (event.key.code == sf::Keyboard::Return) {
                if (currentGameOverIdx == 0) triggerTransition(GameState::Gameplay);
                else if (currentGameOverIdx == 1) triggerTransition(GameState::MainMenu);
            }
        }
    }
}

void UIManager::update(float deltaTime) {
    auto updateVisuals = [](std::vector<Button>& buttons) {
        for (auto& b : buttons) {
            if (b.isSelected) {
                b.shape.setFillColor(sf::Color(100, 100, 220));
                b.shape.setOutlineColor(sf::Color::Cyan);
            } else {
                b.shape.setFillColor(sf::Color(40, 40, 40));
                b.shape.setOutlineColor(sf::Color(150, 150, 150));
            }
        }
    };

    if (currentState == GameState::MainMenu) updateVisuals(mainMenuButtons);
    else if (currentState == GameState::Pause) updateVisuals(pauseButtons);
    else if (currentState == GameState::Settings) updateVisuals(settingsButtons);
    else if (currentState == GameState::GameOver) updateVisuals(gameOverButtons);

    if (isTransitioning) {
        transitionAlpha += 600.0f * deltaTime;
        if (transitionAlpha >= 255.0f) {
            transitionAlpha = 255.0f;
            currentState = nextState;
            isTransitioning = false;

            // Báo hiệu reset game khi màn hình đen hoàn toàn để chuẩn bị sang màn chơi mới
            if (currentState == GameState::Gameplay) {
                extern void initGame();  // Khai báo mượn hàm từ file tetris.cpp
                extern void initBoard();
                extern void spawnBlock();
                extern void block2Board();

                initGame();   // Reset điểm số, cấp độ về 0
                initBoard();  // Xóa sạch ma trận bàn cờ
                spawnBlock(); // Sinh khối gạch mới tinh
                block2Board();
            }
        }
        transitionOverlay.setFillColor(sf::Color(0, 0, 0, static_cast<sf::Uint8>(transitionAlpha)));
    }
    else {
        if (transitionAlpha > 0.0f) {
            transitionAlpha -= 600.0f * deltaTime;
            if (transitionAlpha < 0.0f) transitionAlpha = 0.0f;
            transitionOverlay.setFillColor(sf::Color(0, 0, 0, static_cast<sf::Uint8>(transitionAlpha)));
        }
    }
}

void UIManager::draw(sf::RenderWindow& window) {
    auto drawButtons = [&](const std::vector<Button>& buttons) {
        for (size_t i = 0; i < buttons.size(); ++i) {
            window.draw(buttons[i].shape);
            window.draw(buttons[i].text);
        }
        };

    if (currentState == GameState::MainMenu) {
        drawButtons(mainMenuButtons);
    }
    else if (currentState == GameState::Pause) {
        drawButtons(pauseButtons);
    }
    else if (currentState == GameState::Settings) {
        drawButtons(settingsButtons);

        sf::Text bgmText;
        bgmText.setFont(font);
        bgmText.setCharacterSize(24);
        bgmText.setString("BGM Volume: < " + std::to_string(static_cast<int>(bgmVolume)) + "% >");
        bgmText.setPosition(220.0f, 180.0f);
        bgmText.setFillColor(selectedVolumeBar == 0 ? sf::Color::Cyan : sf::Color::White);
        window.draw(bgmText);

        sf::Text sfxText;
        sfxText.setFont(font);
        sfxText.setCharacterSize(24);
        sfxText.setString("SFX Volume: < " + std::to_string(static_cast<int>(sfxVolume)) + "% >");
        sfxText.setPosition(220.0f, 260.0f);
        sfxText.setFillColor(selectedVolumeBar == 1 ? sf::Color::Cyan : sf::Color::White);
        window.draw(sfxText);
    }
    else if (currentState == GameState::GameOver) {
        window.draw(gameOverTitle);
        window.draw(scoreText);
        drawButtons(gameOverButtons);
    }

    if (isTransitioning || transitionAlpha > 0.0f) {
        window.draw(transitionOverlay);
    }
}