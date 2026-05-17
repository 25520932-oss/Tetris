#ifndef AUDIO_H
#define AUDIO_H

#include <string>
#include <iostream>

#include <SDL2/SDL_mixer.h>

// Định nghĩa các event âm thanh trong game
// Trong audio.h, sửa lại enum này:
enum class SoundEffect {
    MOVE,
    ROTATE,
    HARD_DROP,   // Hit_block.wav
    CLEAR_LINE,  // Destroy_line.wav
    GAME_OVER,
    LEVEL_UP,    // Cho file Level_Up
    JOINT        // Cho file Block.wav (lúc khối chạm đáy/khớp vào nhau)
};



class Audio {
private:
    Mix_Music* bgMusic;
    Mix_Chunk* moveSound;
    Mix_Chunk* rotateSound;
    Mix_Chunk* dropSound;
    Mix_Chunk* clearSound;
    Mix_Chunk* tetrisSound;
    Mix_Chunk* gameOverSound;

public:
    Audio();
    ~Audio();

    bool init();                 // Khởi tạo hệ thống audio
    bool loadMedia();            // Load file .wav, .mp3 từ thư mục assets
    void setMusicVolume(int volume); // Chỉnh nhạc nền (BGM)
    void setSFXVolume(int volume);   // Chỉnh hiệu ứng (Khối rơi, ăn hàng...)
    void playBGM();              // Bật nhạc nền
    void stopBGM();              // Tắt nhạc nền
    void playSFX(SoundEffect effect); // Phát hiệu ứng (SFX)
    void close();                // Giải phóng bộ nhớ khi tắt game
};

#endif