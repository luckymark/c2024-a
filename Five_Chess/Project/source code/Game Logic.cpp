#include "Game Logic.h"
#include "Graphics Logic.h"
#include <string>
using namespace std;
extern HWND game;
RELEASE_INLINE void Five_Chess::putchess(int x, int y) {
	// 为空，落子
	if(chessboard[x][y] == ' ') {
		chessboard[x][y]		= white_player_playing ? '1' : '2';
		white_player_playing	= !white_player_playing;
		prev_lastx				= lastx;
		prev_lasty				= lasty;
		lastx					= x;
		lasty					= y;
	}
	// 被占据，抛异常
	else {
		throw Occupied();
	}
}

RELEASE_INLINE void Five_Chess::rmchess(int x, int y) noexcept {
	// 不检测了
	chessboard[x][y]		= ' ';
	white_player_playing	= !white_player_playing;
	lastx					= prev_lastx;
	lasty					= prev_lasty;
}

RELEASE_INLINE bool Five_Chess::has_ended(char &ch) const noexcept {
	// 五子连珠，游戏结束
	for(int i = 0; i < 15; ++i) {
		for(int j = 0; j < 11; ++j) {
			if(	chessboard[i][j]		== chessboard[i][j + 1] &&
				chessboard[i][j + 1]	== chessboard[i][j + 2] &&
				chessboard[i][j + 2]	== chessboard[i][j + 3] &&
				chessboard[i][j + 3]	== chessboard[i][j + 4] &&
				chessboard[i][j] != ' ') {
					ch = chessboard[i][j];
					return true;
			}
		}
	}
	for(int i = 0; i < 15; ++i) {
		for(int j = 0; j < 11; ++j) {
			if(	chessboard[j][i]		== chessboard[j + 1][i] &&
				chessboard[j + 1][i]	== chessboard[j + 2][i] &&
				chessboard[j + 2][i]	== chessboard[j + 3][i] &&
				chessboard[j + 3][i]	== chessboard[j + 4][i] &&
				chessboard[j][i] != ' ') {
					ch = chessboard[j][i];
					return true;
			}
		}
	}
	for(int i = 0; i < 11; ++i) {
		for(int j = 0; j < 11; ++j) {
			if(	chessboard[i][j]			== chessboard[i + 1][j + 1] &&
				chessboard[i + 1][j + 1]	== chessboard[i + 2][j + 2] &&
				chessboard[i + 2][j + 2]	== chessboard[i + 3][j + 3] &&
				chessboard[i + 3][j + 3]	== chessboard[i + 4][j + 4] &&
				chessboard[i][j] != ' ') {
					ch = chessboard[i][j];
					return true;
			}
		}
	}
	for(int i = 4; i < 15; ++i) {
		for(int j = 0; j < 11; ++j) {
			if(	chessboard[i][j]			== chessboard[i - 1][j + 1] &&
				chessboard[i - 1][j + 1]	== chessboard[i - 2][j + 2] &&
				chessboard[i - 2][j + 2]	== chessboard[i - 3][j + 3] &&
				chessboard[i - 3][j + 3]	== chessboard[i - 4][j + 4] &&
				chessboard[i][j] != ' ') {
					ch = chessboard[i][j];
					return true;
			}
		}
	}
	// 棋盘占满，游戏结束
	if(generate_possible_moves().empty()) {
		ch = '3';
		return true;
	}
	// 未结束
	ch = ' ';
	return false;
}

RELEASE_INLINE vector<pair<int, int>> Five_Chess::generate_possible_moves() const noexcept {
	// 返回所有空的坐标
	vector<pair<int, int>> moves;
	for(int i = 0; i < chessboard.size(); ++i) {
		for(int j = 0; j < chessboard[i].size(); ++j) {
			if(chessboard[i][j] == ' ') {
				moves.emplace_back(i, j);
			}
		}
	}
	return moves;
}

RELEASE_INLINE void playgame(Five_Chess &fc,
	Player_Base *player1, Player_Base *player2,
	bool dosleep) noexcept {
	// 进入游戏时打印棋盘
	printboard(fc);
	// 获取胜利者的代理对象
	char ch;
	// 在游戏结束前循环二人操作
	while(!fc.has_ended(ch)) {
		player1->judge(fc);
		player1->put(fc);
		printboard(fc);
		FlushBatchDraw();
		// 如果第一人落子后游戏已经结束，则直接退出循环
		if(fc.has_ended(ch)) break;
		if(dosleep) Sleep(500);
		player2->judge(fc);
		player2->put(fc);
		printboard(fc);
		FlushBatchDraw();
		if(dosleep && !fc.has_ended(ch)) Sleep(500);
	}
	// 结算动画
	vector<tstring> texts = {
		_T("白棋获胜！"),	_T("White wins!"),
		_T("黑棋获胜！"),	_T("Black wins!"),
		_T("平局！"),		_T("Draw!")
	};
	printhint(340, 220, 
		texts[(static_cast<size_t>(ch) - '1') * 2 + static_cast<size_t>(language)].c_str());
	FlushBatchDraw();
	// 等待1s后返回主菜单
	Sleep(1000);
	setlinecolor(BLACK);
}

RELEASE_INLINE void Human::put(Five_Chess &fc) noexcept {
	while(true) {
		// 获取鼠标信息
		MOUSEMSG msg = GetMouseMsg();
		// 没有点击左键的时候不断获取鼠标信息
		while(msg.uMsg != WM_LBUTTONDOWN) {
			msg = GetMouseMsg();
			printboard(fc, msg);
		}
		// 尝试在按下左键的地方落子
		try {
			// 把鼠标消息转换为棋盘坐标
			int x = (msg.x - 25) / 40;
			int y = (msg.y - 25) / 40;
			// 如果在棋盘内则落子，可能抛出异常Occupied，在catch块中处理
			if(msg.uMsg == WM_LBUTTONDOWN && x < 15 && y < 15 && x >= 0 && y >= 0) {
				fc.putchess(x, y);
				// 成功落子，退出循环
				break;
			}
		}
		// 落子失败，该位置被占用，继续循环
		catch(Occupied &) {}
	}
}