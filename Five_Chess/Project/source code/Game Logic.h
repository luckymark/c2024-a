#pragma once
#include "Common.h"
#include "Player_Base.h"
#include <algorithm>
#include <utility>
#include <vector>
#pragma warning(push)
#pragma warning(disable: 5030) // 无法识别属性：msvc::always_inline
// 五子棋棋盘类
class Five_Chess {
public:
	Five_Chess() :
		chessboard(15, std::vector<char>(15, ' ')),
		white_player_playing(false),
		lastx(-1), lasty(-1),
		prev_lastx(-1), prev_lasty(-1) {}
	Five_Chess(const Five_Chess &other) :
		chessboard(other.chessboard),
		white_player_playing(other.white_player_playing),
		lastx(other.lastx), lasty(other.lasty),
		prev_lastx(other.prev_lastx), prev_lasty(other.prev_lasty) {}
	Five_Chess &operator=(const Five_Chess &other) {
		if(this != std::addressof(other)) {
			chessboard = other.chessboard;
			white_player_playing = other.white_player_playing;
			lastx = other.lastx;
			lasty = other.lasty;
			prev_lastx = other.prev_lastx;
			prev_lasty = other.prev_lasty;
		}
		return *this;
	}
	// 落子
	RELEASE_INLINE void								putchess	(int x, int y);
	// 移除棋子
	RELEASE_INLINE void								rmchess		(int x, int y) noexcept;
	// 判定游戏是否结束，ch传入以获取胜利玩家
	RELEASE_INLINE bool								has_ended	(char &ch) const noexcept;
	// 生成所有可能的落子处
	RELEASE_INLINE std::vector<std::pair<int, int>> generate_possible_moves() const noexcept;
	// 返回正在玩的玩家，true为白子
	RELEASE_INLINE bool								player_playing() const noexcept {
		return white_player_playing;
	}
	// 棋盘
	std::vector<std::vector<char>>	chessboard;
	// 是否为白子正在操作
	bool							white_player_playing;
	// 最后一次落子的位置
	int								lastx, lasty;
	// 上一次落子的位置
	int								prev_lastx, prev_lasty;
};

// 进行游戏的函数
// 第四个参数为落子后是否等待500ms，这是为了防止AI自我对弈时落子过快无法看清
RELEASE_INLINE void playgame(Five_Chess &fc,
	Player_Base *player1, Player_Base *player2,
	bool dosleep = false) noexcept;

// 人类操作
class Human : public Player_Base {
public:
	Human() noexcept = default;
	// 人类的判断可由人类自行完成，故提供空实现
	RELEASE_INLINE void judge	(const Five_Chess &fc)	noexcept override {}
	// 获取鼠标信息，点击时落子
	RELEASE_INLINE void put		(Five_Chess &fc)		noexcept override;
};
#pragma warning(pop)
