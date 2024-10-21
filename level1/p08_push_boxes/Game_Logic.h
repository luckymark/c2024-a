#pragma once
#ifndef GAME_LOGIC_H
#define GAME_LOGIC_H 1
#include <vector>
/*
 * ��Ϸ�߼���
 * ���ݻ����߼������������Ϸ����Ϊ14*10
 */
class Game_Logic {
public:
	Game_Logic();
	std::vector<std::vector<int>> move(char ch);
	//void reset(); // �ⲿ�ֵ��߼�������д��
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