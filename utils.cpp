#include "utils.h"
#include <iostream>

#define byte win_byte_override
#include <windows.h>
#undef byte

using namespace std;
#include <ctime>
#include <cstdlib>

// DELAY
void delay(int ms) {
    Sleep(ms);
}

// INIT GAME
//void initGame() {
    //srand(time(0));
//}
