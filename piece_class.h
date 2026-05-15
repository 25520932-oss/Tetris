#ifndef PIECE_CLASS_H
#define PIECE_CLASS_H

#include "data.h"

//  BASE CLASS
//  - shape[4][4]  : hình dạng hiện tại (thay đổi khi xoay)
//  - getCell()    : truy cập ô (pure virtual → bắt buộc override)
//  - rotate()     : xoay 90° CW (virtual → subclass có thể override)
//  - resetShape() : khôi phục shape gốc khi spawn (pure virtual)

class Piece {
public:
    char shape[4][4];

    // Truy cập ô tại hàng i, cột j
    virtual char getCell(int i, int j) const = 0;

    // Xoay 90° CW — hành vi mặc định cho O, T, S, Z, J, L
    // IPiece sẽ override hành vi này
    virtual void rotate() {
        char temp[4][4];
        for (int i = 0; i < 4; i++)
            for (int j = 0; j < 4; j++)
                temp[i][j] = shape[i][j];

        // Công thức CW: new[j][3-i] = old[i][j]
        for (int i = 0; i < 4; i++)
            for (int j = 0; j < 4; j++)
                shape[j][3-i] = temp[i][j];
    }

    // Trả shape về trạng thái ban đầu khi spawn block mới
    virtual void resetShape() = 0;

    virtual ~Piece() {}

protected:
    // Tiện ích: copy src vào shape
    void copyShape(const char src[4][4]) {
        for (int i = 0; i < 4; i++)
            for (int j = 0; j < 4; j++)
                shape[i][j] = src[i][j];
    }
};

//  I PIECE — override rotate() vì chỉ có 2 trạng thái (ngang/dọc)
//  Dùng toggle thay vì xoay ma trận tránh lệch tâm

class IPiece : public Piece {
public:
    IPiece(){}
};

//  O PIECE — override rotate() thành no-op (khối vuông không đổi)
class OPiece : public Piece {
public:
    OPiece() { resetShape(); }
};

//  T, S, Z, J, L — dùng rotate() mặc định từ base Piece

class TPiece : public Piece {
public:
  
};

class SPiece : public Piece {
public:
   
};

class ZPiece : public Piece {
public:
 
};

class JPiece : public Piece {
public:
    
};

class LPiece : public Piece {
public:
 
};

#endif