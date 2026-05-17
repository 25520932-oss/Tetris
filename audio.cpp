#include "audio.h"

Audio::Audio() {
    bgMusic = nullptr;
    moveSound = nullptr;
    rotateSound = nullptr;
    dropSound = nullptr;
    clearSound = nullptr;
    tetrisSound = nullptr;
    gameOverSound = nullptr;
}

Audio::~Audio() {
    close();
}

bool Audio::init() {
    // Khởi tạo SDL_mixer với tần số 44100Hz, 2 channel (Stereo)
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        std::cerr << "Khong the khoi tao SDL_mixer! Loi: " << Mix_GetError() << "\n";
        return false;
    }
    return true;
}

bool Audio::loadMedia() {
    bool success = true;

    // Load nhạc nền (thường dùng mp3 hoặc ogg cho nhẹ)
    bgMusic = Mix_LoadMUS("Path_of_sound_tetris/Sound/Theme.mp3"); 
    if (bgMusic == nullptr) {
        std::cerr << "Loi load nhac nen! " << Mix_GetError() << "\n";
        success = false;
    }

    // Load hiệu ứng âm thanh (dùng .wav để play tức thì, không bị delay)
    moveSound = Mix_LoadWAV("Path_of_sound_tetris/Sound/Move.wav"); //di chuyển
    rotateSound = Mix_LoadWAV("Path_of_sound_tetris/Sound/Rotate.wav"); //xoay khối
    dropSound = Mix_LoadWAV("Path_of_sound_tetris/Sound/Hit_block.wav"); //rơi = nút space
    clearSound = Mix_LoadWAV("Path_of_sound_tetris/Sound/Destroy_line.wav"); //xóa dòng
    gameOverSound = Mix_LoadWAV("Path_of_sound_tetris/Sound/GameOver.wav"); //just game over =)))
    LevelUp = Mix_LoadWAV("Path_of_sound_tetris/Sound/Level_Up.wav"); //thăng cấp
    jointSound = Mix_LoadWAV("Path_of_sound_tetris/Sound/Block.wav"); //khối khớp

    // Check xem có file nào bị miss không
    if (!moveSound || !rotateSound || !dropSound || !clearSound || !tetrisSound || !gameOverSound) {
        std::cerr << "Loi load file SFX! Kiem tra lai duong dan. " << Mix_GetError() << "\n";
        success = false;
    }

    return success;
}

void Audio::playBGM() {
    // Check nếu nhạc chưa chạy thì bật, lặp vô hạn (tham số -1)
    if (Mix_PlayingMusic() == 0) {
        Mix_PlayMusic(bgMusic, -1);
    }
}

void Audio::stopBGM() {
    Mix_HaltMusic();
}

void Audio::playSFX(SoundEffect effect) {
    switch (effect) {
        case SoundEffect::MOVE:
            // Channel 1 cho di chuyển ngang
            Mix_PlayChannel(1, moveSound, 0); 
            break;
            
        case SoundEffect::ROTATE:
            // Channel 2 cho xoay khối
            Mix_PlayChannel(2, rotateSound, 0);
            break;
            
        case SoundEffect::JOINT:
            // Channel 3 cho tiếng chạm đáy bình thường
            Mix_PlayChannel(3, jointSound, 0);
            break;
            
        case SoundEffect::HARD_DROP:
            // Để channel tự do (-1) để tiếng đập rầm dứt khoát
            Mix_PlayChannel(-1, dropSound, 0);
            break;
            
        case SoundEffect::CLEAR_LINE:
            // Tiếng vỡ khối để tự do, vang lên song song với Hard drop
            Mix_PlayChannel(-1, clearSound, 0);
            break;
            
        case SoundEffect::LEVEL_UP:
            // Qua màn mới
            Mix_PlayChannel(-1, LevelUp, 0);
            break;
            
        case SoundEffect::GAME_OVER:
            Mix_PlayChannel(-1, gameOverSound, 0);
            break;
    }
}

void Audio::close() {
    // Dọn dẹp RAM trước khi thoát game
    Mix_FreeChunk(moveSound);
    Mix_FreeChunk(rotateSound);
    Mix_FreeChunk(dropSound);
    Mix_FreeChunk(clearSound);
    
    // Thêm 2 dòng này để giải phóng 2 âm thanh mới
    Mix_FreeChunk(LevelUp);      
    Mix_FreeChunk(jointSound);   
    
    // Đã XÓA dòng Mix_FreeChunk(tetrisSound);
    Mix_FreeChunk(gameOverSound);

    moveSound = nullptr;
    rotateSound = nullptr;
    dropSound = nullptr;
    clearSound = nullptr;
    
    // Reset 2 con trỏ mới
    LevelUp = nullptr;           
    jointSound = nullptr;        
    
    // Đã XÓA dòng tetrisSound = nullptr;
    gameOverSound = nullptr;

    Mix_FreeMusic(bgMusic);
    bgMusic = nullptr;

    // Đóng hệ thống audio
    Mix_Quit();
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