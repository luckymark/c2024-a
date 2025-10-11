# 2024年数据结构与算法A班

# 课程设计: 五子棋AI

## 徐明君

## 2024080902024

![doc版的实验报告](实验报告/五子棋AI实验报告.doc)
> 在实验报告文件夹下有一个doc版的实验报告，此处为md版的

### 一、实验室名称：

电子科技大学清水河校区品学楼C222

### 二、实验项目名称：

基于贪心算法和深度优先搜索算法的五子棋AI

### 三、实验步骤：

1. 问题描述
> 五子棋是一种两人对弈的策略型棋类游戏，需要玩家在棋盘上进行黑白子的交替放置，
目标是率先在横、竖或斜方向上连成五个相同的棋子。
因此，为了实现五子棋AI，我们需要设计一个能够进行有效策略决策和评估的算法和评估函数来实现。
在我的项目中，我采用了深度优先搜索和贪心算法实现搜索，使用连子和是否有遮挡两个参数实现评估。

2. 算法分析与概要设计
> 在本项目中，我们首先使用第三方库EasyX实现了五子棋的界面GUI以便用户操作和调试，
随后采用深度优先搜索和贪心算法的思想，模拟人类的思考模式写AI的下棋策略与方法。

> 五子棋的GUI界面我们使用EasyX实现。
由于EasyX并未提供绘制按钮的接口，在菜单栏界面，我们手动定义按钮类并给出绘制按钮的方法multibutton；
此外我们给出动态绘制棋盘状态的方法printboard，
给出棋型、上一次落子的地点和鼠标的位置对应的落子点，辅助玩家进行分析局势。

> 深度优先搜索（Depth-First Search, DFS）是一种遍历树的算法，
会尽可能深地搜索树的分支，当某一节点的所在边都己被探寻过，搜索将回溯到发现该节点的那条边的起始节点。
贪心算法（Greedy Algorithm）是一种在每一步选择中都采取在当前状态下最好或最优（即最有利）的选择，
从而希望导致结果是最好或最优的算法。
然而，对庞大的五子棋棋盘（15x15）进行完整的深搜，时间复杂度巨大；而仅仅采用贪心算法，又会使得AI短视，
因此我们有必要将两种算法进行结合。
在我的代码实现中，我将深度优先搜索算法和贪心算法结合，只对当次收益更大的点搜索下一层，
这样可以保证搜索效率足够快的同时，可以精确落子到最佳地点。

3. 核心算法的详细设计与实现
   
	3.1. 五子棋的图形界面和胜负判定
   
	3.1.1. 菜单栏
> 菜单栏主要实现两个功能：标题和用户交互。
> 为了实现用户交互，我们定义按钮类；
> 同时，为了菜单栏可以打印多种标题，我们将使用按钮的函数设置为模板函数，传入一个lambda表达式，
> 从而得以打印多种标题。
```cpp
// source_code/Graphics Logic.cpp
// 按钮类，由于并不需要在图像以外的文件内使用，所以不放在Graphics Logic.h中
class Button {
public:
	// 构造函数
	Button(int x, int y, int width, int height, const TCHAR *text) noexcept :
		x(x), y(y), width(width), height(height) {
		_tcscpy(this->text, text);
	}
	// 绘制按钮
	void draw(MOUSEMSG &msg) const noexcept;
	// 返回该按钮是否被按下
	bool isClicked(MOUSEMSG &msg) const noexcept;
private:
	int x, y, width, height;
	TCHAR text[100];
};
// 多个按钮，fn为需要执行的其他命令，如打印标题，返回被点击的按钮的下标
template<class Function> int multibutton(const vector<Button> &buttons, Function fn) noexcept {
	MOUSEMSG msg;
	while(true) {
		msg = GetMouseMsg();
		setbkcolor(Board_Background);
		cleardevice();
		fn();
		for(int i = 0; i < buttons.size(); ++i) {
			buttons[i].draw(msg);
			if(buttons[i].isClicked(msg)) {
				return i;
			}
		}
		FlushBatchDraw();
		Sleep(4);
	}
}
// 应用示例：在选边函数中调用multibutton函数
const vector<tstring> Side_buttons_texts = {
	_T("黑子"),		_T("I choose black"),
	_T("白子"),		_T("I choose white"),
	_T("返回"),		_T("Return")
};
const vector<tstring> Side_texts = {
	_T("选择方向"),	_T("Choose your side")
};
RELEASE_INLINE int side() noexcept {
	vector<Button> side_buttons = {
		Button(240, 250, 200, 50, Side_buttons_texts[		static_cast<size_t>(language)].c_str()),
		Button(240, 350, 200, 50, Side_buttons_texts[2 +	static_cast<size_t>(language)].c_str()),
		Button(240, 450, 200, 50, Side_buttons_texts[4 +	static_cast<size_t>(language)].c_str())
	};
	return (multibutton(side_buttons, []() {
		printmenu(340, 100, Side_texts[						static_cast<size_t>(language)].c_str());
	}));
}
```

