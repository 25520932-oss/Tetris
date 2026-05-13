#include "piece.h"
#include "data.h"
#include "game.h"
#include <cstdlib>

//ghost block
int calcGhostY() {

    return 0; //return tam
}

//Tạo block đầu tiên
void spawnFirst() {
    currentBlock = (BlockType)(rand() % BLOCK_COUNT);
    for (int i = 0; i < NEXT_COUNT; i++)
        nextQueue[i] = (BlockType)(rand() % BLOCK_COUNT);
    rotation = 0;
    x = W / 2 - 2;
    y = 0;
    hasHeld = false;
}

// TẠO BLOCK MỚI
void spawnBlock() {
    currentBlock = (BlockType)(rand() % BLOCK_COUNT);
     for (int i = 0; i < NEXT_COUNT - 1; i++)
        nextQueue[i] = nextQueue[i + 1];     // dịch queue lên 1
    nextQueue[NEXT_COUNT - 1] = (BlockType)(rand() % BLOCK_COUNT); // thêm block mới
    x = W / 2 - 2;  // FIX: x là cột (ngang), spawn ở giữa board
    y = 0;           // FIX: y là hàng (dọc), spawn ở trên cùng
}

// DI CHUYỂN BLOCK
bool moveBlock(int dx, int dy) {
    boardDelBlock();           // Xóa vị trí cũ khỏi board
 
    if (canMove(dx, dy)) {
        x += dx;               // Cập nhật cột
        y += dy;               // Cập nhật hàng
        block2Board();         // Vẽ lại vị trí mới
        return true;
    }
 
    block2Board();             // Không di chuyển được, vẽ lại vị trí cũ
    return false;
}

// XOAY BLOCK (xoay 90 độ theo chiều kim đồng hồ)
void rotateBlock() {
   

}

//Giữ block vào kho 
void holdBlock() {
    
}
// GHIM BLOCK VÀO BOARD
void lockBlock() {
    block2Board();
}
