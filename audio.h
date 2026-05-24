#ifndef AUDIO_H
#define AUDIO_H

#include <SFML/Audio.hpp>
#include <iostream>

// Tui định nghĩa lại enum dựa trên các case bro đã dùng
enum class SoundEffect {
    MOVE,
    ROTATE,
    JOINT,
    HARD_DROP,
    CLEAR_LINE,
    LEVEL_UP,
    GAME_OVER
};

class Audio {
private:
    // Nhạc nền
    sf::Music bgMusic;

    // Buffer: Dùng để lưu trữ dữ liệu âm thanh trong RAM
    sf::SoundBuffer moveBuffer;
    sf::SoundBuffer rotateBuffer;
    sf::SoundBuffer dropBuffer;
    sf::SoundBuffer clearBuffer;
    sf::SoundBuffer gameOverBuffer;
    sf::SoundBuffer levelUpBuffer;
    sf::SoundBuffer jointBuffer;

    // Sound: Cái loa dùng để phát các Buffer ở trên
    sf::Sound moveSound;
    sf::Sound rotateSound;
    sf::Sound dropSound;
    sf::Sound clearSound;
    sf::Sound gameOverSound;
    sf::Sound levelUpSound;
    sf::Sound jointSound;

public:
    Audio();
    ~Audio();

    bool init();
    bool loadMedia();
    void playBGM();
    void stopBGM();
    void playSFX(SoundEffect effect);
    void close();
    
    // SFML dùng thang điểm volume từ 0 đến 100 (float)
    void setMusicVolume(float volume);
    void setSFXVolume(float volume);
};

#endif