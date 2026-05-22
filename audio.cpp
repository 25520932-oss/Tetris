#include "audio.h"

Audio gameAudio;
Audio::Audio() {}
Audio::~Audio() {}

bool Audio::init() {
    // SFML tự động lo phần khởi tạo thiết bị âm thanh ngầm bên dưới
    // Bro không cần gọi hàm init phức tạp như SDL2 nữa
    return true;
}

bool Audio::loadMedia() {
    bool success = true;

    // Dùng openFromFile cho nhạc nền (Stream trực tiếp)
    if (!bgMusic.openFromFile("Path_of_sound_tetris/Sound/Theme.wav")) {
        std::cerr << "Loi load nhac nen!\n";
        success = false;
    }
    bgMusic.setLoop(true); // Lặp vô hạn

    // Dùng loadFromFile cho Buffer hiệu ứng ngắn
    if (!moveBuffer.loadFromFile("Path_of_sound_tetris/Sound/Move.wav")) success = false;
    if (!rotateBuffer.loadFromFile("Path_of_sound_tetris/Sound/Rotate.wav")) success = false;
    if (!dropBuffer.loadFromFile("Path_of_sound_tetris/Sound/Hit_block.wav")) success = false;
    if (!clearBuffer.loadFromFile("Path_of_sound_tetris/Sound/Destroy_line.wav")) success = false;
    if (!jointBuffer.loadFromFile("Path_of_sound_tetris/Sound/Block.wav")) success = false;
    if (!levelUpBuffer.loadFromFile("Path_of_sound_tetris/Sound/Level_Up.wav")) success = false;
    if (!gameOverBuffer.loadFromFile("Path_of_sound_tetris/Sound/Game_Over.wav")) success = false;

    // Nạp đạn (Gắn buffer vào máy phát)
    moveSound.setBuffer(moveBuffer);
    rotateSound.setBuffer(rotateBuffer);
    dropSound.setBuffer(dropBuffer);
    clearSound.setBuffer(clearBuffer);
    jointSound.setBuffer(jointBuffer);
    levelUpSound.setBuffer(levelUpBuffer);
    gameOverSound.setBuffer(gameOverBuffer);

    return success;
}

void Audio::playBGM() {
    if (bgMusic.getStatus() != sf::SoundSource::Playing) {
        bgMusic.play();
    }
}

void Audio::stopBGM() {
    bgMusic.stop();
}

void Audio::playSFX(SoundEffect effect) {
    // Gọi hàm .play() trên máy phát. 
    // SFML xử lý rất thông minh: nếu gọi play() liên tục trên cùng 1 sound (VD: Move liên tục),
    // nó sẽ tự ngắt tiếng cũ để phát tiếng mới -> Chống dội âm y hệt như chia Channel ở SDL2!
    switch (effect) {
        case SoundEffect::MOVE:       moveSound.play(); break;
        case SoundEffect::ROTATE:     rotateSound.play(); break;
        case SoundEffect::HARD_DROP:  dropSound.play(); break;
        case SoundEffect::CLEAR_LINE: clearSound.play(); break;
        case SoundEffect::JOINT:      jointSound.play(); break;
        case SoundEffect::LEVEL_UP:   levelUpSound.play(); break;
        case SoundEffect::GAME_OVER:  gameOverSound.play(); break;
    }
}

void Audio::close() {
    // SFML tự động giải phóng RAM khi tắt game, không cần viết Mix_FreeChunk dài dòng nữa.
    stopBGM();
}

void Audio::setMusicVolume(int volume) {
    // SFML dùng thang âm lượng từ 0.0f đến 100.0f
    // Ui của bro đang gửi vào thang 0->10, nên nhân với 10 là đẹp
    if (volume < 0) volume = 0;
    if (volume > 10) volume = 10;
    bgMusic.setVolume(volume * 10.0f);
}

void Audio::setSFXVolume(int volume) {
    if (volume < 0) volume = 0;
    if (volume > 10) volume = 10;
    
    float vol = volume * 10.0f;
    moveSound.setVolume(vol);
    rotateSound.setVolume(vol);
    dropSound.setVolume(vol);
    clearSound.setVolume(vol);
    jointSound.setVolume(vol);
    levelUpSound.setVolume(vol);
    gameOverSound.setVolume(vol);
}