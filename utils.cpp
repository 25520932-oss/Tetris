#include "utils.h"
#include <SFML/System/Clock.hpp>
#include <ctime>
#include <cstdlib>

void delay(int ms) {
    sf::Clock clock;
    while (clock.getElapsedTime().asMilliseconds() < ms) { /* spin */ }
}

void initGame() {
    srand((unsigned)time(0));
}