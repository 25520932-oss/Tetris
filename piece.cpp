#include "piece.h"
#include "game.h"
#include "piece_class.h"
#include <cstdlib>

// SPAWN BLOCK — lấy block đầu queue, dịch queue, thêm block ngẫu nhiên vào cuối
void spawnBlock() {
    currentBlock = nextQueue[0];
    for (int i = 0; i < NEXT_COUNT - 1; i++)
        nextQueue[i] = nextQueue[i + 1];
    nextQueue[NEXT_COUNT - 1] = (BlockType)(rand() % BLOCK_COUNT);

    // Reset shape về trạng thái ban đầu qua virtual dispatch
    pieces[currentBlock]->resetShape();

    x = W / 2 - 2;
    y = 0;
    rotation = 0;
}

// DI CHUYỂN BLOCK
bool moveBlock(int dx, int dy) {
    boardDelBlock();
    if (canMove(dx, dy)) {
        x += dx;
        y += dy;
        block2Board();
        return true;
    }
    block2Board();
    return false;
}

// XOAY BLOCK — gọi virtual rotate() của từng subclass
void rotateBlock() {
    boardDelBlock();

    // Backup shape trước khi xoay (dùng trực tiếp shape[] trong Piece)
    char temp[4][4];
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            temp[i][j] = pieces[currentBlock]->shape[i][j];

    pieces[currentBlock]->rotate();

    if (!canMove(0, 0)) {
        for (int i = 0; i < 4; i++)
            for (int j = 0; j < 4; j++)
                pieces[currentBlock]->shape[i][j] = temp[i][j];
    }

    block2Board();
}