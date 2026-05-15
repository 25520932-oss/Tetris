#include "graphic.h"

void initGraphics() {
#ifdef _WIN32
    // Ép Console dùng bảng mã UTF-8 (65001)
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);

    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD dwMode = 0;
    GetConsoleMode(hOut, &dwMode);
    // Bật xử lý mã màu ANSI
    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(hOut, dwMode);
#endif
    // Ẩn con trỏ chuột cho chuyên nghiệp
    std::cout << "\033[?25l";
}

void printCell(char cell) {
    switch (cell) {
    case 'I': std::cout << "\033[96m" << BLOCK_CHAR << "\033[0m"; break;
    case 'O': std::cout << "\033[93m" << BLOCK_CHAR << "\033[0m"; break;
    case 'T': std::cout << "\033[95m" << BLOCK_CHAR << "\033[0m"; break;
    case 'S': std::cout << "\033[92m" << BLOCK_CHAR << "\033[0m"; break;
    case 'Z': std::cout << "\033[91m" << BLOCK_CHAR << "\033[0m"; break;
    case 'J': std::cout << "\033[94m" << BLOCK_CHAR << "\033[0m"; break;
    case 'L': std::cout << "\033[38;5;208m" << BLOCK_CHAR << "\033[0m"; break;
    case '#': std::cout << "\033[90m" << WALL_CHAR << "\033[0m"; break;
    default:  std::cout << "\033[2m" << BG_CHAR << "\033[0m"; break;
    }
}

void drawBoard(char board[20][15]) {
    // Đưa con trỏ về đầu thay vì xóa màn hình (Mục tiêu: Animation mượt)
    std::cout << "\033[H";
    for (int i = 0; i < 20; i++) {
        for (int j = 0; j < 15; j++) {
            printCell(board[i][j]);
        }
        std::cout << "\n";
    }
}