#include "board.h"

bool isInside(int x, int y) {
    return (x >= 0 && x < H && y >= 0 && y < W);
}

bool isEmpty(int x, int y) {
    return isInside(x, y) && board[x][y] == CELL_EMPTY;
}

void setCell(int x, int y, char value) {
    if (isInside(x, y)) board[x][y] = value;
}

// Trả về CELL_WALL nếu ngoài biên — giúp canMove không cần check biên riêng
char getCell(int x, int y) {
    return isInside(x, y) ? board[x][y] : CELL_WALL;
}