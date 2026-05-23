#include "input.h"
#include "piece.h"
#include "audio.h"   // [NEW] SFX cho từng thao tác

void processInput(const sf::Event& event) {
    if (event.type != sf::Event::KeyPressed) return;

    switch (event.key.code) {

        // Di chuyển trái/phải
    case sf::Keyboard::A: case sf::Keyboard::Left:
        if (moveBlock(-1, 0))
            gameAudio.playSFX(SoundEffect::MOVE);
        break;

    case sf::Keyboard::D: case sf::Keyboard::Right:
        if (moveBlock(1, 0))
            gameAudio.playSFX(SoundEffect::MOVE);
        break;

        // Soft drop
    case sf::Keyboard::S: case sf::Keyboard::Down:
        if (moveBlock(0, 1))
            gameAudio.playSFX(SoundEffect::MOVE);
        break;

        // Xoay
    case sf::Keyboard::W: case sf::Keyboard::Up:
        rotateBlock();
        gameAudio.playSFX(SoundEffect::ROTATE); 
        break;

        // Hold
    case sf::Keyboard::C:
        doHoldBlock();
        gameAudio.playSFX(SoundEffect::ROTATE);
        break;

        // Hard drop
    case sf::Keyboard::Space:
        while (moveBlock(0, 1));                    // rơi hết xuống đáy
        gameAudio.playSFX(SoundEffect::HARD_DROP);
        break;

    default:
        break;
    }
}