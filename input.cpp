#include "input.h"
#include "piece.h"
#include <conio.h>

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

        // Đưa khối xuống đáy ngay
        case ' ':
            while (moveBlock(0, 1));  // FIX: dy=+1
            break;
    }
}