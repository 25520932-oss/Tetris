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
const char I_INITIAL[4][4] = {
    {' ', ' ', ' ', ' '},
    {'I', 'I', 'I', 'I'},
    {' ', ' ', ' ', ' '},
    {' ', ' ', ' ', ' '}
};

class IPiece : public Piece {
private:
    int rotationState; // 0: Ngang, 1: Dọc
public:
    IPiece(){ resetShape(); }
    char getCell(int i, int j) const override { return shape[i][j]; }
    void resetShape() override {
        copyShape(I_INITIAL);
        rotationState = 0; 
    }
    void rotate() override {
        if (rotationState == 0) {
            // Chuyển sang trạng thái Dọc
            char verticalI[4][4] = {
                {' ', 'I', ' ', ' '},
                {' ', 'I', ' ', ' '},
                {' ', 'I', ' ', ' '},
                {' ', 'I', ' ', ' '}
            };
            copyShape(verticalI);
            rotationState = 1;
        } else {
            // Quay về trạng thái Ngang
            copyShape(I_INITIAL);
            rotationState = 0;
        }
    }
};


//  O PIECE — override rotate() thành no-op (khối vuông không đổi)
const char O_INITIAL[4][4] = {
    {' ', ' ', ' ', ' '},
    {' ', 'O', 'O', ' '},
    {' ', 'O', 'O', ' '},
    {' ', ' ', ' ', ' '}
};

class OPiece : public Piece {
public:
    OPiece() { resetShape(); }
    char getCell(int i, int j) const override { return shape[i][j]; }
    
    void resetShape() override { copyShape(O_INITIAL); }

    // OVERRIDE hàm rotate(): Khối vuông xoay không đổi nên ta làm rỗng (No-op)
    void rotate() override {
        // Không làm gì cả
    }
};

//  T, S, Z, J, L — dùng rotate() mặc định từ base Piece

// class TPiece : public Piece {
// public:
  
// };

// class SPiece : public Piece {
// public:
   
// };

// class ZPiece : public Piece {
// public:
 
// };

// class JPiece : public Piece {
// public:
    
// };

// class LPiece : public Piece {
// public:
 
// };

const char T_INITIAL[4][4] = {
    {' ', ' ', ' ', ' '},
    {' ', ' ', 'T', ' '},
    {' ', 'T', 'T', 'T'},
    {' ', ' ', ' ', ' '}
};

class TPiece : public Piece {
private:
    int rotationState; // 0: Trạng thái ban đầu, 1: X
public:
    TPiece() { resetShape(); }
    char getCell(int i, int j) const override { return shape[i][j]; }
    void resetShape() override { copyShape(T_INITIAL); }
    void rotate() override {
        if (rotationState == 0) {
            // Chuyển sang trạng thái Dọc
            char verticalT[4][4] = {
                {' ', ' ', ' ', ' '},
                {' ', ' ', 'T', ' '},
                {' ', ' ', 'T', 'T'},
                {' ', ' ', 'T', ' '}
            };
            copyShape(verticalT);
            rotationState = 1;}

        else if (rotationState == 1) {
            // Chuyển sang trạng thái Ngang ngược
            char invertedT[4][4] = {
                {' ', ' ', ' ', ' '},
                {' ', ' ', ' ', ' '},
                {' ', 'T', 'T', 'T'},
                {' ', ' ', 'T', ' '}
            };
            copyShape(invertedT);
            rotationState = 2;
        } else if (rotationState == 2) {
            // Chuyển sang trạng thái Dọc ngược
            char verticalInvertedT[4][4] = {
                {' ', ' ', ' ', ' '},
                {' ', ' ', 'T', ' '},
                {' ', 'T', 'T', ' '},
                {' ', ' ', 'T', ' '}
            };
            copyShape(verticalInvertedT);
            rotationState = 3;
        } else {
            // Quay về trạng thái ban đầu
            copyShape(T_INITIAL);
            rotationState = 0;
        }
    }
};

// ==========================================
// 4. S PIECE
// ==========================================
const char S_INITIAL[4][4] = {
    {' ', ' ', ' ', ' '},
    {' ', 'S', 'S', ' '},
    {'S', 'S', ' ', ' '},
    {' ', ' ', ' ', ' '}  
};

class SPiece : public Piece {
public:
    SPiece() { resetShape(); }
    char getCell(int i, int j) const override { return shape[i][j]; }
    void resetShape() override { copyShape(S_INITIAL); }
};

// ==========================================
// 5. Z PIECE
// ==========================================
const char Z_INITIAL[4][4] = {
    {' ', ' ', ' ', ' '},
    {'Z', 'Z', ' ', ' '},
    {' ', 'Z', 'Z', ' '},
    {' ', ' ', ' ', ' '}  
};

class ZPiece : public Piece {
public:
    ZPiece() { resetShape(); }
    char getCell(int i, int j) const override { return shape[i][j]; }
    void resetShape() override { copyShape(Z_INITIAL); }
};

// ==========================================
// 6. J PIECE
// ==========================================
const char J_INITIAL[4][4] = {
    {' ', ' ', ' ', ' '},
    {'J', ' ', ' ', ' '},
    {'J', 'J', 'J', ' '},
    {' ', ' ', ' ', ' '}
};

class JPiece : public Piece {
public:
    JPiece() { resetShape(); }
    char getCell(int i, int j) const override { return shape[i][j]; }
    void resetShape() override { copyShape(J_INITIAL); }
};

// ==========================================
// 7. L PIECE
// ==========================================
const char L_INITIAL[4][4] = {
     {' ', ' ', ' ', ' '},
    {' ', ' ', 'L', ' '},
    {'L', 'L', 'L', ' '},
    {' ', ' ', ' ', ' '}
};

class LPiece : public Piece {
public:
    LPiece() { resetShape(); }
    char getCell(int i, int j) const override { return shape[i][j]; }
    void resetShape() override { copyShape(L_INITIAL); }
};

#endif