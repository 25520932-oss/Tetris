#include "data.h"
#include "game.h"
#include "piece.h"
#include "input.h"
#include "render.h"
#include "utils.h"

int main() {
    //KHỞI TẠO 
    initGame();
    initBoard();
    initPieces();
    initRender();

    spawnBlock();
    block2Board();

    //Clock để tính thời gian rơi
    sf::Clock fallClock;
    bool gameOver = false;

    while (window.isOpen() && !gameOver) {
─
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            processInput(event);
        }
  
        int speed = std::max(80, 300 - level * 20);
        if (fallClock.getElapsedTime().asMilliseconds() >= speed) {
            fallClock.restart();

            if (!moveBlock(0, 1)) {
                removeLine();
                spawnBlock();

                if (isGameOver()) {
                    gameOver = true;
                } else {
                    block2Board();
                }
            }
        }

        render();
    }

    //game over tạm
    if (window.isOpen())
        window.close();

    return 0;
}