#include "AI.h"
#include "Chess.h"
void AI::init(Chess * chess)
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










int AI::alphabeta(int alpha, int beta, bool playerFlag, int depth)
{
	//递归出口
	if (depth <= 0) {
		
		return evaluate(playerFlag);
		
	}
	
	//AI
	if (playerFlag == false) {
		int maxEval = INT_MIN;
		for (auto move : chess->availableMoves) {
			if (hasNeighbour(move.row, move.col) == false) continue;
			chess->chessMap[move.row][move.col] = CHESS_WHITE;
			chess->availableMoves.erase(std::find(chess->availableMoves.begin(), chess->availableMoves.end(), move));
			int eval = alphabeta(alpha, beta, true,depth-1);
			chess->chessMap[move.row][move.col] = CHESS_EMPTY;
			chess->availableMoves.push_back(move);
			maxEval = max(maxEval, eval);
			alpha = max(alpha, eval);
			if (beta <= alpha) {
				break;
			}
		}
		return maxEval;
	}
	else {
		int minEval = INT_MAX;
		for (auto move : chess->availableMoves) {
			if (hasNeighbour(move.row, move.col) == false) continue;
			chess->chessMap[move.row][move.col] = CHESS_BLACK;
			chess->availableMoves.erase(std::find(chess->availableMoves.begin(), chess->availableMoves.end(), move));
			int eval = alphabeta(alpha, beta, false, depth-1);
			chess->chessMap[move.row][move.col] = CHESS_EMPTY;
			chess->availableMoves.push_back(move);
			minEval = min(minEval, eval);
			beta = min(beta, eval);
			if (beta <= alpha) {
				break;
			}
		}
		return minEval;
	}
	

}


ChessPos AI::findBestMove(int depth)
{
	int bestValue = INT_MIN;
	ChessPos bestMove = {-1, -1};
	
	for (auto move : chess->availableMoves) {
		if (hasNeighbour(move.row, move.col) == false) continue;
		chess->chessMap[move.row][move.col] = CHESS_WHITE;
		chess->availableMoves.erase(std::find(chess->availableMoves.begin(), chess->availableMoves.end(), move));
		//先放下棋子，然后对形成的局面进行打分，比如这样走会形成连五，那么这个局面的分数就很高
		int eval = alphabeta(INT_MIN, INT_MAX, true,depth);
		chess->chessMap[move.row][move.col] = CHESS_EMPTY;
		chess->availableMoves.push_back(move);
		printf("Move: (%d, %d) Eval: %d\n", move.row, move.col, eval);
		
		//如果评分一样，随机走一步(待实现)
		if (eval > bestValue) {
			bestValue = eval;
			bestMove = move;
		}
	}
	printf("%d ",bestMove.row);
	printf("%d\n",bestMove.col);
	return bestMove;
}

bool AI::match_shape(int x, int y, int dx, int dy,vector<int>& shape_pattern)
{
	int len = shape_pattern.size();
	for (int k = 0; k < len; ++k) {
		int nx = x + k * dx;
		int ny = y + k * dy;
		if (nx < 0 || ny < 0 || nx >= chess->getGradeSize() || ny >= chess->getGradeSize()) {
			return false;
		}
		int data = chess->getChessData(nx, ny);
		if (data != shape_pattern[k]) {
			return false;
		}
	}
	return true;
}

int AI::evaluate(bool playerFlag)
{
	int total_score = 0;
	int size = chess->getGradeSize();

	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			vector<pair<int,vector<int>>> table;
			if (playerFlag == true) {
				 table = shape_score1;
			}
			else {
				table = shape_score2;
			}
			for (auto& shape : table) {
				int score = shape.first;
				vector<int> shape_pattern = shape.second;


				//横向匹配
				if (match_shape(i, j, 0, 1,shape_pattern)) {
					total_score += score;
				}
				//纵向匹配
				if (match_shape(i, j, 1, 0, shape_pattern)) {
					total_score += score;
				}
				//  "\"
				if (match_shape(i, j, 1, 1, shape_pattern)) {
					total_score += score;
				}
				//  "/"
				if (match_shape(i, j, 1, -1, shape_pattern)) {
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

