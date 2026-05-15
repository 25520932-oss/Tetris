#include "game.h"
#include "piece_class.h"

// Macro tiện để đọc ô của block hiện tại qua virtual dispatch
#define CUR(i,j)  pieces[currentBlock]->getCell(i, j)

// XÓA BLOCK KHỎI BOARD
void boardDelBlock() {
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            if (CUR(i,j) != CELL_EMPTY && y+i < H && x+j < W)
                board[y+i][x+j] = CELL_EMPTY;
}

// GÁN BLOCK LÊN BOARD
void block2Board() {
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            if (CUR(i,j) != CELL_EMPTY)
                board[y+i][x+j] = CELL_BLOCK;
}

// KIỂM TRA CÓ THỂ DI CHUYỂN
bool canMove(int dx, int dy) {
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            if (CUR(i,j) != CELL_EMPTY) {
                int tx = x + j + dx;
                int ty = y + i + dy;
                if (tx < 1 || tx >= W-1 || ty < 0 || ty >= H-1)
                    return false;
                if (board[ty][tx] != CELL_EMPTY)
                    return false;
            }
    return true;
}

// XÓA DÒNG ĐẦY
int removeLine() {
    int count = 0;
    for (int i = H-2; i >= 1; i--) {
        bool isFull = true;
        for (int j = 1; j < W-1; j++)
            if (board[i][j] == CELL_EMPTY) { isFull = false; break; }

        if (isFull) {
            count++;
            for (int k = i; k > 1; k--)
                for (int j = 1; j < W-1; j++)
                    board[k][j] = board[k-1][j];
            for (int j = 1; j < W-1; j++)
                board[1][j] = CELL_EMPTY;
            i++;
        }
    }
    if (count > 0) {
        const int pts[5] = {0, 1, 3, 6, 10};
        score += (count <= 4) ? pts[count] : count * 3;
        if (score > highScore) highScore = score;
        level = score / 10 + 1;
    }
    return count;
}

// KIỂM TRA THUA
bool isGameOver() {
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            if (CUR(i,j) != CELL_EMPTY)
                if (board[y+i][x+j] != CELL_EMPTY)
                    return true;
    return false;
}