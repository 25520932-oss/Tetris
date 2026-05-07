#include "render.h"
#include "data.h"
#include <iostream>

#define byte win_byte_override
#include <windows.h>
#undef byte

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
     gotoxy(0,0);
    for (int i = 0 ; i < BOARD_HEIGHT ; i++, cout<<endl)
        for (int j = 0 ; j < BOARD_WIDTH ; j++)
            cout<<board[i][j]<<board[i][j];
}
