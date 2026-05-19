#include "piece.h"
#include "game.h"
#include "piece_class.h"
#include <cstdlib>


void spawnBlock() {
    currentBlock = nextQueue[0];
    for (int i = 0; i < NEXT_COUNT - 1; i++)
        nextQueue[i] = nextQueue[i + 1];
    nextQueue[NEXT_COUNT - 1] = (BlockType)(rand() % BLOCK_COUNT);

    pieces[currentBlock]->resetShape();

    x = W / 2 - 2;
    y = 0;
    rotation = 0;

    // Mỗi lượt spawn mới → cho phép hold lại
    holdUsed = false;
}

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

void rotateBlock() {
    boardDelBlock();

    char temp[4][4];
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            temp[i][j] = pieces[currentBlock]->shape[i][j];

    pieces[currentBlock]->rotate();

    if (!canMove(0, 0)) {
        // Hoàn tác nếu xoay gây va chạm
        for (int i = 0; i < 4; i++)
            for (int j = 0; j < 4; j++)
                pieces[currentBlock]->shape[i][j] = temp[i][j];
    }

    block2Board();
}


void doHoldBlock() {
    if (holdUsed) return;       // đã hold lượt này → bỏ qua
    holdUsed = true;

    boardDelBlock();

    if (holdBlock == NONE) {
        // Chưa có hold → lưu lại, spawn block kế tiếp
        holdBlock = currentBlock;
        spawnBlock();           // spawnBlock sẽ reset holdUsed = false,
        holdUsed = true;
    }
    else {
        // Hoán đổi hold ↔ current
        BlockType tmp = holdBlock;
        holdBlock = currentBlock;
        currentBlock = tmp;

        pieces[currentBlock]->resetShape();
        x = W / 2 - 2;
        y = 0;
        rotation = 0;
    }

    block2Board();
}