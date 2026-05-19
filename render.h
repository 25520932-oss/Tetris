#ifndef RENDER_H
#define RENDER_H

#include "data.h"
#include "graphic.h" 
#include <SFML/Graphics.hpp>


const int SIDE_W = 160;

const int BOARD_PX = W * CELL;
const int WIN_W = SIDE_W + BOARD_PX + SIDE_W;

const int WIN_H = H * CELL;

extern sf::RenderWindow window;
extern sf::Font          font;

void initRender(); 

void renderBoard(); 
void renderHoldBox();
void renderNextQueue();
void renderStats();

void render();

#endif