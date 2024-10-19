#pragma once
#ifndef GRAPHIC_LOGIC_H
#define GRAPHIC_LOGIC_H 1
#include <vector>
/*
 * 画面逻辑类
 * 游戏界面大小为800*600，其中每个方格大小为50*50，最外层置空，地图最大为14*10
 * 0代表空地，1代表箱子，2代表目的地，4代表人，8代表墙，使用位运算增强可读性
 * 例如，箱子在目的地上为1 | 2 = 3，人在目的地上为4 | 2 = 6
 * （虽然说最后写出来可读性也跟史一样就是了）
 */
class Graphic_Logic {
public:
	Graphic_Logic();
	~Graphic_Logic();
	void menu();
	//先假定有10关
	int level();
	bool pass();
private:
	//由于最外层置空，x范围为1-14，y范围为1-10
	void draw(int type, int x, int y);
public:
	void init_level(const std::vector<std::vector<int>> &level);
	//正在进行的关卡数，0代表菜单
	int level_playing;
};
#endif // GRAPHIC_LOGIC_H