3.1.2 棋盘界面
  
> 棋盘界面会先生成一个15x15的空棋盘，
> 再根据传入的Five_Chess类的内容填充相应的落子情况，
> 随后根据最近一次的落子添加提示，最后根据鼠标信息提示点击在此处会落子的地点。
```cpp
// source_code/Graphics Logic.cpp
RELEASE_INLINE void printboard(const Five_Chess &game, const MOUSEMSG &msg) noexcept {
	setbkcolor(Board_Background);
	cleardevice();
	// 画空棋盘
	setlinecolor(BLACK);
	for(int i = 0; i < 15; ++i) {
		int offset = 50 + i * 40;
		line(50,		offset, 	610,		offset);
		line(offset,	50,		offset, 	610);
	}
	// 画棋子
	for(int i = 0; i < 15; ++i) {
		for(int j = 0; j < 15; ++j) {
			int x = 50 + i * 40;
			int y = 50 + j * 40;
			if(game.chessboard[i][j] == '1') {
				setfillcolor(WHITE);
				setlinecolor(BLACK);
				solidcircle(x, y, 15);
				circle(x, y, 15);
			}
			else if(game.chessboard[i][j] == '2') {
				setfillcolor(BLACK);
				solidcircle(x, y, 15);
			}
		}
	}
	// 为最近落的子标记红点
	if(game.lastx != -1 && game.lasty != -1) {
		setfillcolor(RED);
		solidcircle(50 + game.lastx * 40, 50 + game.lasty * 40, 5);
	}
	// 根据鼠标消息画鼠标下方的子，做提示
	if(msg.x < 5 && msg.y < 5) return;
	int _x = (msg.x - 25) / 40, _y = (msg.y - 25) / 40;
	if(_x >= 0 && _x < 15 && _y >= 0 && _y < 15 &&
		game.chessboard[_x][_y] == ' ') {
		int x = 50 + _x * 40;
		int y = 50 + _y * 40;
		if(game.white_player_playing)	setfillcolor(LIGHTGRAY);
		else					setfillcolor(DARKGRAY);
		solidcircle(x, y, 15);
	}
	FlushBatchDraw();
}
```
3.1.3. 判断胜负逻辑
> 简单判断棋盘上是否有五颗子相连即可。
3.2. 五子棋的AI算法
> 我的AI算法基于我下五子棋的经验：对方的最优解，往往是我的最优解。
> 原因很简单：对方下在这里五子连珠，我就要在这里堵住对方；对方下在这里活四，我就要在这里堵住；
> 反过来说，对方可能在这里堵住我，那说明这里对我有利。
  
