#ifndef GAME_H
#define GAME_H

#include "data.h"

// XỬ LÝ BLOCK
void boardDelBlock();
void block2Board();

// LOGIC
bool canMove(int dx, int dy);

// XÓA DÒNG
int removeLine();

#endif