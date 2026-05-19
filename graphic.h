#ifndef GRAPHIC_H
#define GRAPHIC_H

#include "data.h"
#include <SFML/Graphics.hpp>

// Kích thước ô (pixel)
const int CELL = 30;

//Bảng màu theo BlockType
extern const sf::Color PIECE_COLORS[BLOCK_COUNT];

//Màu giao diện chung
extern const sf::Color COL_BG;
extern const sf::Color COL_BOARD;
extern const sf::Color COL_GRID;
extern const sf::Color COL_WALL;
extern const sf::Color COL_LOCKED;
extern const sf::Color COL_PANEL;
extern const sf::Color COL_BORDER;
extern const sf::Color COL_LABEL;
extern const sf::Color COL_VALUE;

//Hàm vẽ ô đơn và shape khối
void drawCell(sf::RenderWindow& win, float px, float py, sf::Color col);

void drawPieceShape(sf::RenderWindow& win, sf::Font& font,
    float px, float py, BlockType type);

#endif