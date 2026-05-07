#ifndef DATA_H
#define DATA_H

#include <iostream>
using namespace std;

// KÍCH THƯỚC BOARD
// Thay vì dùng H và W
#define BOARD_HEIGHT 20
#define BOARD_WIDTH 15


// LOẠI KHỐI TETRIS
enum BlockType {
    I, O, T, S, Z, J, L, BLOCK_COUNT
};

// STRUCT KHỐI
struct Block {
    char shape[4][4];
};

// BOARD GAME
extern char board[BOARD_HEIGHT][BOARD_WIDTH];

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
