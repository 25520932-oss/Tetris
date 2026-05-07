#ifndef DATA_H
#define DATA_H

#include <iostream>
using namespace std;

// KÍCH THƯỚC BOARD
#define H 20
#define W 15


// LOẠI KHỐI TETRIS
enum BlockType {
    I, O, T, S, Z, J, L, BLOCK_COUNT
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
extern int x, y;
extern BlockType currentBlock;

// ĐIỂM SỐ & TỐC ĐỘ
extern int score;   // tổng số dòng đã xóa
extern int level;   // cấp độ hiện tại (tăng mỗi 10 dòng)

// kHỞI TẠO BẢNG
void initBlocks();
void initBoard();

#endif
