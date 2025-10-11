#pragma once
#ifndef GAME_LOGIC_H
#define GAME_LOGIC_H 1
#include <vector>
/*
 * 游戏逻辑类
 * 根据画面逻辑类的声明，游戏棋盘为14*10
 */
class Game_Logic {
public:
	Game_Logic();
	std::vector<std::vector<int>> move(char ch);
	//void reset(); // 这部分的逻辑我懒得写了
	int level_playing;
private:
	std::vector<std::vector<std::vector<int>>> boards;
	std::vector<std::vector<int>> player_poses;
};
class Game {
public:
	void play();
};
#endif // GAME_LOGIC_H