#include "AI.h"
#include "Chess.h"
#include <iostream>
void AI::init(Chess* chess)
{
	this->chess = chess;
	int size = chess->getGradeSize();
	for (int i = 0; i < size; i++) {
		vector<int> row(size, 0);
		scoreMap.push_back(row);
	}
}
void AI::go()
{
	ChessPos pos = findBestMove(3);//偶数黑子下，奇数白子下
	Sleep(1000); //假装思考
	chess->chessDown(&pos, CHESS_WHITE);
	printf("白子落子位置%d %d\n", pos.row, pos.col);
}


int AI::alphabeta(int alpha, int beta, bool playerFlag, int depth, vector<ChessPos> choices, vector<vector<int>> Map)
{
	/*cout << "a";*/
	//递归出口
	if (depth <= 0) {
		/*cout << "." ;*/
		return evaluate(playerFlag, Map);
	}

	vector<ChessPos>choicesCopy = choices;

	//AI
	if (playerFlag == false) {
		int maxEval = INT_MIN;

		vector<thread>threads;

		for (auto move : choicesCopy) {
			if (hasNeighbour(move.row, move.col) == false) continue;
			Map[move.row][move.col] = CHESS_WHITE;
			choices.erase(find(choices.begin(), choices.end(), move));

			/*threads.push_back(thread([=, &maxEval,&alpha]() {
				int eval = alphabeta(alpha, beta, true, depth - 1, choices, Map);
				lock_guard<mutex>lock(mtx);
				maxEval = max(maxEval, eval);
				alpha = max(alpha, eval);
				}));*/

			int eval = alphabeta(alpha, beta, true, depth - 1, choices, Map);
			maxEval = max(maxEval, eval);
			alpha = max(alpha, eval);
			
			Map[move.row][move.col] = CHESS_EMPTY;
			choices.push_back(move);
			
			if (beta <= alpha) {
				break;
			}
		}

		// 等待所有线程完成
		/*for (auto& th : threads) {
			th.join();
		}*/

		return maxEval;
	}
	else {
		int minEval = INT_MAX;

		vector<thread>threads;

		for (auto move : choicesCopy) {
			if (hasNeighbour(move.row, move.col) == false) continue;
			Map[move.row][move.col] = CHESS_BLACK;
			choices.erase(find(choices.begin(), choices.end(), move));

			/*threads.push_back(thread([=, &minEval,&beta]() {
				int eval = alphabeta(alpha, beta, false, depth - 1, choices, Map);
				lock_guard<mutex>lock(mtx);
				minEval = min(minEval, eval);
				beta = min(beta, eval);
				}));*/

			int eval = alphabeta(alpha, beta, false, depth - 1, choices, Map);
			minEval = min(minEval, eval);
			beta = min(beta, eval);
			
			Map[move.row][move.col] = CHESS_EMPTY;
			choices.push_back(move);
			
			if (beta <= alpha) {
				break;
			}
		}

		/*for (auto& th : threads) {
			th.join();
		}*/

		return minEval;
	}


}


ChessPos AI::findBestMove(int depth)
{
	bestValue = INT_MIN;
	bestMove = { -1, -1 };

	vector<thread>threads;
	vector<ChessPos> availableMovesCopy = chess->availableMoves;

	for (auto move : availableMovesCopy) {
		if (hasNeighbour(move.row, move.col) == false) continue;

		// 为每个线程创建独立的 Map 和 choices 副本
		/*vector<vector<int>> mapCopy = chess->chessMap;
		vector<ChessPos> choicesCopy = chess->availableMoves;*/

		chess->chessMap[move.row][move.col] = CHESS_WHITE;
		chess->availableMoves.erase(find(chess->availableMoves.begin(), chess->availableMoves.end(), move));

		//启动线程
		threads.push_back(thread([=]() {
			printf("A thread was successfully launched at point(%d, %d)\n", move.row, move.col);
			int eval = alphabeta(INT_MIN, INT_MAX, true, depth, chess->availableMoves, chess->chessMap);
			lock_guard<mutex>lock(mtx);
			if (eval > bestValue) {
				bestValue = eval;
				bestMove = move;
			}
			printf("Value at point(%d, %d): %d\n", move.row, move.col, eval);
			
			}));
		/*Sleep(800);*/
		//先放下棋子，然后对形成的局面进行打分，比如这样走会形成连五，那么这个局面的分数就很高
		
		chess->chessMap[move.row][move.col] = CHESS_EMPTY;
		chess->availableMoves.push_back(move);
	}

	// 等待所有线程完成
	for (auto& th : threads) {
		th.join();
	}

	printf("%d ", bestMove.row);
	printf("%d\n", bestMove.col);
	return bestMove;
}

bool AI::match_shape(int x, int y, int dx, int dy, vector<int>& shape_pattern, vector<vector<int>> Map)
{
	int len = shape_pattern.size();
	for (int k = 0; k < len; ++k) {
		int nx = x + k * dx;
		int ny = y + k * dy;
		if (nx < 0 || ny < 0 || nx >= chess->getGradeSize() || ny >= chess->getGradeSize()) {
			return false;
		}
		int data = Map[nx][ny];
		if (data != shape_pattern[k]) {
			return false;
		}
	}
	return true;
}

int AI::evaluate(bool playerFlag, vector<vector<int>> Map)
{
	int total_score = 0;
	int size = chess->getGradeSize();

	vector<pair<int, vector<int>>> table;
	if (playerFlag == true) {
		table = shape_score1;
	}
	else {
		table = shape_score2;
	}

	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			
			for (auto& shape : table) {
				int score = shape.first;
				vector<int> shape_pattern = shape.second;
				/*cout << ".";*/
				//横向匹配
				if (match_shape(i, j, 0, 1, shape_pattern, Map)) {
					total_score += score;
				}
				//纵向匹配
				if (match_shape(i, j, 1, 0, shape_pattern, Map)) {
					total_score += score;
				}
				//  "\"
				if (match_shape(i, j, 1, 1, shape_pattern, Map)) {
					total_score += score;
				}
				//  "/"
				if (match_shape(i, j, 1, -1, shape_pattern, Map)) {
					total_score += score;
				}
			}
		}
	}
	return total_score;


}

bool AI::hasNeighbour(int row, int col)
{
	for (int i = -1; i <= 1; ++i) {
		for (int j = -1; j <= 1; ++j) {
			if (i == 0 && j == 0) continue;
			int newrow = row + i;
			int newcol = col + j;
			if (newrow >= 0 && newrow < chess->getGradeSize() &&
				newcol >= 0 && newcol < chess->getGradeSize() &&
				chess->getChessData(newrow, newcol) != CHESS_EMPTY) {
				return true;
			}
		}
	}

	return false;
}