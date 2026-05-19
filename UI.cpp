#include "UI.h"
#include "audio.h"


UI ui; 

extern Audio gameAudio; 

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
            gameAudio.setMusicVolume(currentMusicVol); 
        }
        else if (keyCode == 77) { // Phải
            currentMusicVol++;
            if (currentMusicVol > 10) currentMusicVol = 10;
            gameAudio.setMusicVolume(currentMusicVol);
        }
    } 
    else {
        if (keyCode == 75) { // Trái
            currentSFXVol--;
            if (currentSFXVol < 0) currentSFXVol = 0;
            gameAudio.setSFXVolume(currentSFXVol);
            gameAudio.playSFX(SoundEffect::MOVE); 
        }
        else if (keyCode == 77) { // Phải
            currentSFXVol++;
            if (currentSFXVol > 10) currentSFXVol = 10;
            gameAudio.setSFXVolume(currentSFXVol);
            gameAudio.playSFX(SoundEffect::MOVE); 
        }
    }
}