> 在我的AI算法中，对每一个空格子进行分数值估算。
> 分数值的估算基于两点：某个格子附近是否有连子，以及连子是否被另一方棋子遮挡。
> 在每一层的搜索中，搜索得到分数最大的所有空格子，随后对这些分数最大的空格子进行递归搜索，
> 最终得到在搜索层数达到所设置的最大层数时，所能得到的最大分数的格子，将最终的棋子落在此处。
```cpp
// source_code/Search_AI.h
// 搜索AI类
class Search_AI : public Player_Base {
public:
	using score_t = unsigned long long;
	Search_AI	(int md = 14) : maxdepth(md), max_of_judgement(0ULL) {}
	void	judge	(const Five_Chess &fc)		noexcept override;
	void	put	(Five_Chess &fc)		noexcept override;
private:
	score_t put	(Five_Chess &fc, int depth) noexcept;			// 递归的put函数，重写的put函数基于此函数实现
	std::vector<std::vector<score_t>>	judgement;			// 使用judgement数组存储每一个格子的估值
	score_t					max_of_judgement;		// 保存判断最大值，空间换时间
	int					maxdepth;			// 最大深度
	static constexpr score_t		inf = static_cast<score_t>(-1) >> 4; // 无穷，右移4避免溢出
	static constexpr score_t		score_ref[5] = { 1ull, 1ull << 5, 1ULL << 12, 1ULL << 23, 1ULL << 40 }; // 棋盘类型对应的得分估值数组
};
// source_code/Search_AI.cpp
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
                return  inf * static_cast<double>((maxdepth - depth + 2)) / static_cast<double> (maxdepth);
            }
            judge(fc);
            score_t score = max_of_judgement;
            if(depth != 0) fc.rmchess(row, col);
            else return static_cast<score_t>(-1);
            return      score * static_cast<double>((maxdepth - depth + 2)) / static_cast<double>(maxdepth);
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
                return  inf * static_cast<double>((maxdepth - depth + 2)) / static_cast<double>(maxdepth);
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
```
### 四、实验数据及结果分析：
实验结果表明：我的AI虽然具有了一定分析棋盘并落子的能力，并在和网上的AI的对弈中取得了不错的成果，但与同学们的AI还有很大差距。

对我的AI代码进行分析可知，我的AI在很多方面有所欠缺。
例如，在面对左图这种情况，我的AI（执黑）会落子到红圈处，因为在我的代码的实现中，这里的评分可能会更高，而实际上落子到此处并不能解决白子即将胜利的问题。

此外，我的AI对边界条件的处理依然不够完美，这导致我的AI可能会落子到边界上根本不能连成五子连珠的地点，造成无效落子。
以及，在与同学的基于Alpha-Beta剪枝算法的AI的对弈当中，我的AI展现出了较大的劣势。我认为，这可能也与上述原因有关，适当优化评分函数和边界条件，可能会使我的AI战力提升。

### 五、总结及心得体会：

在实践中，我的AI算法表现出了一定的局限性。评分函数设置的不合理、递归中的逻辑问题等问题导致了我的AI并未获得很强的战斗力。
在本次的实践中，我认识到了我与同龄人之间的差距，同时也明确了我接下来的计划：在逻辑和算法方面狠下功夫，通过大量的训练拥有足够的算法处理能力，
从而可以更完整、优秀地完成更加复杂的现实问题。

此外，在实践中，我深刻意识到了增强代码可读性的必要性。
在一开始，我的代码显得格外臃肿，有着各种不必要的开销、变量和方法，代码的可读性也异常差。
而在我的多轮重构之下，代码的可读性增强了许多，我对代码的修改与修补速度也加快了不少。
这说明，写代码时保持良好的命名规范、增加注释，有助于我们更好地书写后面的代码，也有助于后人维护、修改。

### 六、对本实验过程及方法、手段的改进建议及展望：

在过程中，我认为可以培养好更合理的编程习惯，掌握良好的命名方法等规范，以免在后期Debug和添加新功能时的痛苦。

在方法上，我认为可以更好的编写我的评分函数，增加根据自己的方向决定权重的算法，使用更复杂的逻辑和更严格的算法来实现更精确的评分函数，从而更好的落子，提升AI的实力。

在手段上，我认为可以编写更严谨的边界处理条件，减少棋子落在边界处造成无效落子从而失先的可能性，减少AI犯的错误，从而增加胜算。

-----------

![战五渣.jpg](真是个战五渣，电脑都打不过.png)

TaT
