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

sf::RenderWindow window(sf::VideoMode(800, 600), "Tetris Game - SFML 2.6.2");

int main() {
    //tu dong chay dung voi toc do quet cua may
    window.setVerticalSyncEnabled(true);

    UIManager ui;
    if (!ui.init("arial.ttf", window)) {
        return -1;
    }

    initGame();       // seed random
    initBoard();      // tạo board + tường
    initPieces();     // tạo 7 piece objects
    initRender();     // tạo SFML window + load font

    gameAudio.loadMedia();
    gameAudio.setMusicVolume(7);
    gameAudio.setSFXVolume(8);
    gameAudio.playBGM();

    spawnBlock();
    block2Board();

    sf::Clock gameClock;
    float dropTimer = 0.0f;

    // Bộ đếm thời gian quản lý việc đè phím di chuyển
    float sideMoveTimer = 0.0f;
    bool isKeyHeld = false;

    while (window.isOpen()) {
        float deltaTime = gameClock.restart().asSeconds();

        sf::Event event;
        // 1. VÒNG LẶP SỰ KIỆN 
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Escape) {
                    if (ui.getCurrentState() == GameState::Gameplay) {
                        ui.setCurrentState(GameState::Pause);
                    }
                }
            }

            if (ui.getCurrentState() == GameState::Gameplay) {
                processInput(event);
            }

            // Gửi sự kiện sang UI xử lý nút bấm Menu
            ui.handleEvent(event, window);
        }

        // ─── CẬP NHẬT TRẠNG THÁI UI ───
        ui.update(deltaTime);

        // LOGIC GAMEPLAY TETRIS 
        if (ui.getCurrentState() == GameState::Gameplay) {

            dropTimer += deltaTime;
            float speedInSeconds = std::max(80, 400 - level * 25) / 1000.0f;

            if (dropTimer >= speedInSeconds) {
                dropTimer = 0.0f;

                
                if (!moveBlock(0, 1)) {
                    lockBlock();
                    int cleared = removeLine();
                    spawnBlock();

                    if (isGameOver()) {
                        ui.triggerTransition(GameState::GameOver);
                        ui.setScore(score);
                        gameAudio.playSFX(SoundEffect::GAME_OVER);
                    }
                    else {
                        block2Board();
                    }
                    (void)cleared;
                }
            }
        }

        // ─── RENDERING ───
        window.clear(sf::Color(10, 20, 45));
        if (ui.getCurrentState() == GameState::Gameplay) {
            render();
        }
        else {
            ui.draw(window);
        }
        window.display();
    }
}