#ifndef DATA_H
#define DATA_H

#include <iostream>
using namespace std;

// KÍCH THƯỚC BOARD
const int H = 22;
const int W = 12;

// KÝ TỰ ĐẠI DIỆN
const char CELL_EMPTY = ' ';
const char CELL_WALL  = (char)178; // ▓
const char CELL_BLOCK = (char)176; // ░

// LOẠI KHỐI TETRIS
enum BlockType {
    I, O, T, S, Z, J, L, BLOCK_COUNT,
    NONE = -1
};

// === FORWARD DECLARE để data.h không phụ thuộc vào piece_class.h ===
class Piece;

// BOARD GAME
extern char board[H][W];

// Mảng pointer — truy cập qua virtual dispatch (đa hình)
extern Piece* pieces[BLOCK_COUNT];

// BIẾN TRẠNG THÁI
extern int x, y;
extern int rotation;
extern BlockType currentBlock;

const int NEXT_COUNT = 4;
extern BlockType nextQueue[NEXT_COUNT];

// ĐIỂM SỐ & CẤP ĐỘ
extern int score;
extern int level;
extern int highScore;

// KHỞI TẠO
void initPieces(); // thay initBlocks()
void initBoard();

#endif