#include "game.h"
#include "piece_class.h"
#include "render.h"   
#include "graphic.h" 
#include "audio.h" 

// Macro tiện để đọc ô của block hiện tại qua virtual dispatch
#define CUR(i,j)  pieces[currentBlock]->getCell(i, j)

// XÓA BLOCK KHỎI BOARD
void boardDelBlock() {
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            if (CUR(i, j) != CELL_EMPTY && y + i < H && x + j < W)
                board[y + i][x + j] = CELL_EMPTY;
}

// GÁN BLOCK LÊN BOARD
void block2Board() {
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            if (CUR(i, j) != CELL_EMPTY)
                board[y + i][x + j] = CELL_BLOCK;
}

// KIỂM TRA CÓ THỂ DI CHUYỂN
bool canMove(int dx, int dy) {
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            if (CUR(i, j) != CELL_EMPTY) {
                int tx = x + j + dx;
                int ty = y + i + dy;
                if (tx < 1 || tx >= W - 1 || ty < 0 || ty >= H - 1)
                    return false;
                if (board[ty][tx] != CELL_EMPTY)
                    return false;
            }
    return true;
}

// XÓA DÒNG ĐẦY
int removeLine() {
    int count = 0;
    int prevLvl = level;

    for (int i = H - 2; i >= 1; i--) {
        bool isFull = true;
        for (int j = 1; j < W - 1; j++)
            if (board[i][j] == CELL_EMPTY) { isFull = false; break; }

        if (isFull) {
            {
                // Flash trắng toàn dòng i trực tiếp trên window hiện tại
                const float OX = (float)SIDE_W;
                const float OY = 0.f;
                for (int flash = 0; flash < 3; flash++) {
                    // Sáng
                    sf::RectangleShape row_flash({ (float)BOARD_PX, (float)CELL });
                    row_flash.setPosition(OX, OY + i * CELL);
                    row_flash.setFillColor(sf::Color(255, 255, 255, 200));
                    window.clear(COL_BG);
                    // Vẽ board bình thường trước
                    for (int ri = 0; ri < H; ri++)
                        for (int rj = 0; rj < W; rj++) {
                            char cell = board[ri][rj];
                            float px = OX + rj * CELL;
                            float py = OY + ri * CELL;
                            if (cell == CELL_BLOCK)
                                drawCell(window, px, py, COL_LOCKED);
                            else if (cell == CELL_WALL) {
                                sf::RectangleShape wsh({ (float)CELL,(float)CELL });
                                wsh.setPosition(px, py);
                                wsh.setFillColor(COL_WALL);
                                window.draw(wsh);
                            }
                        }
                    window.draw(row_flash);
                    window.display();
                    sf::sleep(sf::milliseconds(50));

                    // Tối
                    sf::RectangleShape row_dark({ (float)BOARD_PX, (float)CELL });
                    row_dark.setPosition(OX, OY + i * CELL);
                    row_dark.setFillColor(sf::Color(10, 10, 15, 230));
                    window.clear(COL_BG);
                    for (int ri = 0; ri < H; ri++)
                        for (int rj = 0; rj < W; rj++) {
                            char cell = board[ri][rj];
                            float px = OX + rj * CELL;
                            float py = OY + ri * CELL;
                            if (cell == CELL_BLOCK)
                                drawCell(window, px, py, COL_LOCKED);
                            else if (cell == CELL_WALL) {
                                sf::RectangleShape wsh({ (float)CELL,(float)CELL });
                                wsh.setPosition(px, py);
                                wsh.setFillColor(COL_WALL);
                                window.draw(wsh);
                            }
                        }
                    window.draw(row_dark);
                    window.display();
                    sf::sleep(sf::milliseconds(50));
                }
            }

            count++;
            linesCleared++;

            // Dịch board xuống
            for (int k = i; k > 1; k--)
                for (int j = 1; j < W - 1; j++)
                    board[k][j] = board[k - 1][j];
            for (int j = 1; j < W - 1; j++)
                board[1][j] = CELL_EMPTY;
            i++;
        }
    }

    if (count > 0) {
        const int pts[5] = { 0, 1, 3, 6, 10 };
        score += (count <= 4) ? pts[count] : count * 3;
        if (score > highScore) highScore = score;

        int newLvl = score / 10 + 1;
        level = newLvl;

        if (newLvl > prevLvl)
            gameAudio.playSFX(SoundEffect::LEVEL_UP);
        else
            gameAudio.playSFX(SoundEffect::CLEAR_LINE);
    }

    return count;
}

// KIỂM TRA THUA
bool isGameOver() {
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            if (CUR(i, j) != CELL_EMPTY)
                if (board[y + i][x + j] != CELL_EMPTY)
                    return true;
    return false;
}