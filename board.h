#ifndef BOARD_H
#define BOARD_H

#include "data.h"

bool isInside(int x, int y);
bool isEmpty(int x, int y);
void setCell(int x, int y, char value);
char getCell(int x, int y);

#endif