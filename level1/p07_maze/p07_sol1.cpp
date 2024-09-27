//
// Created by Emerson on 2024/9/27.
//
#include <iostream>
using namespace std;
//地图
int maze[5][5] = {
    {0,1,0,0,0},
    {0,1,0,1,0},
    {0,1,0,1,0},
    {0,1,0,1,0},
    {0,0,0,1,0}
};

//玩家
int x = 0, y = 0;
//目的地
int targetX = 4,targetY = 4;
//地图绘制
void printMaze() {
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 5; ++j) {
            if (i == x && j == y) {
                cout << "P ";
            }
            else if(i == targetX && j == targetY) {
                cout << "T";
            }
            else if (maze[i][j] == 0) {
                cout << ". ";
            }
            else {
                cout << "# ";
            }
        }
        cout << endl;
    }
}

//行动是否有效
bool isValid(int newX, int newY) {
    if (newX >= 0 && newX < 5 && newY >= 0 && newY < 5) {
        if (maze[newX][newY] == 0) {
            return true;
        }
    }
    return false;
}
//行动
void Move(char& command) {
    switch (command) {
        case 'W':
            if (isValid(x - 1, y)) {
                x--;
            }
        break;
        case'S':
            if (isValid(x + 1, y)) {
                x++;
            }
        break;
        case'A':
            if (isValid(x, y - 1)) {
                y--;
            }
        break;
        case'D':
            if (isValid(x, y + 1)) {
                y++;
            }
        break;
        default:
            cout << "指令无效 " << endl;
    }
}

int main() {
    char command;
    while (1) {
        printMaze();
        cout << "输入指令" << endl;
        cin >> command;
        Move(command);
        if (x == targetX && y == targetY) {
            cout << "WIN" << endl;
            break;
        }
    }
    return 0;
}