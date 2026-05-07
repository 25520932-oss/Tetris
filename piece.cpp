#include "piece.h"
#include "data.h"
#include "game.h"
#include <cstdlib>

// TẠO BLOCK MỚI
void spawnBlock() {
    currentBlock = (BlockType)(rand() % BLOCK_COUNT);
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
    // Tạo shape mới sau khi xoay

}

// GHIM BLOCK VÀO BOARD
void lockBlock() {
    block2Board();
}
