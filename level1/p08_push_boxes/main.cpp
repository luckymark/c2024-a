#define _CRT_SECURE_NO_WARNINGS
#include <graphics.h>
#include <conio.h>
#include <windows.h>
#include <iostream>
#include <cstdio>
using namespace std;

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 650

#define RATIO 50

#define SECTION 5
#define LINE 9
#define COLUMN 12
#define MAPS_MAX 5

#define START_X 100
#define START_Y 100


//控制键 上、下、左、右 控制方向，'q' 退出
#define KEY_UP 'w' //char 'a'
#define KEY_LEFT 'a'
#define KEY_RIGHT 'd'
#define KEY_DOWN 's'
#define KEY_QUIT 'q'

#define isValid(pos) (pos.x >= 0 && pos.x < LINE && pos.y >= 0 && pos.y < COLUMN)

const int MAX = 20;

typedef enum _DIRECTION DIRECTION;
typedef struct _POS POS;

IMAGE bg_img;

enum _PROPS
{
    WALL,      //墙
    FLOOR,     //地板
    BOX_DES,   //箱子目的地
    MAN,       //小人
    BOX,       //箱子
    HIT,       //箱子命中目标
    ALL        //用于记录数组的大小
};

//游戏控制方向
enum _DIRECTION
{
    UP,
    DOWN,
    LEFT,
    RIGHT
};

struct _POS
{
    int x;
    int y;
};



int map[LINE][COLUMN];


IMAGE images[ALL];

POS man;

void changeMap(POS* pos, _PROPS prop)
{
    map[pos->x][pos->y] = prop;
    putimage(START_X + pos->y * RATIO, START_Y + pos->x * RATIO, &images[prop]);
}

/**********************************************
*实现游戏四个方向（上、下、左、右）的控制
* 输入：
* direct - 人前进方向
* 输出： 无
**********************************************/


void gameControl(DIRECTION direct)
{
    POS next_pos = man;
    POS next_next_pos = man;
    switch (direct)
    {
        case UP:
            next_pos.x--;
            next_next_pos.x -= 2;
            break;
        case DOWN:
            next_pos.x++;
            next_next_pos.x += 2;
            break;
        case LEFT:
            next_pos.y--;
            next_next_pos.y -= 2;
            break;
        case RIGHT:
            next_pos.y++;
            next_next_pos.y += 2;
            break;
    }
    if (isValid(next_pos) && map[next_pos.x][next_pos.y] == FLOOR)
    {
        changeMap(&next_pos, MAN);
        changeMap(&man, FLOOR);
        man = next_pos;
    }
    else if (isValid(next_next_pos) && map[next_pos.x][next_pos.y] == BOX)
    {
        if (map[next_next_pos.x][next_next_pos.y] == FLOOR)
        {
            changeMap(&next_next_pos, BOX);
            changeMap(&next_pos, MAN);
            changeMap(&man, FLOOR);
            man = next_pos;
        }
        else if (map[next_next_pos.x][next_next_pos.y] == BOX_DES)
        {
            changeMap(&next_next_pos, HIT);
            changeMap(&next_pos, MAN);
            changeMap(&man, FLOOR);
            man = next_pos;
        }
    }
}

/**********************************************
*判断游戏是否结束，如果不存在任何一个箱子目的地，就代表游戏结束
*输入： 无
*返回值：
* true - 游戏结束 false - 游戏继续
**********************************************/
bool isGameOver() {
    for (int i = 0; i < LINE; i++) {
        for (int j = 0; j < COLUMN; j++) {
            if (map[i][j] == BOX_DES) return false;
        }
    }
    return true;
}

void UpdataS(int mark)
{
    FILE* file;
    fopen_s(&file, "Map.txt", "r");

    int score = 0;

    int line = 0;
    int col = 0;

    fscanf_s(file, "%d %d %d", &line, &col, &score);
    fgetc(file);
    char c;
    for (int i = 0; i < line; i++)
    {
        for (int j = 0; j < col; j++)
        {
            c = fgetc(file);
            map[i][j] = c - '0';
        }
        fgetc(file);
    }

    score = mark;
    fclose(file);

    errno_t err;

    err=fopen_s(&file, "Map.txt", "w");
    if (err != 0)
    {
        cout << "ERROR";
        return;
    }


    //断点


    fprintf_s(file, "%d %d %d", line, col, score);
    for (int i = 0; i < line; i++)
    {
        for (int j = 0; j < col; j++)
        {
            fputc((char)(map[i][j] + '0'), file);
        }
        fputc('\n', file);
    }

    fclose(file);
}

void gameOverScreen(IMAGE* bg)
{
    putimage(0, 0, bg);
    settextcolor(WHITE);
    RECT rec = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };
    settextstyle(20, 0, "宋体");
    drawtext("恭喜您~ \n 您终于成为了一个合格的搬箱子老司机！", &rec, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
}


void game()
{
    int mark = 100;
    putimage(0, 0, &bg_img);
    FILE* file;
    fopen_s(&file, "Map.txt", "r");

    int score = 0;

    int line = 0;
    int col = 0;

    fscanf_s(file, "%d %d %d", &line, &col, &score);
    getc(file);
    int i = 0;
    char c;
    for (int i = 0; i < line; i++)
    {
        for (int j = 0; j < COLUMN; j++)
        {
            c = getc(file);
            map[i][j] = c-'0';
        }
        getc(file);
    }



    cout << "当前得分：" << score;

    for (int i = 0; i < LINE; i++)
    {
        for (int j = 0; j < COLUMN; j++)
        {
            if (map[i][j] == MAN)
            {
                man.x = i;
                man.y = j;
            }
            putimage(START_X + j * RATIO, START_Y + i * RATIO, &images[map[i][j]]);
        }
    }

    bool quit = false;

    do
    {
        if (_kbhit())
        {
            char ch = _getch();

            if (ch == KEY_UP)
            {
                gameControl(UP);
                mark--;
            }
            else if (ch == KEY_DOWN)
            {
                gameControl(DOWN);
                mark--;
            }
            else if (ch == KEY_LEFT)
            {
                gameControl(LEFT);
                mark--;
            }
            else if (ch == KEY_RIGHT)
            {
                gameControl(RIGHT);
                mark--;
            }
            else if (ch == KEY_QUIT)
            {
                quit = true;
            }
            if (/*isGameOver())*/1)
            {
                gameOverScreen(&bg_img);
                if (mark > score)
                {
                    UpdataS(mark);
                }
            }
        }
        Sleep(100); //100ms = 0.1s
    } while (quit == false);

}


int main()
{
    //搭台唱戏
    initgraph(SCREEN_WIDTH, SCREEN_HEIGHT);

    //设置背景
    loadimage(&bg_img, "blackground.bmp", SCREEN_WIDTH, SCREEN_HEIGHT, true);

    //墙: 0，地板 : 1，箱子目的地 : 2, 小人 : 3, 箱子 : 4, 箱子命中目标 : 5
    loadimage(&images[WALL], "wall_right.bmp", RATIO, RATIO, true);
    loadimage(&images[FLOOR], "floor.bmp", RATIO, RATIO, true);
    loadimage(&images[BOX_DES], "des.bmp", RATIO, RATIO, true);
    loadimage(&images[MAN], "man.bmp", RATIO, RATIO, true);
    loadimage(&images[BOX], "box.bmp", RATIO, RATIO, true);
    loadimage(&images[HIT], "box.bmp", RATIO, RATIO, true);

    game();

    system("pause");
    return 0;
}
