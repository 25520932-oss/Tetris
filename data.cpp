#include "data.h"
int score = 0;
int level = 0;

// BẢNG
char board[BOARD_HEIGHT][BOARD_WIDTH];


// BLOCKS (7 KHỐI)
Block blocks[BLOCK_COUNT];

// BIẾN BAN ĐẦU
int x = 4, y = 0; //BLOCK RƠI Ở CHÍNH GIỮA
BlockType currentBlock = I;

// ĐIỂM SỐ & TỐC ĐỘ
int score = 0;
int level = 0;

//TẠO BẢNG
void initBoard() {
    for (int i = 0; i < BOARD_HEIGHT; i++) {
        for (int j = 0; j < BOARD_WIDTH; j++) {
            if (i == BOARD_HEIGHT - 1 || j == 0 || j == BOARD_WIDTH - 1)
                board[i][j] = (char)178;//đổi thành dạng khối đậm
            else
                board[i][j] = ' ';
        }
    }
}

//TẠO HÌNH DẠNG CHO BLOCKS
void initBlocks() {
    // I BLOCK
    Block Iblock = {{
        {' ',' ',' ',' '},
        {'I','I','I','I'},
        {' ',' ',' ',' '},
        {' ',' ',' ',' '}
    }};

    // O BLOCK
    Block Oblock = {{
        {' ',' ',' ',' '},
        {' ','O','O',' '},
        {' ','O','O',' '},
        {' ',' ',' ',' '}
    }};

    // T BLOCK
    Block Tblock = {{
        {' ',' ',' ',' '},
        {'T','T','T',' '},
        {' ','T',' ',' '},
        {' ',' ',' ',' '}
    }};

    // S BLOCK
    Block Sblock = {{
        {' ',' ',' ',' '},
        {' ','S','S',' '},
        {'S','S',' ',' '},
        {' ',' ',' ',' '}
    }};

    // Z BLOCK
    Block Zblock = {{
        {' ',' ',' ',' '},
        {'Z','Z',' ',' '},
        {' ','Z','Z',' '},
        {' ',' ',' ',' '}
    }};

    // J BLOCK
    Block Jblock = {{
        {' ',' ',' ',' '},
        {'J',' ',' ',' '},
        {'J','J','J',' '},
        {' ',' ',' ',' '}
    }};

    // L BLOCK
    Block Lblock = {{
        {' ',' ',' ',' '},
        {' ',' ','L',' '},
        {'L','L','L',' '},
        {' ',' ',' ',' '}
    }};

    blocks[I] = Iblock;
    blocks[O] = Oblock;
    blocks[T] = Tblock;
    blocks[S] = Sblock;
    blocks[Z] = Zblock;
    blocks[J] = Jblock;
    blocks[L] = Lblock;
}
