#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <stdbool.h>

HANDLE console;
COORD CrPos = {2, 1};
CONSOLE_SCREEN_BUFFER_INFO ScreenBufferInfo;

enum{
    HIGH = 20,
    WIDTH = 53
};

int map[20][53]={
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
        {1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,1,0,0,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,1,0,0,1,1,1,1,1,1,1,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1},
        {1,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,1,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,1,0,1,0,0,0,0,1,0,0,0,0,0,0,1},
        {1,0,0,0,1,0,0,0,0,0,0,1,0,0,0,1,0,0,1,0,0,0,1,0,0,0,0,1,0,0,0,0,0,1,1,1,1,1,0,0,1,0,0,0,0,1,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,1,1,0,0,1,1,1,1,1,0,0,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,1,0,0,1,0,0,0,1},
        {1,1,0,0,0,0,0,0,0,0,0,1,0,0,0,1,0,0,1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1,0,0,1,0,0,0,1,0,0,0,1,1,1,1,1,1,0,0,1},
        {1,0,0,0,1,0,0,0,1,0,0,1,0,0,0,1,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,1,0,0,1,0,0,0,0,0,0,1,0,0,0,0,1,0,0,0,1},
        {1,0,0,0,1,1,0,0,1,0,0,1,0,0,0,1,0,0,1,0,1,1,1,0,0,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,0,0,0,1,0,0,0,1},
        {1,0,0,0,1,0,0,0,1,0,1,1,0,0,0,1,0,0,1,0,0,0,1,0,0,0,0,0,1,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1,0,0,0,1},
        {1,0,1,1,1,0,1,1,1,0,0,1,0,0,0,1,0,0,1,0,0,0,1,1,1,1,1,1,0,0,0,0,0,1,0,0,1,0,0,1,0,0,0,0,0,0,0,0,1,0,0,0,1},
        {1,0,0,0,1,0,0,0,1,0,0,0,0,0,0,1,0,0,1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1,0,0,1,0,0,1,0,0,1,0,0,0,0,0,1,0,0,0,1},
        {1,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,0,1,0,0,0,0,0,1,0,0,1,0,0,1,0,0,1,0,0,0,0,0,1,0,0,0,1},
        {1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,1,0,0,1,0,0,0,1,0,0,0,0,1,0,0,0,0,0,1,0,0,1,0,0,0,0,1,1,0,0,0,0,0,1,0,0,0,1},
        {1,0,0,0,1,0,0,0,0,1,1,1,1,1,1,1,0,0,1,0,0,0,1,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,0,1,0,0,0,0,0,1,0,0,0,1},
        {1,0,1,1,0,1,0,0,1,0,0,1,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,1},
        {1,0,1,0,0,0,0,0,1,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1},
        {1,0,1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,2,1},
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},

};

void init();


void kbEvent();


void updateStatus();

void drawWall();


bool inValidMove(int x, int y);

void win();

void cle(COORD ClPos);

void prin(COORD PrPos);

void Move(COORD *MoPos, int key) ;


int main() {
    init();
    while (1) {
        kbEvent();
        updateStatus();
    }
}

bool inValidMove(int x, int y) {
    return map[y][x / 2] == 0 || map[y][x / 2] == 2;
}


void Move(COORD *MoPos, int key) {
    switch (key) {
        case 72:
            if(!inValidMove(MoPos->X, MoPos->Y - 1))break;
            MoPos->Y--;
            break;
        case 75:
            if(!inValidMove(MoPos->X - 2, MoPos->Y))break;
            MoPos->X-=2;
            break;
        case 77:
            if(!inValidMove(MoPos->X + 2, MoPos->Y))break;
            MoPos->X+=2;
            break;
        case 80:
            if(!inValidMove(MoPos->X, MoPos->Y + 1))break;
            MoPos->Y++;
            break;
        default:
            break;
    }
}

void prin(COORD PrPos){
    SetConsoleCursorPosition(console, PrPos);
    printf("人");
}

void cle(COORD ClPos) {
    SetConsoleCursorPosition(console, ClPos);
    printf("  ");
}

void updateStatus() {
    if(map[CrPos.Y][CrPos.X/2]==2) {
        win();
    }
}

void win() {
    MessageBox(0,"Congratulation!","you win!!!!!",0);
    exit(0);
}

void kbEvent() {
    if (kbhit()) {
        cle(CrPos);
        Move(&CrPos, getch());
        prin(CrPos);
    }
}

void init() {
    console = GetStdHandle(STD_OUTPUT_HANDLE);
    GetConsoleScreenBufferInfo(console, &ScreenBufferInfo);
    drawWall();
    prin(CrPos);

    CONSOLE_CURSOR_INFO info;
    info.dwSize = 100;
    info.bVisible = FALSE;
    SetConsoleCursorInfo(console, &info);


}

void drawWall() {
    for (int i = 0; i < HIGH; ++i) {
        for (int j = 0; j < WIDTH; ++j) {
            if(map[i][j]==1)printf("墙");
            if(map[i][j]==0)printf("  ");
            if(map[i][j]==2)printf("家");
        }
        putchar('\n');
    }
}
