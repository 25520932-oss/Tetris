#include "render.h"
#include "graphic.h"
#include "piece_class.h"
#include <string>

sf::RenderWindow window;
sf::Font         font;

//ve bang hinh chu nhat
static void drawRect(float x, float y, float w, float h,
    sf::Color fill,
    sf::Color outline = sf::Color::Transparent,
    float thick = 0.f) {
    sf::RectangleShape r({ w, h });
    r.setPosition(x, y);
    r.setFillColor(fill);
    if (thick > 0.f) {
        r.setOutlineThickness(thick);
        r.setOutlineColor(outline);
    }
    window.draw(r);
}

//drawText
static float drawText(const std::string& str, float x, float y,
    unsigned size, sf::Color color, bool bold = false) {
    sf::Text t;
    t.setFont(font);
    t.setString(str);
    t.setCharacterSize(size);
    t.setFillColor(color);
    if (bold) t.setStyle(sf::Text::Bold);
    t.setPosition(x, y);
    window.draw(t);
    return t.getLocalBounds().width;
}

//drawPanel
static void drawPanel(float px, float py, float pw, float ph,
    const std::string& title = "") {
    drawRect(px, py, pw, ph, COL_PANEL, COL_BORDER, 1.5f);
    if (!title.empty()) {
        float tw = drawText(title, 0, 0, 13, COL_LABEL);
        drawText(title, px + (pw - tw) / 2.f, py - 18.f, 13, COL_LABEL);
    }
}

void initRender() {
    window.create(sf::VideoMode(WIN_W, WIN_H), "Tetris",
        sf::Style::Titlebar | sf::Style::Close);
    window.setFramerateLimit(60);

    if (!font.loadFromFile("arial.ttf"))
        if (!font.loadFromFile("C:/Windows/Fonts/arial.ttf"))
            if (!font.loadFromFile("/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf"))
                font.loadFromFile("/System/Library/Fonts/Helvetica.ttc");
}

void renderBoard() {
    const float OX = (float)SIDE_W;
    const float OY = 0.f;

    // Nền board (toàn bộ W*H)
    drawRect(OX, OY, (float)BOARD_PX, (float)WIN_H, COL_BOARD);

    for (int i = 0; i <= H; i++)
        drawRect(OX, OY + i * CELL, (float)BOARD_PX, 1.f, COL_GRID);
    for (int j = 0; j <= W; j++)
        drawRect(OX + j * CELL, OY, 1.f, (float)WIN_H, COL_GRID);

    for (int i = 0; i < H; i++) {
        for (int j = 0; j < W; j++) {
            char cell = board[i][j];
            float px = OX + j * CELL;   // [FIX] j thay vì (j-1)
            float py = OY + i * CELL;   // [FIX] i thay vì (i-1)

            if (cell == CELL_BLOCK) {
                drawCell(window, px, py, COL_LOCKED);
            }
            else if (cell == CELL_WALL) {
                drawRect(px, py, CELL, CELL, COL_WALL);
            }
        }
    }

    // Vẽ piece hiện tại với màu đúng
    if (currentBlock != NONE) {
        sf::Color col = PIECE_COLORS[currentBlock];
        for (int i = 0; i < 4; i++)
            for (int j = 0; j < 4; j++)
                if (pieces[currentBlock]->getCell(i, j) != CELL_EMPTY) {
                    int bi = y + i;
                    int bj = x + j;
                    if (bi >= 0 && bi < H && bj >= 0 && bj < W)  // [FIX] bound đủ H,W
                        drawCell(window,
                            OX + bj * CELL,   // [FIX] bj thay vì (bj-1)
                            OY + bi * CELL,    // [FIX] bi thay vì (bi-1)
                            col);
                }
    }

    // Viền trái/phải board
    drawRect(OX - 2.f, OY, 2.f, (float)WIN_H, COL_BORDER);
    drawRect(OX + BOARD_PX, OY, 2.f, (float)WIN_H, COL_BORDER);
}

void renderHoldBox() {
    const float PANEL_W = SIDE_W - 20.f;
    const float PANEL_H = 4.f * CELL + 16.f;
    const float PX = 10.f;
    const float PY = 30.f;

    drawPanel(PX, PY, PANEL_W, PANEL_H, "HOLD");

    drawPieceShape(window, font,
        PX + (PANEL_W - 4.f * CELL) / 2.f, PY + 8.f,
        holdBlock);
}

void renderNextQueue() {
    const float PANEL_W = SIDE_W - 20.f;
    const float SLOT_H = 4.f * CELL + 12.f;
    const float PX = (float)(SIDE_W + BOARD_PX) + 10.f;
    const float PY_START = 30.f;

    float totalH = NEXT_COUNT * SLOT_H + 8.f;
    drawPanel(PX, PY_START, PANEL_W, totalH, "NEXT");

    for (int k = 0; k < NEXT_COUNT; k++) {
        float slotY = PY_START + 8.f + k * SLOT_H;
        float shapeX = PX + (PANEL_W - 4.f * CELL) / 2.f;
        // [CHANGED] drawPieceShape từ graphic.cpp
        drawPieceShape(window, font, shapeX, slotY, nextQueue[k]);

        if (k < NEXT_COUNT - 1)
            drawRect(PX + 8.f, slotY + SLOT_H - 1.f,
                PANEL_W - 16.f, 1.f, COL_GRID);
    }
}

//thong so
void renderStats() {
    const float PANEL_W = SIDE_W - 20.f;
    const float PX = 10.f;
    float       PY = 30.f + 4.f * CELL + 16.f + 20.f;

    struct Stat { const char* label; int value; };
    Stat stats[] = {
        { "SCORE",      score       },
        { "HIGH SCORE", highScore   },
        { "LINES",      linesCleared },
        { "LEVEL",      level       },
    };

    for (auto& s : stats) {
        const float BOX_H = 44.f;
        drawPanel(PX, PY, PANEL_W, BOX_H, s.label);

        std::string val = std::to_string(s.value);
        sf::Text t;
        t.setFont(font);
        t.setString(val);
        t.setCharacterSize(20);
        t.setStyle(sf::Text::Bold);
        t.setFillColor(COL_VALUE);
        float tw = t.getLocalBounds().width;
        t.setPosition(PX + (PANEL_W - tw) / 2.f, PY + 12.f);
        window.draw(t);

        PY += BOX_H + 22.f;
    }
}

void render() {
    window.clear(COL_BG);

    renderBoard();
    renderHoldBox();
    renderNextQueue();
    renderStats();

    window.display();
}