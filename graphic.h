#ifndef GRAPHIC_H
#define GRAPHIC_H

#include <iostream>
#include <string>

#ifdef _WIN32
    #include <windows.h>
    #define BLOCK_CHAR "\xe2\x96\x88\xe2\x96\x88" 
    #define WALL_CHAR  "\xe2\x96\x92\xe2\x96\x92"
    #define BG_CHAR    "\xc2\xb7 " 
#else
    #define BLOCK_CHAR "██"
    #define WALL_CHAR  "▒▒"
    #define BG_CHAR    "· "
#endif

// Mã màu bổ sung cho Animation
const std::string RESET = "\033[0m";
const std::string FLASH = "\033[97m\033[5m"; // Màu trắng + hiệu ứng nhấp nháy (nếu terminal hỗ trợ)
const std::string GHOST = "\033[90m";        // Màu xám đậm cho bóng mờ

void initGraphics();
void drawBoard(char board[20][15]);
void playClearAnimation(char board[20][15], int row); // Hiệu ứng ăn điểm

#endif