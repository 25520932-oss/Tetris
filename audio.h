#ifndef AUDIO_H
#define AUDIO_H

#include <SFML/Audio.hpp>
#include <iostream>

enum class SoundEffect {
    MOVE,
    ROTATE,
    HARD_DROP,
    CLEAR_LINE,
    GAME_OVER,
    LEVEL_UP,
    JOINT
};

class Audio {
private:
    // Nhạc nền
    sf::Music bgMusic;

    // Buffer (chứa dữ liệu file âm thanh)
    sf::SoundBuffer moveBuffer;
    sf::SoundBuffer rotateBuffer;
    sf::SoundBuffer dropBuffer;
    sf::SoundBuffer clearBuffer;
    sf::SoundBuffer jointBuffer;
    sf::SoundBuffer levelUpBuffer;
    sf::SoundBuffer gameOverBuffer;

    // Máy phát (phát cái Buffer ở trên)
    sf::Sound moveSound;
    sf::Sound rotateSound;
    sf::Sound dropSound;
    sf::Sound clearSound;
    sf::Sound jointSound;
    sf::Sound levelUpSound;
    sf::Sound gameOverSound;

public:
    Audio();
    ~Audio();

    bool init();                 
    bool loadMedia();            
    void playBGM();              
    void stopBGM();              
    void playSFX(SoundEffect effect); 
    void close();                

    // Ép kiểu nhận vào thang điểm từ 0 -> 10 (từ UI gửi sang)
    void setMusicVolume(int volume); 
    void setSFXVolume(int volume);   
};
extern Audio gameAudio;
#endif