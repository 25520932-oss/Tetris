#include "data.h"
#include "game.h"
#include "piece.h"
#include "input.h"
#include "render.h"
#include "utils.h"
#include "audio.h"
#include <algorithm>  

int main() {
    //KHỞI TẠO
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

    sf::Clock fallClock;
    bool gameOver = false;

    // GAME LOOP
    while (window.isOpen() && !gameOver) {

        // Xử lý sự kiện
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            processInput(event);
        }

        // Logic rơi theo thời gian
        int speed = std::max(80, 400 - level * 25);
        if (fallClock.getElapsedTime().asMilliseconds() >= speed) {
            fallClock.restart();

            if (!moveBlock(0, 1)) {
                // Block không xuống được → gắn vào board
                lockBlock();

                int cleared = removeLine();

                spawnBlock();

                if (isGameOver()) {
                    gameOver = true;
                    gameAudio.playSFX(SoundEffect::GAME_OVER); // [NEW] SFX game over
                    // Đợi animation kết thúc trước khi đóng
                    sf::sleep(sf::milliseconds(800));
                }
                else {
                    block2Board();
                }

                (void)cleared; // dùng cleared nếu cần thêm logic sau này
            }
        }

        // Render
        render();
    }

    // Dọn dẹp
    gameAudio.stopBGM();
    if (window.isOpen())
        window.close();

    return 0;
}