#include "graphic.h"
#include <thread>
#include <chrono>

static sf::RenderWindow* window = nullptr;

sf::RenderWindow* getRenderWindow() {
    return window;
}

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

    unsigned int totalCols = BOARD_COLS + (2 * DASHBOARD_WIDTH_COLS);
    unsigned int windowWidth = totalCols * CELL_SIZE;
    unsigned int windowHeight = BOARD_ROWS * CELL_SIZE;

    window = new sf::RenderWindow(sf::VideoMode(windowWidth, windowHeight), "Tetris Ultra Smooth Edition - Fixed Background", sf::Style::Close);
    window->setFramerateLimit(60);
}

bool isGraphicsOpen() {
    return (window != nullptr && window->isOpen());
}

void handleGraphicsEvents() {
    if (window == nullptr) return;
    sf::Event event;
    while (window->pollEvent(event)) {
        if (event.type == sf::Event::Closed) window->close();
    }
}

sf::Color getPieceColor(char type, int alpha = 255) {
    switch (type) {
    case 'I': return sf::Color(0, 240, 240, alpha);
    case 'O': return sf::Color(240, 240, 0, alpha);
    case 'T': return sf::Color(160, 0, 240, alpha);
    case 'S': return sf::Color(0, 240, 0, alpha);
    case 'Z': return sf::Color(240, 0, 0, alpha);
    case 'J': return sf::Color(0, 0, 240, alpha);
    case 'L': return sf::Color(240, 128, 0, alpha);
    case '#': return sf::Color(60, 60, 65, alpha);  // Màu tường xám bao quanh biên     
    case 'G': return sf::Color(255, 255, 255, 35); // Ghost Piece (Bóng mờ)
    case 'F': return sf::Color(255, 255, 255, 240); // Flash trắng khi xóa hàng
    default:  return sf::Color(0, 0, 0, 0);
    }
}

void drawBoard(char board[BOARD_ROWS][BOARD_COLS], char pieceType, int pieceMatrix[4][4], float visualX, float visualY) {
    if (window == nullptr || !window->isOpen()) return;

    // Tọa độ bù (Offset) để đẩy toàn bộ bàn cờ logic dịch vào chính giữa cửa sổ
    float boardOffsetX = static_cast<float>(DASHBOARD_WIDTH_COLS * CELL_SIZE);


    sf::RectangleShape innerBackground(sf::Vector2f((BOARD_COLS - 2) * CELL_SIZE, (BOARD_ROWS - 1) * CELL_SIZE));
    innerBackground.setFillColor(sf::Color(10, 18, 32)); // Màu xanh đen chuẩn của lòng bàn cờ cũ
    innerBackground.setPosition(boardOffsetX + CELL_SIZE, 0); // Đặt từ sau hàng tường trái
    window->draw(innerBackground);

    sf::RectangleShape cellRect(sf::Vector2f(CELL_SIZE - 2, CELL_SIZE - 2));
    cellRect.setOutlineThickness(1);

    // 1. Vẽ vùng bàn cờ tĩnh và lưới ngầm
    for (int i = 0; i < BOARD_ROWS; i++) {
        for (int j = 0; j < BOARD_COLS; j++) {
            char cell = board[i][j];
            cellRect.setPosition((j * CELL_SIZE) + boardOffsetX + 1.0f, (i * CELL_SIZE) + 1.0f);

            if (cell != ' ') {
                cellRect.setFillColor(getPieceColor(cell));
                if (cell == '#') cellRect.setOutlineColor(sf::Color(30, 30, 30));
                else cellRect.setOutlineColor(sf::Color(255, 255, 255, 60));
                window->draw(cellRect);
            }
            else {
                // Lưới ngầm mờ ảo vẽ đè lên lớp nền xanh đen vừa tạo
                cellRect.setFillColor(sf::Color(0, 0, 0, 0));
                cellRect.setOutlineColor(sf::Color(255, 255, 255, 8));
                window->draw(cellRect);
            }
        }
    }

    // 2. Vẽ khối gạch đang rơi tự do
    if (pieceType != ' ') {
        cellRect.setOutlineColor(sf::Color(255, 255, 255, 90));
        cellRect.setFillColor(getPieceColor(pieceType));

        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                if (pieceMatrix[i][j]) {
                    float px = ((visualX + j) * CELL_SIZE) + boardOffsetX + 1.0f;
                    float py = ((visualY + i) * CELL_SIZE) + 1.0f;

                    cellRect.setPosition(px, py);
                    window->draw(cellRect);
                }
            }
        }
    }
}

void playClearAnimation(char board[BOARD_ROWS][BOARD_COLS], int row) {
    if (window == nullptr || !window->isOpen()) return;

    char originalRow[BOARD_COLS];
    for (int j = 0; j < BOARD_COLS; j++) originalRow[j] = board[row][j];

    int dummyMatrix[4][4] = { 0 };
    unsigned int totalCols = BOARD_COLS + (2 * DASHBOARD_WIDTH_COLS);
    float w = static_cast<float>(totalCols * CELL_SIZE);
    float h = static_cast<float>(BOARD_ROWS * CELL_SIZE);

    sf::VertexArray ombreBackground(sf::Quads, 4);

    sf::Color topColor(10, 20, 45);     // Xanh đêm ở trên rìa ngoài
    sf::Color bottomColor(45, 15, 65);  // Sắc tím sẫm ở dưới rìa ngoài

    ombreBackground[0].position = sf::Vector2f(0.f, 0.f); ombreBackground[0].color = topColor;
    ombreBackground[1].position = sf::Vector2f(w, 0.f);   ombreBackground[1].color = topColor;
    ombreBackground[2].position = sf::Vector2f(w, h);     ombreBackground[2].color = bottomColor;
    ombreBackground[3].position = sf::Vector2f(0.f, h);   ombreBackground[3].color = bottomColor;

    for (int flash = 0; flash < 3; flash++) {
        for (int j = 1; j < BOARD_COLS - 1; j++) {
            if (originalRow[j] != ' ' && originalRow[j] != '#') board[row][j] = 'F';
        }
        window->clear();
        window->draw(ombreBackground);
        drawBoard(board, ' ', dummyMatrix, 0, 0);
        window->display();
        std::this_thread::sleep_for(std::chrono::milliseconds(50));

        for (int j = 1; j < BOARD_COLS - 1; j++) {
            if (originalRow[j] != ' ' && originalRow[j] != '#') board[row][j] = ' ';
        }
        window->clear();
        window->draw(ombreBackground);
        drawBoard(board, ' ', dummyMatrix, 0, 0);
        window->display();
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }

    for (int j = 0; j < BOARD_COLS; j++) board[row][j] = originalRow[j];
}