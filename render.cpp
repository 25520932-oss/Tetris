#include "render.h"
#include "data.h"
#include <iostream>
#include <windows.h>
using namespace std;

// DI CHUYỂN CON TRỎ
void gotoxy(int x, int y) {
    COORD coord;
    coord.X = y;
    coord.Y = x;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}


// VẼ BOARD + BLOCK
void render() {
   
}