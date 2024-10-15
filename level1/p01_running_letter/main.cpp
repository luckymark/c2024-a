//代码应该没问题，在VS上跑符合要求，但在CLION上不知道为什么是竖着依次显示，没有清屏

#include <iostream>
#include <cstdlib>

#include <string>
#include <windows.h>

using namespace std;
int main() {
    const string letter = "A"; // 你可以将这个字母更换为任何单词
    const int width = 50; // 控制台的宽度
    //int position = -static_cast<int>(letter.length()); // 字母的起始位置
    int position=0;
    bool right = true; // 初始方向向右

    while (true) {
        system("cls"); // 清除屏幕，在 Windows 上使用 system("cls");
        cout << string(position, ' '); // 打印前面的空格
        cout << letter; // 打印字母
        cout << flush; // 确保立即输出

        if (right) {
            position++; // 向右移动
            if (position + letter.length() == width) {
                right = false; // 遇到边界，改变方向
            }
        } else {
            position--; // 向左移动
            if (position == 0) {
                right = true; // 遇到边界，改变方向
            }
        }

        Sleep(100);
    }

    return 0;
}