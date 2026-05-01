#ifndef PIECE_H
#define PIECE_H

#include "data.h"

// KHỞI TẠO BLOCK MỚI
void spawnBlock();

// DI CHUYỂN BLOCK
bool moveBlock(int dx, int dy);

// XOAY BLOCK
void rotateBlock();

// GHIM BLOCK VÀO BOARD
void lockBlock();

#endif