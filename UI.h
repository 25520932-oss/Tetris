#ifndef UI_H
#define UI_H

class UI {
public:
    // Biến lưu trạng thái
    int currentMusicVol = 5;
    int currentSFXVol = 5;
    bool isMenuSettingOpen = false;
    bool isSelectingMusic = true;

    // Hàm xử lý logic (nhận vào phím bấm từ input)
    void handleSettingInput(int keyCode); 
};

// Khai báo global để các file khác (như render.cpp) xài chung 1 object
extern UI ui; 

#endif