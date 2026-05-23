#include "piece.h"
#include "game.h"
#include "piece_class.h"
#include "audio.h"  
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
        for (int i = 0; i < 4; i++)
            for (int j = 0; j < 4; j++)
                pieces[currentBlock]->shape[i][j] = temp[i][j];
    }

    block2Board();
}

void doHoldBlock() {
    if (holdUsed) return;
    holdUsed = true;

    boardDelBlock();

    if (holdBlock == NONE) {
        holdBlock = currentBlock;
        spawnBlock();
        holdUsed = true;
    }
    else {
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

void lockBlock() {
    gameAudio.playSFX(SoundEffect::JOINT);
}