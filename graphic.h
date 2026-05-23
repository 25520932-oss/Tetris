#ifndef GRAPHIC_H
#define GRAPHIC_H

#include "data.h"
#include <SFML/Graphics.hpp>
#include <thread>
#include <chrono>

//Kích thước ô (pixel) 
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

// [NEW] Ghost piece (bóng mờ dự đoán) và flash khi xóa hàng
extern const sf::Color COL_GHOST;
extern const sf::Color COL_FLASH;

//       đổi sang BlockType
sf::Color getPieceColor(BlockType type, sf::Uint8 alpha = 255);

//drawCell — ô đơn với bóng + highlight
void drawCell(sf::RenderWindow& win, float px, float py, sf::Color col);

//  drawGhostCell — ô ghost: trong suốt, chỉ viền màu mờ 
void drawGhostCell(sf::RenderWindow& win, float px, float py, sf::Color col);

// drawPieceShape — shape 4×4, căn giữa trong vùng px,py
void drawPieceShape(sf::RenderWindow& win, sf::Font& font,
    float px, float py, BlockType type);

//drawGhostPiece — bóng mờ dự đoán vị trí rơi
void drawGhostPiece(sf::RenderWindow& win,
    float boardOriginX, float boardOriginY);

// drawOmbreBackground — nền gradient tím sẫm 
void drawOmbreBackground(sf::RenderWindow& win);

//playClearAnimation — flash trắng hàng vừa xóa
void playClearAnimation(sf::RenderWindow& win, sf::Font& fnt,
    const int* rows, int rowCount,
    float boardOriginX, float boardOriginY);

#endif