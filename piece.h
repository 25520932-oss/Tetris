#ifndef PIECE_H
#define PIECE_H

#include "data.h"

// Spawn block đầu tiên (khởi tạo current + toàn bộ next queue)
void spawnBlock();

// Di chuyển block (dx: delta cột, dy: delta hàng)
// Trả về true nếu di chuyển thành công
bool moveBlock(int dx, int dy);

// Xoay block 90° theo chiều kim đồng hồ
// Tự hoàn tác nếu sau xoay bị va chạm
void rotateBlock();

#endif