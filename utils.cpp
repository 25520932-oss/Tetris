#include "utils.h"
#include <windows.h>
#include <ctime>
#include <cstdlib>

// DELAY
void delay(int ms) {
    Sleep(ms);
}

// INIT GAME
void initGame() {
    srand(time(0));
}