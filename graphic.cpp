#include "graphic.h"
#include <thread>
#include <chrono>

void initGraphics() {
#ifdef _WIN32
    SetConsoleOutputCP(65001);
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD dwMode = 0;
    GetConsoleMode(hOut, &dwMode);
    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(hOut, dwMode);
#endif
    std::cout << "\033[?25l";
}

void printCell(char cell) {
    switch (cell) {
        case 'I': std::cout << "\033[96m" << BLOCK_CHAR << RESET; break;
        case 'O': std::cout << "\033[93m" << BLOCK_CHAR << RESET; break;
        case 'T': std::cout << "\033[95m" << BLOCK_CHAR << RESET; break;
        case 'S': std::cout << "\033[92m" << BLOCK_CHAR << RESET; break;
        case 'Z': std::cout << "\033[91m" << BLOCK_CHAR << RESET; break;
        case 'J': std::cout << "\033[94m" << BLOCK_CHAR << RESET; break;
        case 'L': std::cout << "\033[38;5;208m" << BLOCK_CHAR << RESET; break;
        case 'G': std::cout << GHOST << "[]" << RESET; break; // Ký hiệu Ghost Piece
        case 'F': std::cout << "\033[97m" << "██" << RESET; break; // Ký hiệu Flash
        case '#': std::cout << "\033[90m" << WALL_CHAR << RESET; break;
        default:  std::cout << "\033[2m" << BG_CHAR << RESET; break;
    }
}

void drawBoard(char board[20][15]) {
    std::cout << "\033[H";
    for (int i = 0; i < 20; i++) {
        for (int j = 0; j < 15; j++) {
            printCell(board[i][j]);
        }
        std::cout << "\n";
    }
}

// HIỆU ỨNG ĂN ĐIỂM (ANIMATION)
void playClearAnimation(char board[20][15], int row) {
    // Lưu lại trạng thái gốc của hàng
    char originalRow[15];
    for(int j=0; j<15; j++) originalRow[j] = board[row][j];

    // Nháy sáng 2 lần
    for (int flash = 0; flash < 2; flash++) {
        for (int j = 1; j < 14; j++) board[row][j] = 'F'; // 'F' là Flash
        drawBoard(board);
        std::this_thread::sleep_for(std::chrono::milliseconds(50));

        for (int j = 1; j < 14; j++) board[row][j] = ' '; 
        drawBoard(board);
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }
}