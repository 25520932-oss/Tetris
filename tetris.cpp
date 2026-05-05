#include <iostream>
#include <conio.h>
#include <ctime>

// Kiểm tra hệ điều hành để khai báo thư viện phù hợp
#ifdef _WIN32
    #include <windows.h>
#else
    #include <unistd.h>
    #define Sleep(x) usleep(x * 1000) // Chuyển đổi miliseconds sang microseconds cho Mac
#endif

using namespace std;

#define H 20
#define W 15

char board[H][W] = {} ;
char blocks[][4][4] = {
        {{' ','I',' ',' '},
         {' ','I',' ',' '},
         {' ','I',' ',' '},
         {' ','I',' ',' '}},
        {{' ','I',' ',' '},
         {' ','I',' ',' '},
         {' ','I',' ',' '},
         {' ','I',' ',' '}},
        {{' ',' ',' ',' '},
         {' ','O','O',' '},
         {' ','O','O',' '},
         {' ',' ',' ',' '}},
        {{' ',' ',' ',' '},
         {' ','O','O',' '},
         {' ','O','O',' '},
         {' ',' ',' ',' '}},
        {{' ',' ',' ',' '},
         {' ','O','O',' '},
         {' ','O','O',' '},
         {' ',' ',' ',' '}},
        {{' ',' ',' ',' '},
         {' ','O','O',' '},
         {' ','O','O',' '},
         {' ',' ',' ',' '}},
        {{' ',' ',' ',' '},
         {' ','O','O',' '},
         {' ','O','O',' '},
         {' ',' ',' ',' '}},
        {{' ',' ',' ',' '},
         {' ','O','O',' '},
         {' ','O','O',' '},
         {' ',' ',' ',' '}},
        {{' ',' ',' ',' '},
         {' ','O','O',' '},
         {' ','O','O',' '},
         {' ',' ',' ',' '}},
        {{' ',' ',' ',' '},
         {'I','I','I','I'},
         {' ',' ',' ',' '},
         {' ',' ',' ',' '}},
        {{' ',' ',' ',' '},
         {' ','O','O',' '},
         {' ','O','O',' '},
         {' ',' ',' ',' '}},
        {{' ',' ',' ',' '},
         {' ','T',' ',' '},
         {'T','T','T',' '},
         {' ',' ',' ',' '}},
        {{' ',' ',' ',' '},
         {' ','S','S',' '},
         {'S','S',' ',' '},
         {' ',' ',' ',' '}},
        {{' ',' ',' ',' '},
         {'Z','Z',' ',' '},
         {' ','Z','Z',' '},
         {' ',' ',' ',' '}},
        {{' ',' ',' ',' '},
         {'J',' ',' ',' '},
         {'J','J','J',' '},
         {' ',' ',' ',' '}},
        {{' ',' ',' ',' '},
         {' ',' ','L',' '},
         {'L','L','L',' '},
         {' ',' ',' ',' '}}
};

int x = 4, y = 0, b = 1;
int score = 0;
int level = 0;

int getDelay() {
    if (level >= 11) return 80;
    return 300 - (level * 20);
}

// Hàm di chuyển con trỏ để vẽ mượt hơn
void gotoxy(int x, int y) {
#ifdef _WIN32
    COORD c = {(short)x, (short)y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
#else
    printf("\033[%d;%dH", y + 1, x + 1); // Mã ANSI cho macOS/Linux
#endif
}

void boardDelBlock() {
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            if (blocks[b][i][j] != ' ' && y + i < H)
                board[y + i][x + j] = ' ';
}

void block2Board() {
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            if (blocks[b][i][j] != ' ' && y + i < H)
                board[y + i][x + j] = blocks[b][i][j];
}

void initBoard() {
    for (int i = 0; i < H; i++)
        for (int j = 0; j < W; j++)
            if ((i == H - 1) || (j == 0) || (j == W - 1)) board[i][j] = '#';
            else board[i][j] = ' ';
}

void draw() {
    gotoxy(0, 0);
    for (int i = 0; i < H; i++, cout << endl)
        for (int j = 0; j < W; j++)
            cout << board[i][j];
    cout << "Score: " << score << " | Level: " << level << "   ";
}

bool canMove(int dx, int dy) {
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            if (blocks[b][i][j] != ' ') {
                int tx = x + j + dx;
                int ty = y + i + dy;
                if (tx < 1 || tx >= W - 1 || ty >= H - 1) return false;
                if (board[ty][tx] != ' ') return false;
            }
    return true;
}

int removeLine() {
    int linesCleared = 0;
    for (int i = H - 2; i > 0; i--) {
        bool isFull = true;
        for (int j = 1; j < W - 1; j++) {
            if (board[i][j] == ' ') { 
                isFull = false;
                break;
            }
        }
        if (isFull) {
            linesCleared++;
            for (int k = i; k > 1; k--) {
                for (int j = 1; j < W - 1; j++) board[k][j] = board[k-1][j];
            }
            for (int j = 1; j < W - 1; j++) board[1][j] = ' ';
            i++; // Kiểm tra lại hàng hiện tại sau khi dồn
        }
    }
    return linesCleared; 
}

int main() {
    srand((unsigned int)time(0));
    b = rand() % 7;
    initBoard();

    while (1) {
        boardDelBlock();
        if (kbhit()) {
            char c = getch();
            if (c == 'a' && canMove(-1, 0)) x--;
            if (c == 'd' && canMove(1, 0)) x++;
            if (c == 'x' && canMove(0, 1)) y++;
            if (c == 'q') break;
        }

        if (canMove(0, 1)) {
            y++;
        } else {
            block2Board();
            
            // Logic tăng tốc khi xóa hàng
            int lines = removeLine(); 
            if (lines > 0) {
                score += lines * 10;
                level = score / 20; // Cứ mỗi 2 hàng xóa được thì tăng 1 Level
            }
            
            x = 4; y = 0; b = rand() % 7;

            // Kiểm tra Game Over
            if (!canMove(0, 0)) {
                #ifdef _WIN32
                    system("cls");
                #else
                    system("clear");
                #endif
                cout << "GAME OVER!" << endl;
                cout << "Final Score: " << score << " | Level: " << level << endl;
                break;
            }
        }

        block2Board();
        draw();
        Sleep(getDelay()); // Gọi hàm tính độ trễ động
    }
    return 0;
}