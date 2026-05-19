#include "board.h"

bool isInside(int x, int y) {
    return (x >= 0 && x < H && y >= 0 && y < W);
}

bool isEmpty(int x, int y) {
    return isInside(x, y) && board[x][y] == CELL_EMPTY;
}

void setCell(int x, int y, char value) {
    if (isInside(x, y)) board[x][y] = value;
}

// Trả về CELL_WALL nếu ngoài biên — giúp canMove không cần check biên riêng
char getCell(int x, int y) {
    return isInside(x, y) ? board[x][y] : CELL_WALL;
}
void Audio::setMusicVolume(int volume) {
    // Ép kiểu an toàn, đảm bảo volume không vượt quá 0 - 128
    if (volume < 0) volume = 0;
    if (volume > 128) volume = 128;
    
    // Hàm của SDL_mixer để chỉnh âm lượng nhạc nền
    Mix_VolumeMusic(volume);
}

void Audio::setSFXVolume(int volume) {
    if (volume < 0) volume = 0;
    if (volume > 128) volume = 128;
    
    // Tham số -1 nghĩa là áp dụng mức âm lượng này cho TẤT CẢ các channel SFX hiện có
    Mix_Volume(-1, volume);
}