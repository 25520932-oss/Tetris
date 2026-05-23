#include "data.h"
#include "game.h"
#include "piece.h"
#include "input.h"
#include "render.h"
#include "utils.h"
#include <SFML/Graphics.hpp>
#include "ui.h"
#include "audio.h"
#include <algorithm>

// Kích thước window khớp chính xác với board + 2 side panel.
sf::RenderWindow window(
    sf::VideoMode(WIN_W, WIN_H),
    "Tetris Game - SFML 2.6.2"
);

UIManager ui;   // khai báo global để render.cpp và các file khác cùng xài

int main() {
    // VSync — đồng bộ với màn hình, chống tearing và giảm CPU
    window.setVerticalSyncEnabled(true);

    // Tải font TRƯỚC (initRender), sau đó UI mượn lại font đó
    initRender();

    if (!ui.init("", window)) {  // fontPath truyền rỗng — UI.cpp tự lấy từ extern font
        return -1;
    }

    initGame();     // seed random, reset score/level
    initBoard();    // tạo board + tường
    initPieces();   // tạo 7 piece objects

    gameAudio.loadMedia();
    gameAudio.setMusicVolume(7);
    gameAudio.setSFXVolume(8);
    gameAudio.playBGM();

    spawnBlock();
    block2Board();

    sf::Clock gameClock;
    float dropTimer = 0.0f;

    while (window.isOpen()) {
        float deltaTime = gameClock.restart().asSeconds();
        // Giới hạn deltaTime tránh "spiral of death" khi lag đột biến
        if (deltaTime > 0.1f) deltaTime = 0.1f;

        // ── XỬ LÝ SỰ KIỆN ──
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::KeyPressed &&
                event.key.code == sf::Keyboard::Escape) {
                if (ui.getCurrentState() == GameState::Gameplay)
                    ui.setCurrentState(GameState::Pause);
            }

            if (ui.getCurrentState() == GameState::Gameplay)
                processInput(event);

            ui.handleEvent(event, window);
        }

        // ── CẬP NHẬT UI ──
        ui.update(deltaTime);

        // ── LOGIC GAMEPLAY ──
        if (ui.getCurrentState() == GameState::Gameplay) {
            dropTimer += deltaTime;
            float speedInSeconds = std::max(80, 400 - level * 25) / 1000.0f;

            if (dropTimer >= speedInSeconds) {
                dropTimer = 0.0f;

                if (!moveBlock(0, 1)) {
                    lockBlock();
                    removeLine();
                    spawnBlock();

                    if (isGameOver()) {
                        ui.triggerTransition(GameState::GameOver);
                        ui.setScore(score);
                        gameAudio.playSFX(SoundEffect::GAME_OVER);
                    }
                    else {
                        block2Board();
                    }
                }
            }
        }

        // ── RENDER (clear + draw + display chỉ 1 lần duy nhất mỗi frame) ──
        window.clear(sf::Color(10, 20, 45));

        if (ui.getCurrentState() == GameState::Gameplay) {
            render();   // render() KHÔNG gọi clear/display nữa
        }
        else {
            ui.draw(window);
        }

        window.display();
    }

    return 0;
}