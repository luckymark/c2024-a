//
// Created by Emerson on 2024/9/23.
//
#include <iostream>
#include <string>

using namespace std;

const int screenWidth = 30;

void clearScreen() {
    system("cls");
}

string moveAndPrint(string &word, int& posX, bool& movingRight) {
    clearScreen();
    cout << string(posX, ' ') << word;

    if (movingRight) {
        if (posX + word.length() - 1 >= screenWidth - 1) {
            movingRight = false;
        }
    } else {
        if (posX <= 0) {
            movingRight = true;
        }
    }

    if (movingRight) {
        posX++;
    } else {
        posX--;
    }
    return word;
}

int main() {
    string word;
    cin >> word;// 定义要移动的字符串
    int posX = 0; // 定义字符串的初始位置
    bool movingRight = true; // 定义初始移动方向

    while (true) {
        moveAndPrint(word, posX, movingRight);
    }

    return 0;
}