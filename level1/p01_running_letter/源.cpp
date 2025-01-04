#include <iostream>
#include <windows.h> // 用于 Sleep 和 SetConsoleCursorPosition
#include <string>

// 设置光标位置
void setCursorPosition(int x, int y) {
    COORD coord = { (SHORT)x, (SHORT)y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

int main() {
    std::string text = "Ali"; // 要移动的字母或单词
    int screenWidth = 120;    // 控制台宽度（假设为 120）
    int position = 0;        // 当前文本位置
    int direction = 1;       // 移动方向：1 表示向右，-1 表示向左

    while (true) {
        // 清除上一帧的文本
        setCursorPosition(position, 0);
        for (int i = 0; i < text.length(); ++i) {
            std::cout << " ";
        }

        // 更新位置
        position += direction;

        // 检查边界
        if (position + text.length() >= screenWidth) {
            direction = -1; // 反向
        }
        else if (position <= 0) {
            direction = 1; // 反向
        }

        // 绘制新文本
        setCursorPosition(position, 0);
        std::cout << text;

        Sleep(50); // 减少 Sleep 时间，加快移动速度（50 毫秒）
    }

    return 0;
}