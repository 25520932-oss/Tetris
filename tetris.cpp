#include "data.h"
#include "game.h"
#include "piece.h"
#include "input.h"
#include "render.h"
#include "utils.h"

bool GameOver(){
    for (int i = 0 ; i < 4 ; i++)
        for (int j = 0 ; j < 4 ; j++)
            if (blocks[currentBlock].shape[i][j] != ' ')
                if(board[y+i][x+j]!=' ') return true;
    return false;
}

int main() {

    // KHỞI TẠO
    initGame();     // seed random
    initBoard();    // tạo board + tường
    initBlocks();   // tạo shape các khối

    spawnBlock();   // block đầu tiên
    block2Board();  // vẽ block đầu tiên lên board

    // GAME LOOP
    while (true) {

        render();

        // INPUT
        processInput();

        // LOGIC RƠI
        if (!moveBlock(0, 1)) {
            // FIX: moveBlock đã gọi block2Board() bên trong,
            // lockBlock() chỉ cần gọi khi block KHÔNG di chuyển được (chạm đáy)
            lockBlock();


            removeLine();

            spawnBlock();
            if(GameOver()) break;
            block2Board(); // FIX: vẽ block mới lên board ngay sau khi spawn

        }

        // DELAY — tốc độ tăng dần theo level (tối thiểu 80ms)
        int speed = max(80, 300 - level * 20);
        delay(speed);
    }
    gotoxy(23,0);
    cout<<"GAME OVER!";
    return 0;
}
