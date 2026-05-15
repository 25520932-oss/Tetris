#include "data.h"
#include "game.h"
#include "piece.h"
#include "input.h"
#include "render.h"
#include "utils.h"

int main() {

    // KHỞI TẠO
    initGame();       // seed random (utils.cpp)
    initBoard();      // tạo board + tường (data.cpp)
    initPieces();     // BUG FIX: đổi initBlocks() → initPieces() (tên đúng trong data.cpp)

    spawnBlock();     // block đầu tiên
    block2Board();    // vẽ block đầu tiên lên board

    // GAME LOOP
    while (true) {

        render();

        // INPUT
        processInput();

        // LOGIC RƠI
        if (!moveBlock(0, 1)) {
            // block không di chuyển được → khóa tại chỗ (block2Board đã gọi trong moveBlock)
            removeLine();

            spawnBlock();

            // Kiểm tra game over TRƯỚC khi vẽ block mới lên board
            // Nếu check sau block2Board() thì luôn thấy ô bị chiếm → false positive
            if (isGameOver()) break;
            block2Board(); // vẽ block mới lên board
        }

        // DELAY — tốc độ tăng dần theo level (tối thiểu 80ms)
        int speed = max(80, 300 - level * 20);
        delay(speed);
    }

    gotoxy(23, 0);
    cout << "GAME OVER!" << endl;
    return 0;
}