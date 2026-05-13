#ifndef DATA_H
#define DATA_H

#include <iostream>
using namespace std;

// KÍCH THƯỚC BOARD
const int H = 22;
const int W = 12;


// LOẠI KHỐI TETRIS
enum BlockType {
    I, O, T, S, Z, J, L, BLOCK_COUNT,
    NONE = -1
};

// STRUCT KHỐI
struct Block {
    char shape[4][4];
};

// BOARD GAME
extern char board[H][W];

// BLOCK DATA
extern Block blocks[BLOCK_COUNT];

// BIẾN TRẠNG THÁI
extern int x, y;              // vị trí block hiện tại (cột, hàng)
extern int ghostY;            // hàng ghost block
extern int rotation;          // góc xoay 0-3
extern BlockType currentBlock;
const int NEXT_COUNT = 4;
extern BlockType nextQueue[NEXT_COUNT];   // hàng đợi 4 block tiếp theo
extern BlockType heldBlock;
extern bool hasHeld;          // đã hold trong lượt này chưa

// ĐIỂM SỐ & TỐC ĐỘ
extern int score;   // tổng số dòng đã xóa
extern int level;   // cấp độ hiện tại (tăng mỗi 10 dòng)
extern int highScore; // điểm cao nhất

// kHỞI TẠO BẢNG
void initBlocks();
void initBoard();

#endif
