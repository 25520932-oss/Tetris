#ifndef GRAPHIC_H
#define GRAPHIC_H

#include <iostream>
#include <string>

#ifdef _WIN32
#include <windows.h>
#endif

// Sử dụng mã Escape cho ký tự Full Block (U+2588)
#define BLOCK_CHAR "\xe2\x96\x88\xe2\x96\x88" 
#define WALL_CHAR  "\xe2\x96\x92\xe2\x96\x92"
#define BG_CHAR    "\xc2\xb7 " 

void initGraphics();
void drawBoard(char board[20][15]);

#endif