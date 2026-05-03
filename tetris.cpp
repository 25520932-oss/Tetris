<<<<<<< HEAD
#include <iostream>
#include <conio.h>
#include <windows.h>
using namespace std;
#define H 20
#define W 15
char board[H][W] = {} ;
//Can bang ti le xuat hien cua cac khoi
char blocks[][4][4] = {
        {{' ','I',' ',' '},
         {' ','I',' ',' '},
         {' ','I',' ',' '},
         {' ','I',' ',' '}},

        {{' ',' ',' ',' '},
         {' ','O','O',' '},
         {' ','O','O',' '},
         {' ',' ',' ',' '}},

        {{' ',' ',' ',' '},
         {'I','I','I','I'},
         {' ',' ',' ',' '},
         {' ',' ',' ',' '}},

        {{' ',' ',' ',' '},
         {' ','T',' ',' '},
         {'T','T','T',' '},
         {' ',' ',' ',' '}},

        {{' ',' ',' ',' '},
         {' ','S','S',' '},
         {'S','S',' ',' '},
         {' ',' ',' ',' '}},

        {{' ',' ',' ',' '},
         {'Z','Z',' ',' '},
         {' ','Z','Z',' '},
         {' ',' ',' ',' '}},

        {{' ',' ',' ',' '},
         {'J',' ',' ',' '},
         {'J','J','J',' '},
         {' ',' ',' ',' '}},

        {{' ',' ',' ',' '},
         {' ',' ','L',' '},
         {'L','L','L',' '},
         {' ',' ',' ',' '}}
};

int x=4,y=0,b=1;
void gotoxy(int x, int y) {
    COORD c = {x, y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}
void boardDelBlock(){
    for (int i = 0 ; i < 4 ; i++)
        for (int j = 0 ; j < 4 ; j++)
            if (blocks[b][i][j] != ' '){
                int tx = x + j;
                int ty = y + i;
                if (tx > 0 && tx < W-1 && ty > 0 && ty < H-1)
                    board[ty][tx] = ' ';
            }
}
void block2Board(){
    for (int i = 0 ; i < 4 ; i++)
        for (int j = 0 ; j < 4 ; j++)
            if (blocks[b][i][j] != ' ' ){
                int tx = x + j;
                int ty = y + i;
                if (tx > 0 && tx < W-1 && ty > 0 && ty < H-1)
                    board[ty][tx] = (char)176;
            }
}
void initBoard(){
    for (int i = 0 ; i < H ; i++)
        for (int j = 0 ; j < W ; j++)
            if ((i==0) ||(i==H-1) || (j==0) || (j == W-1)) board[i][j] = (char) 178;// doi khung thanh dang khoi
            else board[i][j] = ' ';
}
void draw(){
    gotoxy(0,0);
    for (int i = 0 ; i < H ; i++, cout<<endl)
        for (int j = 0 ; j < W ; j++)
            cout<<board[i][j]<<board[i][j];
            /*In 2 lan de can doi ti le khoi
            Kich thuoc co ban cua khoi la 1920 x 1080 */
}
bool canMove(int dx, int dy){
    for (int i = 0 ; i < 4 ; i++)
        for (int j = 0 ; j < 4 ; j++)
            if (blocks[b][i][j] != ' '){
                int tx = x + j + dx;
                int ty = y + i + dy;
                if ( tx<1 || tx >= W-1 || ty >= H-1) return false;
                if ( board[ty][tx] != ' ') return false;
            }
    return true;
}
void removeLine(){
    int j;
    for (int i = H-2; i >0 ; i-- ){
        for (j = 0; j < W-1 ; j++)
            if (board[i][j] == ' ') break;
        if (j == W-1){
            for (int ii = i; ii >1 ; ii-- )
                for (int j = 0; j < W-1 ; j++ ) board[ii][j] = board[ii-1][j];
            i++;
            draw();
            _sleep(200);
        }
    }
}
=======
#include "data.h"
#include "game.h"
#include "piece.h"
#include "input.h"
#include "render.h"
#include "utils.h"

int main() {

    // KHỞI TẠO
    initGame();     // seed random
    initBoard();    // tạo board + tường
    initBlocks();   // tạo shape các khối

    spawnBlock();   // block đầu tiên
    block2Board();  // FIX: vẽ block đầu tiên lên board

    // GAME LOOP
    while (true) {

        render();

        // INPUT
        processInput();

        // LOGIC RƠI
        if (!moveBlock(1, 0)) {
            // FIX: moveBlock đã gọi block2Board() bên trong,
            // lockBlock() chỉ cần gọi khi block KHÔNG di chuyển được (chạm đáy)
            lockBlock();
>>>>>>> a58f41dc318b569972c9d2388a39b079ea2adbbb

            removeLine();

            spawnBlock();
            block2Board(); // FIX: vẽ block mới lên board ngay sau khi spawn
        }

        // DELAY — tốc độ tăng dần theo level (tối thiểu 80ms)
        int speed = max(80, 300 - level * 20);
        delay(speed);
    }

    return 0;
}
