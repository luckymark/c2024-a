//
// Created by Emerson on 2024/9/27.
//
#include <iostream>
using namespace std;
//��ͼ
int maze[5][5] = {
    {0,1,0,0,0},
    {0,1,0,1,0},
    {0,1,0,1,0},
    {0,1,0,1,0},
    {0,0,0,1,0}
};

//���
int x = 0, y = 0;
//Ŀ�ĵ�
int targetX = 4,targetY = 4;
//��ͼ����
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

//�ж��Ƿ���Ч
bool isValid(int newX, int newY) {
    if (newX >= 0 && newX < 5 && newY >= 0 && newY < 5) {
        if (maze[newX][newY] == 0) {
            return true;
        }
    }
    return false;
}
//�ж�
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
            cout << "ָ����Ч " << endl;
    }
}

int main() {
    char command;
    while (1) {
        printMaze();
        cout << "����ָ��" << endl;
        cin >> command;
        Move(command);
        if (x == targetX && y == targetY) {
            cout << "WIN" << endl;
            break;
        }
    }
    return 0;
}