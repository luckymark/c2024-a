#include "Search_AI.h"
#include <unordered_map>
#ifdef _DEBUG
#include <iostream>
#include <iomanip>
// 分隔符
constexpr char separator[] = "--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n\n";
#endif
using namespace std;
#pragma warning(push)
#pragma warning(disable: 4244) // double转score_t可能会有精度损失，但是这里不需要精度

constexpr int directions[4][2] = { {1, 0}, {0, 1}, {1, 1}, {1, -1} }; // 方向数组
void Search_AI::judge(const Five_Chess &fc) noexcept {
	judgement = vector<vector<score_t>>(15, vector<score_t>(15, 0ull)); // 初始化判断
	max_of_judgement = 0; // 初始化最大值
	auto possible_moves = fc.generate_possible_moves(); // 获取所有的空格
	for(auto &[x, y] : possible_moves) { // 对每一个空格的得分进行估值
		for(int direction_index = 0; direction_index < 4; ++direction_index) {
			int dx = directions[direction_index][0], dy = directions[direction_index][1]; // 计算方向
			int left_count = 0, right_count = 0, left_blocked = 0, right_blocked = 0; // 计算相连棋子的个数以及是否被遮挡
			char left_record = ' ', right_record = ' '; // 记录左右两边的棋子
			if(x + dx < 0 || y + dy < 0 || x + dx > 14 || y + dy > 14) { // 如果越界，直接认为没有相连的棋子
				right_count = 0;
				right_blocked = 1;
			}
			else if(fc.chessboard[x + dx][y + dy] == ' ') right_count = 0; // 相连的一格是空的
			else {
				right_record = fc.chessboard[x + dx][y + dy]; // 记录相连的一格
				for(int offset = 1; offset < 5; ++offset) { // 扫4格
					int nx = x + dx * offset, ny = y + dy * offset; // 计算偏移量
					if(nx >= 0 && nx <= 14 && ny >= 0 && ny <= 14) { // 保证不越界
						if(fc.chessboard[nx][ny] == right_record) {
							right_count = offset; // 相同，计数
						}
						else if(fc.chessboard[nx][ny] != ' ') {
							right_blocked = 1; // 不相同，说明封路
							break;
						}
						else break; // 空，退出
					}
					else { // 如果越界，外面是下不了的，认为有封路
						right_blocked = 1;
						break;
					}
				}
			}
			// 同上逻辑
			if(x - dx < 0 || y - dy < 0 || x - dx > 14 || y - dy > 14) {
				left_count = 0;
				left_blocked = 1;
			}
			else if(fc.chessboard[x - dx][y - dy] == ' ') left_count = 0;
			else {
				left_record = fc.chessboard[x - dx][y - dy];
				for(int offset = 1; offset < 5; ++offset) {
					int nx2 = x - dx * offset, ny2 = y - dy * offset;
					if(nx2 >= 0 && nx2 <= 14 && ny2 >= 0 && ny2 <= 14) {
						if(fc.chessboard[nx2][ny2] == left_record) {
							left_count = offset;
						}
						else if(fc.chessboard[nx2][ny2] != ' ') {
							left_blocked = 1;
							break;
						}
						else break;
					}
					else {
						left_blocked = 1;
						break;
					}
				}
			}
			// 计算该点的得分
			// 如果两边相等，都有封路且总数小于4，这里不可能连成五子连珠，直接跳过
			if((left_record == right_record) && left_blocked && right_blocked && (left_count + right_count < 4)) {
				continue;
			}
			// 如果两边有一边越界，且另一边小于4，这里不可能连成五子连珠，直接跳过
			else if((left_record == ' ') ^ (right_record == ' ') && (left_count < 4) && (right_count < 4) &&
				left_blocked && right_blocked) {
				continue;
			}
			// 如果两边均不为空且不相等，且每一边均小于4，这里不可能连成五子连珠，直接跳过
			else if((left_record != ' ') && (right_record != ' ') &&
				(left_record != right_record) && (left_count < 4) && (right_count < 4)) {
				continue;
			}
			// 正常情况
			else {
				judgement[x][y] +=
					(left_blocked  ? 0.1 : 1.) * score_ref[left_count] *
					(right_blocked ? 0.1 : 1.) * score_ref[right_count];
			}
		}
		// 更新最大值
		max_of_judgement = max(max_of_judgement, judgement[x][y]);
	}
}

Search_AI::score_t Search_AI::put(Five_Chess &fc, int depth) noexcept {
	// 先判断
	judge(fc);
	// 保存最大值的点
	vector<pair<int, int>> max_positions;
	// 递归到最深处，直接返回
	if(depth >= maxdepth) {
		return max_of_judgement;
	}
	// 当最大值为0时，说明游戏必为平局
	if(max_of_judgement == 0 && depth == 0) {
		auto [x, y] = fc.generate_possible_moves()[0];
		fc.putchess(x, y);
		return 0ULL;
	}
	else {
		// 获取分数最大的所有点
		for(auto [row, col] : fc.generate_possible_moves()) {
			// 相对误差小于一定值
			if((abs(static_cast<double>(judgement[row][col] - max_of_judgement))
				/ static_cast<double>(max_of_judgement)) < 0.03 &&
				judgement[row][col] != 0) {
				max_positions.emplace_back(row, col);
			}
		}
		// 如果最大的点只有一个，直接返回
		if(max_positions.size() == 1) {
			auto [row, col] = max_positions[0];
			fc.putchess(row, col);
			// 特判：游戏是否结束
			char winner;
			if(fc.has_ended(winner)) {
				if(depth != 0) fc.rmchess(row, col); // 只有当深度不为0时才需要移除该棋子
				return  inf     * static_cast<double>((maxdepth - depth + 2)) / static_cast<double> (maxdepth);
			}
			judge(fc);
			score_t score = max_of_judgement;
			if(depth != 0) fc.rmchess(row, col);
			else return static_cast<score_t>(-1);
			return      score   * static_cast<double>((maxdepth - depth + 2)) / static_cast<double> (maxdepth);
		}
		int best_row = -1, best_col = -1;
		score_t max_score = 0ull;
		// 对于每一个最大的点，递归搜索在继续落子的情况下，对应的最大的点
		for(auto [row, col] : max_positions) {
			fc.putchess(row, col);
			char winner;
			if(fc.has_ended(winner)) {
				if(depth != 0) {
					fc.rmchess(row, col);
				}
				return  inf     * static_cast<double>((maxdepth - depth + 2)) / static_cast<double> (maxdepth);
			}
			judge(fc);
			score_t current_score = put(fc, depth + 1);
			if(max_score < current_score) {
				max_score = current_score;
				best_row = row, best_col = col;
			}
			fc.rmchess(row, col);
		}
		// 如果深度为0，在最大点落子
		if(depth == 0) {
			fc.putchess(best_row, best_col);
			return static_cast<score_t>(-1);
		}
		else {
			return      max_score * static_cast<double>((maxdepth - depth + 2)) / static_cast<double>(maxdepth);
		}
	}
}

void Search_AI::put(Five_Chess &fc) noexcept {
//#ifdef _DEBUG
//	// 在DEBUG模式下打印judgement
//	for(int i = 0; i < 15; ++i) {
//		for(int j = 0; j < 15; ++j) {
//			cout << setw(16) << judgement[j][i] << "\t";
//		}
//		cout << "\n\n";
//	}
//	cout << separator;
//#endif
	put(fc, 0);
}
#pragma warning(pop)
