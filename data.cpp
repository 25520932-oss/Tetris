#include "data.h"
#include "piece_class.h"

// BOARD
char board[H][W];

// Mảng Piece* — mỗi phần tử trỏ đến đúng subclass
Piece* pieces[BLOCK_COUNT];

// TRẠNG THÁI BLOCK HIỆN TẠI
int x = W / 2 - 2;
int y = 0;
int rotation = 0;
BlockType currentBlock = I;
BlockType nextQueue[NEXT_COUNT] = { O, T, S, Z };

// HOLD
BlockType holdBlock = NONE;
bool      holdUsed = false;

// ĐIỂM SỐ & CẤP ĐỘ
int score = 0;
int level = 1;
int highScore = 0;
int linesCleared = 0;

// KHỞI TẠO BOARD
void initBoard() {
    for (int i = 0; i < H; i++) {
        for (int j = 0; j < W; j++) {
            if (i == 0 || i == H - 1 || j == 0 || j == W - 1)
                board[i][j] = CELL_WALL;
            else
                board[i][j] = CELL_EMPTY;
        }
    }
}

// KHỞI TẠO 7 PIECE
void initPieces() {
    pieces[I] = new IPiece();
    pieces[O] = new OPiece();
    pieces[T] = new TPiece();
    pieces[S] = new SPiece();
    pieces[Z] = new ZPiece();
    pieces[J] = new JPiece();
    pieces[L] = new LPiece();
}