//
// Created by Emerson on 2024/9/27.
//
#include <iostream>
#include <fstream>
using namespace std;
//地图
// int maze[5][5] = {
//     {0,1,0,0,0},
//     {0,1,0,1,0},
//     {0,1,0,1,0},
//     {0,1,0,1,0},
//     {0,0,0,1,0}
// };

const int ROWS = 5;
const int COLS = 5;
int maze[ROWS][COLS];

//玩家
int x, y;
//目的地
int targetX,targetY;

bool loadMap(const string& filename) {
    ifstream file(filename);
    if (!file) {
        cout << "没有了" << endl;
        return false;
    }
    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLS; ++j) {
            file >> maze[i][j];
        }
    }
    file.close();

    //每次初始化时，都将玩家置于起点
    x = 0;
    y = 0;
    //目标地
    targetX = ROWS - 1;
    targetY = COLS - 1;


    return true;
}
//地图绘制
void printMaze() {
    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLS; ++j) {
            if (i == x && j == y) {
                cout << "P ";
            }
            else if(i == targetX && j == targetY) {
                cout << "T";
            }
            else if (maze[i][j] == 0) {
                cout << ". ";
            }
            else if (maze[i][j] == 1) {
                cout << "# ";
            }
        }
        cout << endl;
    }
}

//行动是否有效
bool isValid(int newX, int newY) {
    if (newX >= 0 && newX < ROWS && newY >= 0 && newY < COLS) {
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
    int level = 1;

    while (true) {
        //动态构建文件名
        string filename = "map" + to_string(level) + ".txt";
        if (!loadMap(filename)) {
            cout << "真的一关也没有了" << endl;
            break;
        }

        cout << "加载关卡"  << level << "成功" << endl;

        char command;
        while (true) {
            printMaze(); // 显示地图
            cout << "输入指令 (W/A/S/D 控制上下左右): ";
            cin >> command;
            Move(command); // 移动玩家

            // 判断是否到达目的地
            if (x == targetX && y == targetY) {
                cout << "关卡 " << level << " 完成！" << endl;
                level++; // 进入下一关
                break;
            }
        }
    }
    return 0;
}