#ifndef RENDER_H
#define RENDER_H
#include "data.h"  
// DI CHUYỂN CON TRỎ
void gotoxy(int x, int y);

// VẼ GAME
void render();

//Vẽ 4 block tiếp theo
void renderNextQueue();

//Vẽ khung hiển thị điểm hiện tại
void renderScore();

//Vẽ khung hiển thị điểm cao nhất
void renderHighScore();

#endif

