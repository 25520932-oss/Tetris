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

bool checkCollision(int nextX, int nextY) {
    for (int i = 0; i < 4; i++) { // Duyệt theo hàng của khối gạch
        for (int j = 0; j < 4; j++) { // Duyệt theo cột của khối gạch
            
            // Nếu ô này trong khối gạch có gạch (khác ' ')
            if (blocks[currentBlock].shape[i][j] != ' ') {
                
                // Tính toán vị trí thực tế của ô này trên bảng game (board)
                int boardX = nextX + j;
                int boardY = nextY + i;

                // 1. Kiểm tra va chạm với biên trái, biên phải
                if (boardX < 0 || boardX >= W) {
                    return true; 
                }

                // 2. Kiểm tra va chạm với đáy (biên dưới)
                if (boardY >= H) {
                    return true;
                }

                // 3. Kiểm tra va chạm với các khối gạch đã cố định trên board
                // (Lưu ý: chỉ kiểm tra nếu boardY >= 0 để tránh lỗi mảng khi gạch mới xuất hiện ở trên cùng)
                // if (boardY >= 0 && board[boardY][boardX] != 0) {
                //     return true;
                // }
            }
        }
    }
    // Nếu đi hết vòng lặp mà không vi phạm điều gì -> Không va chạm
    return false;
}


// XOAY BLOCK (xoay 90 độ theo chiều kim đồng hồ)
void rotateBlock() {
    boardDelBlock();
    
   // 1. Lưu lại trạng thái cũ để kiểm tra va chạm sau khi xoay
    int temp[4][4];
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            temp[i][j] = blocks[currentBlock].shape[i][j];
        }
    }

    // 2. Thực hiện xoay ma trận 90 độ (clockwise)
    // Công thức: mới[j][size - 1 - i] = cũ[i][j]
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            blocks[currentBlock].shape[j][4 - 1 - i] = temp[i][j];
        }
    }


    // 3. KIỂM TRA VA CHẠM 
    // Nếu sau khi xoay mà khối gạch đè vào tường hoặc gạch cũ
    if (checkCollision(x, y)) {
        // Hoàn tác: trả lại trạng thái cũ nếu bị lỗi va chạm
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                blocks[currentBlock].shape[i][j] = temp[i][j];
            }
        }
    }
}


//Giữ block vào kho 
void holdBlock() {
    int nextB;           // Khối sẽ xuất hiện tiếp theo
    int holdB = -1;      // Khối đang được giữ (-1 nghĩa là kho đang trống)
    bool canHold = true; // Biến kiểm soát: chỉ cho phép Hold 1 lần mỗi lượt rơi
    if (!canHold) return; // Nếu đã dùng Hold trong lượt này rồi thì thoát

    boardDelBlock(); // 1. Xóa hình ảnh khối hiện tại đang ở vị trí x, y trên board

    if (holdB == -1) {
        // TRƯỜNG HỢP 1: Chưa có khối nào trong kho Hold
        holdB = b;          // Đưa khối hiện tại vào kho
        b = nextB;          // Lấy khối Next ra để chơi
        nextB = rand() % 7; // Tạo mới khối Next tiếp theo
    } else {
        // TRƯỜNG HỢP 2: Đã có khối trong kho Hold
        int temp = b;       // Hoán đổi khối hiện tại và khối trong kho
        b = holdB;
        holdB = temp;
    }

    // 2. Reset vị trí khối mới về đỉnh bàn cờ
    x = 4; 
    y = 0; 

    // 3. Khóa tính năng Hold lại cho đến khi khối này chạm đáy
    canHold = false;

    if (kbhit()) {
    char c = getch();
    if (c == 'c' || c == 'C') {
        holdBlock(); // Gọi hàm khi người chơi nhấn phím C
    }
    // ... các phím di chuyển khác ...
    } else {
    block2Board();
    removeLine(); // Logic xóa hàng (độc lập)

    // Chuẩn bị cho lượt mới
    b = nextB;
    nextB = rand() % 7;
    x = 4; y = 0;
    
    canHold = true; // QUAN TRỌNG: Mở khóa Hold tại đây
}

}
// GHIM BLOCK VÀO BOARD
void lockBlock() {
    block2Board();
}
