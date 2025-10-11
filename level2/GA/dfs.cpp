#include <iostream>
#include <vector>
#include <conio.h>
#include <Windows.h>
using namespace std;
inline void printmaze(const vector<vector<char>> &maze) {
    system("cls");
    for(int i = 0; i < 11; ++i) {
        for(int j = 0; j < 11; ++j) {
            cout << maze[i][j] << ' ';
        }
        cout << '\n';
    }
}
bool dfs(vector<vector<char>> &maze, vector<int> &personpos, vector<vector<bool>> &visited) {
    printmaze(maze);
    Sleep(100);
    if(personpos[0] == 1 && personpos[1] == 10) {
        cout << "Success!" << endl;
        system("pause");
        return true;
    }
    vector<pair<int, int>> directions = { {-1, 0}, {1, 0}, {0, -1}, {0, 1} };
    vector<char> moves = { 'w', 's', 'a', 'd' };
    for(int i = 0; i < 4; ++i) {
        int newY = personpos[0] + directions[i].first;
        int newX = personpos[1] + directions[i].second;
        if(newY >= 0 && newY < 11 && newX >= 0 && newX < 11 && maze[newY][newX] == ' ' && !visited[newY][newX]) {
            visited[newY][newX] = true;
            maze[personpos[0]][personpos[1]] = ' ';
            maze[newY][newX] = '1';
            vector<int> oldPos = personpos;
            personpos = { newY, newX };
            if(dfs(maze, personpos, visited)) return true;
            maze[newY][newX] = ' ';
            maze[oldPos[0]][oldPos[1]] = '1';
            personpos = oldPos;
            visited[newY][newX] = false;
        }
    }
    return false;
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    vector<vector<char>> maze = {
        {'0','0','0','0','0','0','0','0','0','0','0'},
        {'0','0',' ','0','0',' ','0','0',' ',' ',' '},
        {'0',' ',' ',' ',' ',' ',' ','0',' ','0','0'},
        {'0',' ','0',' ',' ','0',' ','0',' ',' ','0'},
        {'0',' ','0',' ','0','0',' ','0','0',' ','0'},
        {'0',' ','0',' ','0','0',' ','0','0',' ','0'},
        {'0',' ','0','0',' ',' ',' ','0','0',' ','0'},
        {'0',' ','0','0',' ','0','0','0','0',' ','0'},
        {'1',' ','0','0',' ','0','0','0','0',' ','0'},
        {'0',' ',' ','0',' ',' ',' ',' ',' ',' ','0'},
        {'0','0','0','0','0','0','0','0','0','0','0'}
    };
    vector<int> personpos = { 8, 0 };
    vector<vector<bool>> visited(11, vector<bool>(11, false));
    dfs(maze, personpos, visited);
    return 0;
}