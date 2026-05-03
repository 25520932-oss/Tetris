#ifndef BOARD_H
#define BOARD_H

#include "data.h"

// XÓA TOÀN BỘ BOARD
void clearBoard();

// KIỂM TRA
bool isInside(int x, int y);
bool isEmpty(int x, int y);

// GHI / ĐỌC
void setCell(int x, int y, char value);
char getCell(int x, int y);

#endif