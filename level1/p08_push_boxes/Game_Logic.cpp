#include "Game_Logic.h"
#include "Graphic_Logic.h"
#include<graphics.h>
#include <fstream>
#include<conio.h>
using namespace std;
Game_Logic::Game_Logic() {
	fstream file;
	file.open("maps.txt", ios::in);
	_STL_ASSERT(file.is_open(), "File opening failed");
	boards = vector<vector<vector<int>>>(10, vector<vector<int>>(10, vector<int>(14)));
	player_poses = vector<vector<int>>(10, vector<int>(2));
	for(int i = 0; i < 10; ++i) {
		for(int j = 0; j < 10; ++j) {
			for(int k = 0; k < 14; ++k) {
				file >> boards[i][j][k];
				if((boards[i][j][k] & 4) == 4) {
					player_poses[i][0] = j;
					player_poses[i][1] = k;
				}
			}
		}
	}
	level_playing = 0;
}
vector<vector<int>> Game_Logic::move(char ch) {
    auto &board = boards[level_playing];
    if(ch == (char) -1) return board;
    int x = player_poses[level_playing][1], y = player_poses[level_playing][0];
    switch(ch) {
        case 'W':
        case 'w': {
            if(y == 0) return board;
            else if((board[y - 1][x] == 0) || board[y - 1][x] == 2) { // 上面是空地或目标
                board[y][x] -= 4;
                board[y - 1][x] += 4;
                player_poses[level_playing][0] = y - 1;
            }
            else if(board[y - 1][x] == 8) return board; //撞墙了
            else if(board[y - 1][x] == 1 || board[y - 1][x] == 3) { // 推到箱子了
                if(y - 1 == 0) { // 往墙上推，推回来
                    board[y][x] -= 3;
                    board[y - 1][x] += 3;
                    player_poses[level_playing][0] = y - 1;
                }
                else if((board[y - 2][x] == 8) || board[y - 2][x] == 1) {
                    board[y][x] -= 3;
                    board[y - 1][x] += 3;
                    player_poses[level_playing][0] = y - 1;
                }
                else if(board[y - 2][x] == 2 || board[y - 2][x] == 0) { // 空地或目的地
                    board[y][x] -= 4;
                    board[y - 1][x] += 3;
                    board[y - 2][x] += 1;
                    player_poses[level_playing][0] = y - 1;
                }
            }
        } break;
        case 'S':
        case 's': {
            if(y == 9) return board;
            else if((board[y + 1][x] == 0) || board[y + 1][x] == 2) {
                board[y][x] -= 4;
                board[y + 1][x] += 4;
                player_poses[level_playing][0] = y + 1;
            }
            else if(board[y + 1][x] == 8) return board;
            else if(board[y + 1][x] == 1 || board[y + 1][x] == 3) {
                if(y + 1 == 9) {
                    board[y][x] -= 3;
                    board[y + 1][x] += 3;
                    player_poses[level_playing][0] = y + 1;
                }
                else if((board[y + 2][x] == 8) || board[y + 2][x] == 1) {
                    board[y][x] -= 3;
                    board[y + 1][x] += 3;
                    player_poses[level_playing][0] = y + 1;
                }
                else if((board[y + 2][x] == 2) || board[y + 2][x] == 0) {
                    board[y][x] -= 4;
                    board[y + 1][x] += 3;
                    board[y + 2][x] += 1;
                    player_poses[level_playing][0] = y + 1;
                }
            }
        } break;
        case 'A':
        case 'a': {
            if(x == 0) return board;
            else if((board[y][x - 1] == 0) || board[y][x - 1] == 2) {
                board[y][x] -= 4;
                board[y][x - 1] += 4;
                player_poses[level_playing][1] = x - 1;
            }
            else if(board[y][x - 1] == 8) return board;
            else if(board[y][x - 1] == 1 || board[y][x - 1] == 3) {
                if(x - 1 == 0) {
                    board[y][x] -= 3;
                    board[y][x - 1] += 3;
                    player_poses[level_playing][1] = x - 1;
                }
                else if((board[y][x - 2] == 8) || board[y][x - 2] == 1) {
                    board[y][x] -= 3;
                    board[y][x - 1] += 3;
                    player_poses[level_playing][1] = x - 1;
                }
                else if((board[y][x - 2] == 2) || board[y][x - 2] == 0) {
                    board[y][x] -= 4;
                    board[y][x - 1] += 3;
                    board[y][x - 2] += 1;
                    player_poses[level_playing][1] = x - 1;
                }
            }
        } break;
        case 'D':
        case 'd': {
            if(x == 13) return board;
            else if((board[y][x + 1] == 0) || board[y][x + 1] == 2) {
                board[y][x] -= 4;
                board[y][x + 1] += 4;
                player_poses[level_playing][1] = x + 1;
            }
            else if(board[y][x + 1] == 8) return board;
            else if(board[y][x + 1] == 1 || board[y][x + 1] == 3) {
                if(x + 1 == 13) {
                    board[y][x] -= 3;
                    board[y][x + 1] += 3;
                    player_poses[level_playing][1] = x + 1;
                }
                else if((board[y][x + 2] == 8) || board[y][x + 2] == 1) {
                    board[y][x] -= 3;
                    board[y][x + 1] += 3;
                    player_poses[level_playing][1] = x + 1;
                }
                else if((board[y][x + 2] == 2) || board[y][x + 2] == 0) {
                    board[y][x] -= 4;
                    board[y][x + 1] += 3;
                    board[y][x + 2] += 1;
                    player_poses[level_playing][1] = x + 1;
                }
            }
        } break;
    }
    return board;
}
bool has_ended(vector<vector<int>> &board) {
    for(int i = 0; i < 10; ++i) {
        for(int j = 0; j < 14; ++j) {
            if(board[i][j] == 1) return false;
        }
    }
    return true;
}
void Game::play() {
    Graphic_Logic gralog;
    Game_Logic gamlog;
    BeginBatchDraw();
    while(true) {
        gralog.menu();
        int lv = gralog.level() - 1;
        if(lv == 10) continue;
        gamlog.level_playing = lv;
        gralog.init_level(gamlog.move('\0'));
        while(true) {
            ExMessage msg = getmessage(EX_KEY); // 捕获键盘事件
            if(msg.message == WM_KEYDOWN) {
                char ch = msg.vkcode; // 获取按键代码
                auto _board = gamlog.move(ch);
                gralog.init_level(_board);
                if(has_ended(_board)) {
					int n = gamlog.level_playing;
                    gamlog = Game_Logic();
					gamlog.level_playing = n;
                    if(gralog.pass()) {
                        gamlog.level_playing++;
                        gralog.level_playing++;
                        gralog.init_level(gamlog.move('\0'));
                    }
                    else {
                        gralog.level_playing = 0;
						gamlog.level_playing = 0;
                        break;
                    }
                }
            }
            Sleep(10);
        }
    }
    EndBatchDraw();
}