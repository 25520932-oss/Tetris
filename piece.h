#ifndef PIECE_H
#define PIECE_H

#include "data.h"

// Spawn block kế tiếp từ queue
void spawnBlock();

// Trả về true nếu di chuyển thành công
bool moveBlock(int dx, int dy);

// Xoay block 90° CW; tự hoàn tác nếu va chạm
void rotateBlock();

// Hold block hiện tại (chỉ 1 lần mỗi lượt)
void doHoldBlock();

//Để tạo âm thanh cho xóa khối
void lockBlock();

#endif