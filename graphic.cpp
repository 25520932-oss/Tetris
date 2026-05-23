#include "graphic.h"
#include "piece_class.h"
#include "game.h"       // boardDelBlock(), block2Board(), canMove()
#include <algorithm>    // std::min, std::max



//7 màu theo thứ tự BlockType enum (I O T S Z J L)
const sf::Color PIECE_COLORS[BLOCK_COUNT] = {
    sf::Color(0,   240, 240),   // I – cyan
    sf::Color(240, 240,   0),   // O – yellow
    sf::Color(160,   0, 240),   // T – purple
    sf::Color(0,   240,   0),   // S – green
    sf::Color(240,   0,   0),   // Z – red
    sf::Color(0,     0, 240),   // J – blue
    sf::Color(240, 160,   0),   // L – orange
};

//àu giao diện
const sf::Color COL_BG = sf::Color(15, 15, 20);
const sf::Color COL_BOARD = sf::Color(10, 10, 15);
const sf::Color COL_GRID = sf::Color(35, 35, 45);
const sf::Color COL_WALL = sf::Color(80, 80, 90);
const sf::Color COL_LOCKED = sf::Color(180, 180, 190);
const sf::Color COL_PANEL = sf::Color(22, 22, 30);
const sf::Color COL_BORDER = sf::Color(220, 220, 230);
const sf::Color COL_LABEL = sf::Color(180, 180, 200);
const sf::Color COL_VALUE = sf::Color(255, 255, 255);

// Ghost: viền trắng mờ 
//       Flash: trắng đục 
const sf::Color COL_GHOST = sf::Color(255, 255, 255, 35);
const sf::Color COL_FLASH = sf::Color(255, 255, 255, 220);

// ra màu theo BlockType với alpha tùy chỉnh.
sf::Color getPieceColor(BlockType type, sf::Uint8 alpha) {
    if (type == NONE || type < 0 || type >= BLOCK_COUNT)
        return sf::Color(0, 0, 0, 0);
    sf::Color c = PIECE_COLORS[type];
    c.a = alpha;
    return c;
}

void drawCell(sf::RenderWindow& win, float px, float py, sf::Color col) {
    const float S = (float)CELL;
    const float PAD = 2.f;

    // Bóng ngoài (viền tối)
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

void drawGhostCell(sf::RenderWindow& win, float px, float py, sf::Color col) {
    const float S = (float)CELL;
    const float PAD = 2.f;

    sf::RectangleShape body({ S - PAD * 2, S - PAD * 2 });
    body.setPosition(px + PAD, py + PAD);
    body.setFillColor(sf::Color(0, 0, 0, 0));                    // Hoàn toàn trong suốt
    body.setOutlineThickness(1.5f);
    body.setOutlineColor(sf::Color(col.r, col.g, col.b, 90));    // Viền cùng màu khối, mờ
    win.draw(body);
}

void drawPieceShape(sf::RenderWindow& win, sf::Font& /*font*/,
    float px, float py, BlockType type) {
    if (type == NONE) return;
    sf::Color col = PIECE_COLORS[type];

    // Tìm bounding box của shape
    int minR = 4, maxR = 0, minC = 4, maxC = 0;
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            if (pieces[type]->getCell(i, j) != CELL_EMPTY) {
                minR = std::min(minR, i); maxR = std::max(maxR, i);
                minC = std::min(minC, j); maxC = std::max(maxC, j);
            }

    int rows = maxR - minR + 1;
    int cols = maxC - minC + 1;

    // Căn giữa trong vùng 4×4 CELL
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


void drawOmbreBackground(sf::RenderWindow& win) {
    sf::Vector2u sz = win.getSize();
    float w = (float)sz.x;
    float h = (float)sz.y;

    sf::Color topColor(10, 20, 45);   // Xanh đêm — giống bạn bè
    sf::Color botColor(45, 15, 65);   // Tím sẫm  — giống bạn bè

    sf::VertexArray bg(sf::Quads, 4);
    bg[0] = { sf::Vector2f(0.f, 0.f), topColor };
    bg[1] = { sf::Vector2f(w,   0.f), topColor };
    bg[2] = { sf::Vector2f(w,   h), botColor };
    bg[3] = { sf::Vector2f(0.f, h), botColor };
    win.draw(bg);
}


void playClearAnimation(sf::RenderWindow& win, sf::Font& /*fnt*/,
    const int* rows, int rowCount,
    float boardOriginX, float boardOriginY) {
    if (rowCount <= 0) return;

    // Helper nội bộ: kiểm tra hàng i có trong danh sách flash không
    auto isFlashRow = [&](int i) -> bool {
        for (int k = 0; k < rowCount; k++)
            if (rows[k] == i) return true;
        return false;
        };

    // Helper nội bộ: vẽ board với các hàng flash tô màu flashColor
    auto drawFrame = [&](sf::Color flashColor) {
        win.clear();
        drawOmbreBackground(win);

        for (int i = 0; i < H; i++) {
            for (int j = 0; j < W; j++) {
                char cell = board[i][j];
                float px = boardOriginX + j * CELL;
                float py = boardOriginY + i * CELL;

                if (isFlashRow(i) && cell != CELL_WALL && cell != CELL_EMPTY) {
                    // Ô thuộc hàng flash: tô màu flashColor
                    sf::RectangleShape fc({ (float)CELL - 2.f, (float)CELL - 2.f });
                    fc.setPosition(px + 1.f, py + 1.f);
                    fc.setFillColor(flashColor);
                    win.draw(fc);
                }
                else if (cell == CELL_BLOCK) {
                    drawCell(win, px, py, COL_LOCKED);
                }
                else if (cell == CELL_WALL) {
                    sf::RectangleShape wall({ (float)CELL, (float)CELL });
                    wall.setPosition(px, py);
                    wall.setFillColor(COL_WALL);
                    win.draw(wall);
                }
                // CELL_EMPTY: bỏ qua (nền ombre đã vẽ phía dưới)
            }
        }
        win.display();
        };

    // 3 lần blink: sáng → tối → sáng → tối → sáng → tối
    for (int flash = 0; flash < 3; flash++) {
        drawFrame(COL_FLASH);   // Phase sáng: trắng đục
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
        drawFrame(COL_BOARD);   // Phase tối: tối như nền board
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }
}