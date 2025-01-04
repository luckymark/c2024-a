#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <conio.h>
#include <windows.h>

using namespace std;

// 定义迷宫元素
const char WALL = '#';
const char PLAYER = 'P';
const char BOX = 'B';
const char TARGET = 'T';
const char EMPTY = ' ';
const char BOX_ON_TARGET = 'X'; // 箱子在目标位置上

// 定义方向
enum Direction { UP, DOWN, LEFT, RIGHT };

// 双缓冲相关变量
HANDLE hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
HANDLE hBuffer = CreateConsoleScreenBuffer(
    GENERIC_READ | GENERIC_WRITE,
    FILE_SHARE_READ | FILE_SHARE_WRITE,
    NULL,
    CONSOLE_TEXTMODE_BUFFER,
    NULL
);
COORD bufferSize = { 80, 25 }; // 缓冲区大小
COORD bufferCoord = { 0, 0 };
SMALL_RECT writeRegion = { 0, 0, 79, 24 }; // 写入区域

// 设置双缓冲
void setDoubleBuffer() {
    SetConsoleActiveScreenBuffer(hBuffer);
}

// 绘制到缓冲区
void drawToBuffer(const vector<vector<char>>& maze) {
    DWORD dwBytesWritten;
    for (int i = 0; i < maze.size(); ++i) {
        for (int j = 0; j < maze[i].size(); ++j) {
            WriteConsoleOutputCharacterA(hBuffer, &maze[i][j], 1, { (SHORT)j, (SHORT)i }, &dwBytesWritten);
        }
    }
}

// 迷宫类
class MazeGame {
private:
    vector<vector<char>> maze; // 迷宫地图
    int playerX, playerY;      // 玩家位置
    vector<pair<int, int>> boxes; // 箱子位置
    vector<pair<int, int>> targets; // 目标位置
    int steps; // 步数

public:
    MazeGame(const vector<vector<char>>& map) {
        maze = map;
        steps = 0;
        findPlayerAndObjects();
    }

    // 查找玩家、箱子和目标位置
    void findPlayerAndObjects() {
        for (int i = 0; i < maze.size(); ++i) {
            for (int j = 0; j < maze[i].size(); ++j) {
                if (maze[i][j] == PLAYER) {
                    playerX = i;
                    playerY = j;
                }
                else if (maze[i][j] == BOX) {
                    boxes.emplace_back(i, j);
                }
                else if (maze[i][j] == TARGET) {
                    targets.emplace_back(i, j);
                }
            }
        }
    }

    // 显示迷宫
    void display() {
        drawToBuffer(maze); // 绘制到缓冲区
        SetConsoleCursorPosition(hBuffer, { 0, (SHORT)maze.size() });
        cout << "Steps: " << steps << endl;
    }

    // 移动玩家
    bool move(Direction dir) {
        int dx = 0, dy = 0;
        switch (dir) {
        case UP: dx = -1; break;
        case DOWN: dx = 1; break;
        case LEFT: dy = -1; break;
        case RIGHT: dy = 1; break;
        }

        int newX = playerX + dx;
        int newY = playerY + dy;

        // 检查边界和墙壁
        if (maze[newX][newY] == WALL) {
            return false;
        }

        // 检查箱子
        auto it = find(boxes.begin(), boxes.end(), make_pair(newX, newY));
        if (it != boxes.end()) {
            int boxX = newX + dx;
            int boxY = newY + dy;
            if (maze[boxX][boxY] == WALL || find(boxes.begin(), boxes.end(), make_pair(boxX, boxY)) != boxes.end()) {
                return false; // 箱子前面是墙或另一个箱子
            }
            // 移动箱子
            *it = make_pair(boxX, boxY);
            maze[newX][newY] = EMPTY;
            maze[boxX][boxY] = (maze[boxX][boxY] == TARGET) ? BOX_ON_TARGET : BOX;
        }

        // 移动玩家
        maze[playerX][playerY] = EMPTY;
        maze[newX][newY] = PLAYER;
        playerX = newX;
        playerY = newY;
        steps++;
        return true;
    }

    // 检查是否胜利
    bool isWin() {
        for (const auto& target : targets) {
            if (find(boxes.begin(), boxes.end(), target) == boxes.end()) {
                return false;
            }
        }
        return true;
    }

    // 获取步数
    int getSteps() const {
        return steps;
    }
};

// 从文件加载迷宫
vector<vector<char>> loadMazeFromFile(const string& filename) {
    ifstream file(filename);
    vector<vector<char>> maze;
    string line;
    while (getline(file, line)) {
        vector<char> row(line.begin(), line.end());
        maze.push_back(row);
    }
    return maze;
}

// 保存分数到文件
void saveScoreToFile(int level, int steps) {
    ofstream file("scores.txt", ios::app);
    if (file.is_open()) {
        file << "Level " << level << ": " << steps << " steps\n";
        file.close();
    }
}

// 主函数
int main() {
    setDoubleBuffer(); // 启用双缓冲

    vector<string> levels = { "levels/level1.txt", "levels/level2.txt", "levels/level3.txt" };
    for (size_t i = 0; i < levels.size(); ++i) {
        auto maze = loadMazeFromFile(levels[i]);
        MazeGame game(maze);

        while (true) {
            game.display();
            if (game.isWin()) {
                cout << "You win!" << endl;
                saveScoreToFile(i + 1, game.getSteps());
                break;
            }

            // 获取键盘输入
            if (_kbhit()) {
                char ch = _getch();
                Direction dir;
                switch (ch) {
                case 'w': dir = UP; break;
                case 's': dir = DOWN; break;
                case 'a': dir = LEFT; break;
                case 'd': dir = RIGHT; break;
                default: continue;
                }
                game.move(dir);
            }
        }
        cout << "Press any key to continue to the next level..." << endl;
        _getch();
    }

    // 恢复默认屏幕缓冲区
    SetConsoleActiveScreenBuffer(hOutput);
    return 0;
}