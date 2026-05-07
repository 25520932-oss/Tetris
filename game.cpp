#include "game.h"
#include <iostream>

#define byte win_byte_override
#include <windows.h>
#undef byte

using namespace std;



// XÓA BLOCK KHỎI BOARD
void boardDelBlock(){
    for (int i = 0 ; i < 4 ; i++)
        for (int j = 0 ; j < 4 ; j++)
            if (blocks[currentBlock].shape[i][j] != ' ' && y+i < H && x+j < W)
                board[y+i][x+j] = ' ';
}

// GÁN BLOCK VÀO BOARD
void block2Board(){
    for (int i = 0 ; i < 4 ; i++)
        for (int j = 0 ; j < 4 ; j++)
            if (blocks[currentBlock].shape[i][j] != ' ')
                board[y+i][x+j] = (char)176;//đổi thành dạng khối mờ
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

// XÓA DÒNG ĐẦY — trả về số dòng đã xóa - tăng tốc mỗi lần xóa
int removeLine() {
 int count = 0;

    for (int i = H - 2; i >= 1; i--) {
        bool isFull = true;
        for (int j = 1; j < W - 1; j++) {
            if (board[i][j] == ' ') {
                isFull = false;
                break;
            }
        }
 
        if (isFull) {
            count++;
            // Dịch tất cả dòng phía trên xuống
            for (int k = i; k > 1; k--) {
                for (int j = 1; j < W - 1; j++) {
                    board[k][j] = board[k-1][j];
                }
            }
            // Xóa dòng trên cùng
            for (int j = 1; j < W - 1; j++) board[1][j] = ' ';
            i++; // Kiểm tra lại dòng hiện tại sau khi dịch
        }
    }
 
    // Tính điểm theo số dòng xóa được
    if (count > 0) {
        // 1 dòng = 1đ, 2 dòng = 3đ, 3 dòng = 6đ, 4 dòng (Tetris) = 10đ
        int pts[5] = {0, 1, 3, 6, 10};
        score += (count <= 4) ? pts[count] : count * 3;
        level = score / 10 + 1;
    }
 
    return count;

}
