
#include "graphic.h"
#include "piece_class.h"
#include <algorithm>

//Bảng màu theo BlockType
const sf::Color PIECE_COLORS[BLOCK_COUNT] = {
    sf::Color(0,   240, 240),   // I – cyan
    sf::Color(240, 240,   0),   // O – yellow
    sf::Color(160,   0, 240),   // T – purple
    sf::Color(0,   240,   0),   // S – green
    sf::Color(240,   0,   0),   // Z – red
    sf::Color(0,     0, 240),   // J – blue
    sf::Color(240, 160,   0),   // L – orange
};

//Màu giao diện chung
const sf::Color COL_BG = sf::Color(15, 15, 20);
const sf::Color COL_BOARD = sf::Color(10, 10, 15);
const sf::Color COL_GRID = sf::Color(35, 35, 45);
const sf::Color COL_WALL = sf::Color(80, 80, 90);
const sf::Color COL_LOCKED = sf::Color(180, 180, 190);
const sf::Color COL_PANEL = sf::Color(22, 22, 30);
const sf::Color COL_BORDER = sf::Color(220, 220, 230);
const sf::Color COL_LABEL = sf::Color(180, 180, 200);
const sf::Color COL_VALUE = sf::Color(255, 255, 255);

void drawCell(sf::RenderWindow& win, float px, float py, sf::Color col) {
    const float S = (float)CELL;
    const float PAD = 2.f;

    // Bóng ngoài
    sf::RectangleShape shadow({ S, S });
    shadow.setPosition(px, py);
    shadow.setFillColor(col * sf::Color(60, 60, 60));
    win.draw(shadow);

    // Khối chính
    sf::RectangleShape body({ S - PAD * 2, S - PAD * 2 });
    body.setPosition(px + PAD, py + PAD);
    body.setFillColor(col);
    win.draw(body);

    // Highlight trên
    sf::RectangleShape hlTop({ S - PAD * 2, 3.f });
    hlTop.setPosition(px + PAD, py + PAD);
    hlTop.setFillColor(sf::Color(255, 255, 255, 60));
    win.draw(hlTop);

    // Highlight trái
    sf::RectangleShape hlLeft({ 3.f, S - PAD * 2 });
    hlLeft.setPosition(px + PAD, py + PAD);
    hlLeft.setFillColor(sf::Color(255, 255, 255, 60));
    win.draw(hlLeft);
}

void drawPieceShape(sf::RenderWindow& win, sf::Font& /*font*/,
    float px, float py, BlockType type) {
    if (type == NONE) return;
    sf::Color col = PIECE_COLORS[type];

    // Tìm bounding box
    int minR = 4, maxR = 0, minC = 4, maxC = 0;
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            if (pieces[type]->getCell(i, j) != CELL_EMPTY) {
                minR = std::min(minR, i); maxR = std::max(maxR, i);
                minC = std::min(minC, j); maxC = std::max(maxC, j);
            }

    int rows = maxR - minR + 1;
    int cols = maxC - minC + 1;

    // Căn giữa trong ô 4×4
    float offX = (4 * CELL - cols * CELL) / 2.f;
    float offY = (4 * CELL - rows * CELL) / 2.f;

    for (int i = minR; i <= maxR; i++)
        for (int j = minC; j <= maxC; j++)
            if (pieces[type]->getCell(i, j) != CELL_EMPTY)
                drawCell(win,
                    px + offX + (j - minC) * CELL,
                    py + offY + (i - minR) * CELL,
                    col);
}