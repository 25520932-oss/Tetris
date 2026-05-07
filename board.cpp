#include "board.h"

// XÓA BOARD
void clearBoard() {
    for (int i = 0; i < BOARD_HEIGHT; i++)
        for (int j = 0; j < BOARD_WIDTH; j++)
            board[i][j] = ' ';
}

// TRONG BIÊN?
bool isInside(int x, int y) {
    return (x >= 0 && x < BOARD_HEIGHT && y >= 0 && y < BOARD_WIDTH);
}


// Ô TRỐNG?
bool isEmpty(int x, int y) {
    return isInside(x, y) && board[x][y] == ' ';
}

// GHI Ô
void setCell(int x, int y, char value) {
    if (isInside(x, y)) {
        board[x][y] = value;
    }
}

// ĐỌC Ô
char getCell(int x, int y) {
    if (isInside(x, y)) return board[x][y];
    return '#'; // ngoài biên coi như tường
}
