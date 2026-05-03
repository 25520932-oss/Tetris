#include "game.h"
#include <iostream>
#include <windows.h>
using namespace std;



// XÓA BLOCK KHỎI BOARD
void boardDelBlock(){
    for (int i = 0 ; i < 4 ; i++)
        for (int j = 0 ; j < 4 ; j++)
            if (blocks[currentBlock].shape[i][j] != ' ' && y+i < H)
                board[y+i][x+j] = ' ';
}

// GÁN BLOCK VÀO BOARD
void block2Board(){
    for (int i = 0 ; i < 4 ; i++)
        for (int j = 0 ; j < 4 ; j++)
            if (blocks[currentBlock].shape[i][j] != ' ')
                board[y+i][x+j] = blocks[currentBlock].shape[i][j];
}

// KIỂM TRA DI CHUYỂN
bool canMove(int dx, int dy){
    for (int i = 0 ; i < 4 ; i++)
        for (int j = 0 ; j < 4 ; j++)
            if (blocks[currentBlock].shape[i][j] != ' '){
                int tx = x + j + dx;
                int ty = y + i + dy;

                // FIX: thêm ty < 0 để kiểm tra biên trên
                if (tx < 1 || tx >= W - 1 || ty < 0 || ty >= H - 1)
                    return false;

                if (board[ty][tx] != ' ')
                    return false;
            }
    return true;
}

// XÓA DÒNG ĐẦY — trả về số dòng đã xóa
int removeLine() {
 
}