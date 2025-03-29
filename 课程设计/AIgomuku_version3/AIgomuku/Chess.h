#pragma once
#include<graphics.h>//easyX图形库的头文件
#include<vector>
using namespace std;

//落子位置
struct ChessPos {
	int row;
	int col;

	ChessPos(int r = 0,int c = 0) : row(r),col(c){}

	bool operator==(const ChessPos& pos) {
		return row == pos.row && col == pos.col;
	}

};

typedef enum {
	CHESS_WHITE = -1, //白棋
	CHESS_BLACK = 1, //黑棋
	CHESS_EMPTY = 0 //空白
}chess_kind_t;

class Chess
{	
public:
	vector<vector<int>> chessMap;
	vector<ChessPos> availableMoves;
	
	Chess(int gradeSize, int marginX, int marginY, float chessSize);

	void FindAvailableMoves();
	//棋盘的初始化：加载棋盘的图片资源，初始化棋盘的相关数据
	void init();

	bool isValid(int x, int y);
	//判断在指定坐标(x,y)位置，是否是有效点击
	bool clickBoard(int x, int y, ChessPos* pos);

	//在指定位置落子
	void chessDown(ChessPos *pos, chess_kind_t kind);
	
	//获取棋盘大小
	int getGradeSize();


	//获取指定位置是黑棋，还是白棋，还是空白
	int getChessData(ChessPos* pos);
	int getChessData(int row, int col);

	//检查棋局是否结束
	bool checkOver();
private:
	IMAGE chessBlackImg;
	IMAGE chessWhiteImg;

	int gradeSize;//棋盘的大小
	int margin_x;//棋盘的左侧边界
	int margin_y;//棋盘的顶部边界
	float chessSize;//棋子的大小(棋盘小方格的大小)
	
	//存储当前棋局的棋子分布数据 0:空白 1:黑子 -1:白子
	//chessMap[3][5] 表示棋盘的第3行第5列
	

	//表示现在该谁下棋
	bool playerFlag;//true:黑子走  false:白子走

	void updateGameMap(ChessPos* pos);

	bool checkWin();//如果胜负已分，返回true,否则返回false

	ChessPos lastPos;//最近落子点的位置
};

