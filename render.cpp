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


// Khung nằm bên phải board, bắt đầu tại cột W*2 + 2
void renderNextQueue() {
    // Board được vẽ mỗi ô 2 ký tự ngang, nên offset X = W*2 + 2
    const int offsetX = W * 2 + 2;  // cột bắt đầu khung NEXT (tính theo console column)
    const int offsetY = 1;           // hàng bắt đầu

    // Tiêu đề
    gotoxy(offsetY, offsetX);
    cout << "NEXT";

    // Vẽ đường viền trên
    gotoxy(offsetY + 1, offsetX);
    cout << (char)201;  // ╔
    for (int j = 0; j < 10; j++) cout << (char)205 << (char)205;  // ══
    cout << (char)187;  // ╗

    // Vẽ từng block trong queue
    for (int k = 0; k < NEXT_COUNT; k++) {
        BlockType type = nextQueue[k];

        // 4 hàng shape + 1 hàng trống ngăn cách
        for (int i = 0; i < 4; i++) {
            int row = offsetY + 2 + k * 5 + i;  // mỗi block chiếm 5 hàng (4 shape + 1 gap)
            gotoxy(row, offsetX);
            cout << (char)186;  // ║ viền trái

            for (int j = 0; j < 4; j++) {
                char cell = blocks[type].shape[i][j];
                if (cell != ' ')
                    cout << (char)219 << (char)219;  // █ block đặc
                else
                    cout << "  ";
            }

            // 1 cột trống padding phải + viền phải
            cout << "  " << (char)186;  // ║ viền phải
        }

        // Hàng trống ngăn cách giữa các block (trừ block cuối)
        if (k < NEXT_COUNT - 1) {
            int sepRow = offsetY + 2 + k * 5 + 4;
            gotoxy(sepRow, offsetX);
            cout << (char)186;
            for (int j = 0; j < 10; j++) cout << "  ";
            cout << (char)186;
        }
    }

    // Vẽ đường viền dưới
    int bottomRow = offsetY + 2 + NEXT_COUNT * 5 - 1;
    gotoxy(bottomRow, offsetX);
    cout << (char)200;  // ╚
    for (int j = 0; j < 10; j++) cout << (char)205 << (char)205;
    cout << (char)188;  // ╝
}

// VẼ BOARD + BLOCK
void render() {
    // Ẩn con trỏ (chỉ cần gọi 1 lần khi khởi tạo)
    CONSOLE_CURSOR_INFO ci = {1, FALSE};
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &ci);
     gotoxy(0,0);
    for (int i = 0 ; i < H ; i++, cout<<endl)
        for (int j = 0 ; j < W ; j++)
            cout<<board[i][j]<<board[i][j];
    
    renderNextQueue();
}
