#include <iostream>
#include <conio.h>
#include <windows.h>

#define LINE 9
#define COLUMN 9
#define KEY_UP 'w'
#define KEY_LEFT 'a'
#define KEY_RIGHT 'd'
#define KEY_DOWN 's'

using namespace std;

enum DIRECTION
{
    UP,
    DOWN,
    LEFT,
    RIGHT
};

int mp[LINE][COLUMN] =
        {
                {0,0,1,1,1,1,1,1},
                {1,0,0,0,0,0,0,1},
                {1,0,0,1,0,1,1,1},
                {1,1,0,0,0,0,1,1},
                {1,0,0,1,1,0,1,1},
                {1,0,1,1,1,0,1,1},
                {1,0,0,1,1,0,0,0},
                {1,1,1,1,1,1,1,1},
        };

struct POS
{
    int x;
    int y;
};

POS start = { 0,0 };
POS man = start;
POS target = { 6,7 };


void Pmaze()
{
    for (int i = 0; i < LINE-1; i++)
    {
        for (int j = 0; j < COLUMN-1; j++)
        {
            if (i == start.x && j == start.y)
            {
                cout << "S";
            }
            else if (i == target.x && j == target.y)
            {
                cout << "T";
            }
            else if (i == man.x && j == man.y)
            {
                cout << "U";
            }
            else if (mp[i][j] == 1)
            {
                cout << "#";
            }
            else if(mp[i][j]==0)
            {
                cout << ".";
            }
        }
        cout << endl;
    }
}

void Move(enum DIRECTION direct)
{
    POS tmp = man;
    switch (direct)
    {
        case UP:
            tmp.x--;
            break;
        case DOWN:
            tmp.x++;
        case LEFT:
            tmp.y--;
        case RIGHT:
            tmp.y++;
    }

    if (mp[tmp.x][tmp.y] == 0&&tmp.x>=0&&tmp.x<LINE&&tmp.y>=0&&tmp.y<COLUMN)
    {
        man = tmp;
        system("cls");
        Pmaze();
    }
}


void game()
{
    while(1)
    {
        if (_kbhit())
        {
            char ch = _getch();
            if (ch == KEY_UP)
            {
                Move(UP);
            }
            else if (ch == KEY_DOWN)
            {
                Move(DOWN);
            }
            else if (ch == KEY_LEFT)
            {
                Move(LEFT);
            }
            else if (ch == KEY_RIGHT)
            {
                Move(RIGHT);
            }

            if (man.x==target.x&&man.y==target.y)
            {
                Sleep(100);
                break;
            }
        }
        Sleep(100);
    }

}


int main()
{
    cout << "press any key to start..." << endl;
    char s = _getch();
    system("cls");
    Pmaze();
    game();
    system("cls");
    cout << "You Win!!!";
    return 0;
}
