#include "Graphics Logic.h"
#include "Game Logic.h"
#include "Search_AI.h"
#include <iostream>
#include <fstream>
#pragma comment(lib,"winmm.lib")
using namespace std;

int WINAPI WinMain(_In_ HINSTANCE hin, _In_opt_ HINSTANCE hp, _In_ LPSTR cmd, _In_ int ncmd) {
	init(); // 加载设置、显示游戏画面并播放音乐
	while(true) { // 游戏循环
		int choice = menu(); // 通过菜单栏的返回值获取玩家选项
		switch(choice) {
			case 0: { // 单人游戏
				int			_side = side(); // 选边，0为黑子，1为白子，2为返回
				Five_Chess	fc;
				Search_AI	ai;
				Human		h;
				if		(_side == 2)	break; // 返回主菜单
				else if	(_side == 1)	fc.putchess(7, 7); // 玩家选择白子，在棋盘中间直接摆放一颗黑子
				playgame(fc, &h, &ai); // 进行游戏
				break;
			} // case 0
			case 1: { // 双人游戏
				Five_Chess	fc;
				Human		h;
				playgame(fc, &h, &h); // 玩家与玩家对抗
				break;
			} // case 1
			case 2: { // AI自我对弈
				// 为了给AI对决尽可能增加随机性，我们固定第一颗子放在中央，第二颗子随机放在中央的周围
				Five_Chess	fc;
				char		ch = ' ';
				Search_AI	ai;
				SYSTEMTIME	time; // 以当前的时间作为决定第二颗子的落子位置
				GetLocalTime(&time);
				fc.putchess(7, 7);
				printboard(fc);
				FlushBatchDraw();
				int			_x =  time.wMilliseconds		% 3 - 1,
							_y = (time.wMilliseconds / 3)	% 3 - 1;
				if(_x == 0 && _y == 0) ++_y; // 不能让两颗子重叠
				Sleep(500);
				fc.putchess(7 + _x, 7 + _y);
				printboard(fc);
				FlushBatchDraw();
				Sleep(500);
				playgame(fc, &ai, &ai, true);
				break;
			} // case 2
			case 3: { // 选项
				options();
				break;
			}
			case 4: { // 退出游戏
				writesettings();
				closegraph();
				return 0;
			}
		#ifdef _DEBUG
			case 5: {// 在DEBUG模式下左下角会有“打开编译器进行DEBUG”的选项，点击会启动我的本地文件，从而方便我进行DEBUG
				ShellExecute(nullptr, _T("open"), _T("D:/文档/Visual Studio 2022/C++/Five_Chess/Five_Chess.sln"), 0, 0, SW_SHOWNORMAL);
				writesettings();
				closegraph();
				return 0;
			}
		#endif
			default: __assume(false);
		}
	}
}