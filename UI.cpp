#include "UI.h"
#include "audio.h"

// Định nghĩa object ui thật sự nằm ở đây
UI ui; 

// Móc object audio từ bên ngoài vào để chỉnh nhạc
extern Audio gameAudio; 

// Giả sử bro đang dùng mã phím ASCII hoặc enum gì đó
// 72: Lên, 80: Xuống, 75: Trái, 77: Phải (Mã phím Windows Console)
void UI::handleSettingInput(int keyCode) {
    if (!isMenuSettingOpen) return;

    // Bấm LÊN hoặc XUỐNG để đổi dòng
    if (keyCode == 72 || keyCode == 80) {
        isSelectingMusic = !isSelectingMusic;
    }

    if (isSelectingMusic) {
        if (keyCode == 75) { // Trái
            currentMusicVol--;
            if (currentMusicVol < 0) currentMusicVol = 0;
            gameAudio.setMusicVolume(currentMusicVol * 12); 
        }
        else if (keyCode == 77) { // Phải
            currentMusicVol++;
            if (currentMusicVol > 10) currentMusicVol = 10;
            gameAudio.setMusicVolume(currentMusicVol * 12);
        }
    } 
    else {
        if (keyCode == 75) { // Trái
            currentSFXVol--;
            if (currentSFXVol < 0) currentSFXVol = 0;
            gameAudio.setSFXVolume(currentSFXVol * 12);
            gameAudio.playSFX(SoundEffect::MOVE); 
        }
        else if (keyCode == 77) { // Phải
            currentSFXVol++;
            if (currentSFXVol > 10) currentSFXVol = 10;
            gameAudio.setSFXVolume(currentSFXVol * 12);
            gameAudio.playSFX(SoundEffect::MOVE); 
        }
    }
}