#include "input.h"
#include "piece.h" 

void processInput(const sf::Event& event) {
    if (event.type != sf::Event::KeyPressed) return;

    switch (event.key.code) {
    case sf::Keyboard::A: case sf::Keyboard::Left:
        moveBlock(-1, 0);
        break;
    case sf::Keyboard::D: case sf::Keyboard::Right:
        moveBlock(1, 0);
        break;
    case sf::Keyboard::S: case sf::Keyboard::Down:
        moveBlock(0, 1);
        break;
    case sf::Keyboard::W: case sf::Keyboard::Up:
        rotateBlock();
        break;
    case sf::Keyboard::C:
        doHoldBlock();
        break;
    case sf::Keyboard::Space:
        while (moveBlock(0, 1));
        break;
    default:
        break;
    }
}