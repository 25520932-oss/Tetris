#ifndef PIECE_H
#define PIECE_H

#include "data.h"

// Lấy shape đã xoay
void getRotatedShape(BlockType type, int rot, char out[4][4]);

// Tính vị trí ghost
int calcGhostY();

// Spawn block đầu tiên (khởi tạo cả current + next)
void spawnFirst();

// Spawn block tiếp theo (lấy next, sinh next mới)
void spawnBlock();

// DI CHUYỂN BLOCK
bool moveBlock(int dx, int dy);

// XOAY BLOCK
void rotateBlock();

// Hold block
void holdBlock();

// GHIM BLOCK VÀO BOARD
void lockBlock();

#endif