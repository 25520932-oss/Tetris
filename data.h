#ifndef DATA_H
#define DATA_H

#include <iostream>
using namespace std;

// KÍCH THƯỚC BOARD
const int H = 22 ;
const int W = 12;

// KÝ TỰ ĐẠI DIỆN
const char CELL_EMPTY = ' ';
const char CELL_WALL = (char)178; // ▓
const char CELL_BLOCK = (char)176; // ░

// LOẠI KHỐI TETRIS
enum BlockType {
    I, O, T, S, Z, J, L, BLOCK_COUNT,
    NONE = -1
};

// === FORWARD DECLARE ===
class Piece;

// BOARD GAME
extern char board[H][W];

// Mảng pointer — truy cập qua virtual dispatch
extern Piece* pieces[BLOCK_COUNT];

// BIẾN TRẠNG THÁI
extern int x, y;
extern int rotation;
extern BlockType currentBlock;

const int NEXT_COUNT = 4;
extern BlockType nextQueue[NEXT_COUNT];

// HOLD
extern BlockType holdBlock;      // NONE nếu chưa hold
extern bool holdUsed;       // chỉ hold 1 lần mỗi lượt

// ĐIỂM SỐ & CẤP ĐỘ
extern int score;
extern int level;
extern int highScore;
extern int linesCleared;         // tổng số dòng đã xóa

// KHỞI TẠO
void initPieces();
void initBoard();

#endif