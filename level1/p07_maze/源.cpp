#include <iostream>
#include <vector>
#include <stack>
#include <chrono> // 用于计时
#include <conio.h> // 用于键盘输入
#include <windows.h> // 用于控制台操作

using namespace std;

// 迷宫尺寸
const int ROWS = 15;
const int COLS = 30;

// 迷宫地图
char maze[ROWS][COLS];

// 玩家初始位置
int playerRow = 1;
int playerCol = 1;

// 出口位置
int exitRow = ROWS - 2;
int exitCol = COLS - 2;

// 设置光标位置
void setCursorPosition(int x, int y) {
    COORD coord = { (SHORT)x, (SHORT)y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

// 初始化迷宫（全部为墙）
void initializeMaze() {
    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLS; ++j) {
            maze[i][j] = '#';
        }
    }
}

// 随机生成迷宫（使用深度优先搜索算法）
void generateMaze(int startRow, int startCol) {
    // 方向数组：上、右、下、左
    int dirRow[] = { -2, 0, 2, 0 };
    int dirCol[] = { 0, 2, 0, -2 };

    // 随机数种子
    srand(time(nullptr));

    // 使用栈实现 DFS
    stack<pair<int, int>> stack;
    stack.push({ startRow, startCol });
    maze[startRow][startCol] = ' ';

    while (!stack.empty()) {
        int row = stack.top().first;
        int col = stack.top().second;
        stack.pop();

        // 随机打乱方向
        int dirs[] = { 0, 1, 2, 3 };
        for (int i = 0; i < 4; ++i) {
            int j = rand() % 4;
            swap(dirs[i], dirs[j]);
        }

        // 尝试四个方向
        for (int i = 0; i < 4; ++i) {
            int newRow = row + dirRow[dirs[i]];
            int newCol = col + dirCol[dirs[i]];

            if (newRow > 0 && newRow < ROWS - 1 && newCol > 0 && newCol < COLS - 1 && maze[newRow][newCol] == '#') {
                maze[newRow][newCol] = ' ';
                maze[row + dirRow[dirs[i]] / 2][col + dirCol[dirs[i]] / 2] = ' '; // 打通路径
                stack.push({ newRow, newCol });
            }
        }
    }

    // 设置出口
    maze[exitRow][exitCol] = 'E';
}

// 打印迷宫
void printMaze() {
    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLS; ++j) {
            cout << maze[i][j];
        }
        cout << endl;
    }
}

// 移动玩家
void movePlayer(int newRow, int newCol) {
    if (maze[newRow][newCol] != '#') { // 检查是否撞墙
        maze[playerRow][playerCol] = ' '; // 清空玩家当前位置
        playerRow = newRow;
        playerCol = newCol;
        maze[playerRow][playerCol] = 'P'; // 更新玩家新位置
    }
}

// 主函数
int main() {
    char input;
    bool gameOver = false;

    // 初始化迷宫
    initializeMaze();
    generateMaze(1, 1); // 从 (1, 1) 开始生成迷宫

    // 设置玩家初始位置
    maze[playerRow][playerCol] = 'P';

    // 隐藏光标
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
    cursorInfo.bVisible = false;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);

    // 记录开始时间
    auto startTime = chrono::high_resolution_clock::now();

    while (!gameOver) {
        setCursorPosition(0, 0); // 将光标移动到左上角
        printMaze();

        // 检查是否到达出口
        if (playerRow == exitRow && playerCol == exitCol) {
            auto endTime = chrono::high_resolution_clock::now();
            auto duration = chrono::duration_cast<chrono::seconds>(endTime - startTime);
            cout << "恭喜你宝宝，逃出了该作业迷宫！用时: " << duration.count() << " 秒" << endl;
            gameOver = true;
            break;
        }

        // 获取键盘输入
        input = _getch();

        // 根据输入移动玩家
        switch (input) {
        case 'w': // 上
            movePlayer(playerRow - 1, playerCol);
            break;
        case 's': // 下
            movePlayer(playerRow + 1, playerCol);
            break;
        case 'a': // 左
            movePlayer(playerRow, playerCol - 1);
            break;
        case 'd': // 右
            movePlayer(playerRow, playerCol + 1);
            break;
        case 'q': // 退出游戏
            gameOver = true;
            break;
        default:
            break;
        }
    }

    // 恢复光标显示
    cursorInfo.bVisible = true;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);

    return 0;
}
