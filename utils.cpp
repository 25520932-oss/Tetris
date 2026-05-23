#include "utils.h"
#include <SFML/System/Clock.hpp>
#include <ctime>
#include <cstdlib>
#include "data.h"

void delay(int ms) {
    sf::Clock clock;
    while (clock.getElapsedTime().asMilliseconds() < ms) { /* spin */ }
}

void initGame() {
    //reset lai khi retry game
    score = 0;
    level = 1;
    linesCleared = 0;

    srand((unsigned)time(0));
}