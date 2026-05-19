#include "input.h"
#include "piece.h"
#include <conio.h>
#include "UI.h"

// XỬ LÝ INPUT
// Convention: moveBlock(dx, dy) — dx: delta cột (trái/phải), dy: delta hàng (xuống)
void processInput() {
    if (!_kbhit()) return;

    char key = _getch();

    switch (key) {
        // DI CHUYỂN NGANG
        case 'a': // trái
        case 'A':
            moveBlock(-1, 0);  // FIX: dx=-1 (sang trái), dy=0
            break;

        case 'd': // phải
        case 'D':
            moveBlock(1, 0);   // FIX: dx=+1 (sang phải), dy=0
            break;

        case 's': // xuống nhanh
        case 'S':
            moveBlock(0, 1);   // FIX: dx=0, dy=+1 (xuống 1 hàng)
            break;

        // XOAY
        case 'w':
        case 'W':
            rotateBlock();
            break;
        //HOLD
        case 'c':
        case 'C':
            //holdBlock();
            break;
        // Đưa khối xuống đáy ngay
        case ' ':
            while (moveBlock(0, 1));  // FIX: dy=+1
            break;
    }
}

void handleInput() {
    // 1. Kiểm tra xem người dùng có đang gõ phím nào không
    if (_kbhit()) { 
        
        // 2. Lấy mã phím vừa gõ
        int key = _getch(); 

        // 3. XỬ LÝ BẪY PHÍM MŨI TÊN 
        if (key == 224 || key == 0) {
            key = _getch(); 
        }

        // 4. Xử lý ESC (mã 27) để Mở/Đóng Setting
        if (key == 27) {
            ui.isMenuSettingOpen = !ui.isMenuSettingOpen; 
        }

        // 5. CHIA LUỒNG XỬ LÝ PHÍM
        if (ui.isMenuSettingOpen) {
            // Đang mở Setting -> Quăng phím cho UI xử lý (tăng giảm âm lượng)
            ui.handleSettingInput(key);
        } 
        else {
            // Không mở Setting -> Xử lý phím chơi game bình thường
            // Ví dụ:
            // if (key == 75) // Dịch sang trái
            // if (key == 77) // Dịch sang phải
            // if (key == 32) // Bấm Space (mã 32) để rớt khối nhanh
        }
    }
}