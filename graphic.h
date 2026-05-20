#ifndef GRAPHIC_H
#define GRAPHIC_H

#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>

#ifdef _WIN32
#include <windows.h>
#endif

const int BOARD_ROWS = 20; // Số hàng
const int BOARD_COLS = 15; // Số cột (bao gồm cả 2 cột tường xám biên)
const int CELL_SIZE = 32;  // Kích thước 1 ô vuông (pixel)

const int DASHBOARD_WIDTH_COLS = 6; // Chiều rộng vùng mở rộng trơn mỗi bên (tính bằng số ô)

const std::string RESET = "\033[0m";
const std::string FLASH = "\033[97m\033[5m";
const std::string GHOST = "\033[90m";

void initGraphics();
bool isGraphicsOpen();
void handleGraphicsEvents();
sf::RenderWindow* getRenderWindow();
void drawBoard(char board[BOARD_ROWS][BOARD_COLS], char pieceType, int pieceMatrix[4][4], float visualX, float visualY);
void playClearAnimation(char board[BOARD_ROWS][BOARD_COLS], int row);

#endif