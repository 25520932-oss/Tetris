#include "render.h"
#include "data.h"
#include "piece_class.h"
#include <iostream>
#include <string>

#define byte win_byte_override
#include <windows.h>
#undef byte

using namespace std;

void gotoxy(int row, int col) {
    COORD coord = { (SHORT)col, (SHORT)row };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void renderNextQueue() {
    const int offCol = W * 2 + 2;
    const int offRow = 1;

    gotoxy(offRow, offCol);
    cout << "NEXT";

    gotoxy(offRow + 1, offCol);
    cout << (char)201;
    for (int j = 0; j < 10; j++) cout << (char)205 << (char)205;
    cout << (char)187;

    for (int k = 0; k < NEXT_COUNT; k++) {
        BlockType type = nextQueue[k];
        for (int i = 0; i < 4; i++) {
            gotoxy(offRow + 2 + k * 5 + i, offCol);
            cout << (char)186;
            for (int j = 0; j < 4; j++) {
                // Dùng getCell() thay vì truy cập shape trực tiếp
                cout << (pieces[type]->getCell(i, j) != CELL_EMPTY
                         ? string(2, (char)219)
                         : "  ");
            }
            cout << "  " << (char)186;
        }
        if (k < NEXT_COUNT - 1) {
            gotoxy(offRow + 2 + k * 5 + 4, offCol);
            cout << (char)186;
            for (int j = 0; j < 10; j++) cout << "  ";
            cout << (char)186;
        }
    }

    int bottomRow = offRow + 2 + NEXT_COUNT * 5 - 1;
    gotoxy(bottomRow, offCol);
    cout << (char)200;
    for (int j = 0; j < 10; j++) cout << (char)205 << (char)205;
    cout << (char)188;
}

static void renderScoreBox(int row, int col, const char* label, int value) {
    gotoxy(row, col);
    cout << label;
    gotoxy(row + 1, col);
    cout << (char)201;
    for (int j = 0; j < 10; j++) cout << (char)205 << (char)205;
    cout << (char)187;
    gotoxy(row + 2, col);
    cout << (char)186;
    string s = to_string(value);
    cout << " " << s;
    for (int i = 0; i < 20 - 1 - (int)s.size(); i++) cout << " ";
    cout << (char)186;
    gotoxy(row + 3, col);
    cout << (char)200;
    for (int j = 0; j < 10; j++) cout << (char)205 << (char)205;
    cout << (char)188;
}

void renderScore() {
    renderScoreBox(1 + 2 + NEXT_COUNT * 5 + 1, W * 2 + 2, "SCORE", score);
}

void renderHighScore() {
    renderScoreBox(1 + 2 + NEXT_COUNT * 5 + 6, W * 2 + 2, "HIGH SCORE", highScore);
}

void render() {
    CONSOLE_CURSOR_INFO ci = {1, FALSE};
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &ci);
    gotoxy(0, 0);
    for (int i = 0; i < H; i++, cout << '\n')
        for (int j = 0; j < W; j++)
            cout << board[i][j] << board[i][j];
    renderNextQueue();
    renderScore();
    renderHighScore();
}