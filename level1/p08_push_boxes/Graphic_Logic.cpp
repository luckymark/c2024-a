#include "Graphic_Logic.h"
#include <graphics.h>
#include <stdexcept>
using namespace std;
#if defined _MSVC_LANG && !defined _DEBUG // MSVC RELEASE
#define _ASSERT_(expr, msg) __assume(expr)
#elif defined _DEBUG // DEBUG
#define _ASSERT_(expr, msg)                                 \
    do {    									            \
        if(!expr) {     					                \
    		MessageBox(NULL, _T(msg), _T("Error"), MB_OK);  \
            exit(-1);									    \
        }												    \
    } while(false);
#else // OTHERS RELEASE
#define _ASSERT_(expr, msg)
#endif
Graphic_Logic::Graphic_Logic() {
	initgraph(800, 600);
	level_playing = 0;
}
Graphic_Logic::~Graphic_Logic() {
	closegraph();
}
enum reference {
	Space = 0,
	Box = 1,
	Destination = 2,
	Person = 4,
	Wall = 8
};
class Button {
private:
	int x, y, width, height;
	TCHAR *text;
public:
	Button(int x, int y, int width, int height, const TCHAR *text) :
		x(x), y(y), width(width), height(height), text((TCHAR *) (text)) {}
	void draw(MOUSEMSG &msg) noexcept {
		if(msg.x >= x && msg.x <= x + width && msg.y >= y && msg.y <= y + height) {
			setfillcolor(RGB(233, 233, 233));
			setbkcolor(RGB(233, 233, 233));
		}
		else {
			setfillcolor(RGB(188, 188, 188));
			setbkcolor(RGB(188, 188, 188));
		}
		fillrectangle(x, y, x + width, y + height);
		settextstyle(20, 0, _T("黑体"));
		settextcolor(RGB(0, 0, 0));
		int textWidth = textwidth(text);
		int textHeight = textheight(text);
		int textX = x + (width - textWidth) / 2;
		int textY = y + (height - textHeight) / 2;
		outtextxy(textX, textY, text);
		setbkcolor(RGB(255, 255, 255));
	}
	bool isClicked(MOUSEMSG &msg) const noexcept {
		return msg.x >= x && msg.x <= x + width && msg.y >= y && msg.y <= y + height && msg.uMsg == WM_LBUTTONDOWN;
	}
};
int multibutton(vector<Button> &buttons) {
	MOUSEMSG msg;
	BeginBatchDraw();
	while(true) {
		if(MouseHit()) {
			msg = GetMouseMsg();
			cleardevice();
			for(int i = 0; i < buttons.size(); ++i) {
				buttons[i].draw(msg);
				if(buttons[i].isClicked(msg)) {
					EndBatchDraw();
					return i;
				}
			}
			FlushBatchDraw();
		}
		Sleep(10);
	}
}
// 传入的函数不应含有参数，如果需要，请放在lambda里的中括号里
template<class Function> int multibutton(vector<Button> &buttons, Function fn) {
	MOUSEMSG msg;
	BeginBatchDraw();
	while(true) {
		if(MouseHit()) {
			msg = GetMouseMsg();
			cleardevice();
			fn();
			for(int i = 0; i < buttons.size(); ++i) {
				buttons[i].draw(msg);
				if(buttons[i].isClicked(msg)) {
					EndBatchDraw();
					return i;
				}
			}
			FlushBatchDraw();
		}
		Sleep(10);
	}
}
void Graphic_Logic::menu() {
	vector<Button> buttons = {
		Button(300, 200, 200, 50, _T("开始游戏")),
		Button(300, 300, 200, 50, _T("退出游戏"))
	};
	switch(multibutton(buttons, []() {
		settextcolor(RGB(0, 0, 0));
		settextstyle(50, 0, _T("黑体"));
		outtextxy(320, 100, _T("推箱子"));
	})) {
		case 0:
			return;
		case 1:
			exit(0);
		default:
			_ASSERT_(false, "Invalid button index");
	}
}
int Graphic_Logic::level() {
	vector<Button> buttons = {
		Button(100, 200, 80, 80, _T("第一关")),
		Button(230, 200, 80, 80, _T("第二关")),
		Button(360, 200, 80, 80, _T("第三关")),
		Button(490, 200, 80, 80, _T("第四关")),
		Button(620, 200, 80, 80, _T("第五关")),
		Button(100, 320, 80, 80, _T("第六关")),
		Button(230, 320, 80, 80, _T("第七关")),
		Button(360, 320, 80, 80, _T("第八关")),
		Button(490, 320, 80, 80, _T("第九关")),
		Button(620, 320, 80, 80, _T("第十关")),
		Button(300, 500, 200, 50, _T("返回菜单"))
	};
	level_playing = 1 + multibutton(buttons, []() {
		settextcolor(RGB(0, 0, 0));
		settextstyle(50, 0, _T("黑体"));
		outtextxy(300, 100, _T("选择关卡"));
	});
	return level_playing;
}
void drawPerson(int x, int y, COLORREF color = RGB(255, 0, 0)) {
	y -= 10;
	setfillcolor(color);
	fillcircle(x, y, 10);
	fillrectangle(x - 5, y + 10, x + 5, y + 20);
	fillrectangle(x - 15, y + 10, x - 5, y + 15);
	fillrectangle(x + 5, y + 10, x + 15, y + 15);
	fillrectangle(x - 5, y + 20, x, y + 30);
	fillrectangle(x, y + 20, x + 5, y + 30);
}
//范围：横向x*50到(x+1)*50，纵向y*50到(y+1)*50
void Graphic_Logic::draw(int type, int x, int y) {
	switch(type) {
		case Box:
			setfillcolor(RGB(255, 255, 0));
			fillrectangle(x * 50, y * 50, (x + 1) * 50, (y + 1) * 50);
			break;
		case Destination:
			setfillcolor(RGB(0, 255, 0));
			fillrectangle(x * 50, y * 50, (x + 1) * 50, (y + 1) * 50);
			break;
		case Person:
			drawPerson(x * 50 + 25, y * 50 + 25);
			break;
		case Wall:
			setfillcolor(RGB(180, 30, 30));
			fillrectangle(x * 50, y * 50, (x + 1) * 50, (y + 1) * 50);
			break;
		case Space:
			setfillcolor(RGB(255, 255, 255));
			fillrectangle(x * 50, y * 50, (x + 1) * 50, (y + 1) * 50);
			break;
		case (Person | Destination):
			setfillcolor(RGB(0, 255, 0));
			fillrectangle(x * 50, y * 50, (x + 1) * 50, (y + 1) * 50);
			drawPerson(x * 50 + 25, y * 50 + 25);
			break;
		case (Box | Destination):
			setfillcolor(RGB(112, 224, 255));
			fillrectangle(x * 50, y * 50, (x + 1) * 50, (y + 1) * 50);
			break;
		default:
			_ASSERT_(false, "Invalid type");
			break;
	}
}
void Graphic_Logic::init_level(const vector<vector<int>> &level) {
	_ASSERT_((level.size() == 10 && level[0].size() == 14), "Invalid level message");
	setbkcolor(RGB(255, 255, 255));
	cleardevice();
	for(int i = 0; i < 10; ++i) {
		for(int j = 0; j < 14; ++j) {
			draw(level[i][j], j + 1, i + 1);
		}
	}
	FlushBatchDraw();
}
bool Graphic_Logic::pass() {
	vector<Button> buttons = {
		Button(300, 200, 200, 50, _T("下一关")),
		Button(300, 300, 200, 50, _T("返回菜单"))
	};
	switch(multibutton(buttons, []() {
		settextcolor(RGB(0, 0, 0));
		settextstyle(50, 0, _T("黑体"));
		outtextxy(280, 100, _T("恭喜过关！"));
	})) {
		case 0:
			return true;
		case 1:
			return false;
		default:
			_ASSERT_(false, "Invalid button index");
	}
}
void Graphic_Logic::has_ended() {
	vector<Button> buttons = {
		Button(300, 300, 200, 50, _T("返回菜单"))
	};
	multibutton(buttons, []() {
		settextcolor(RGB(0, 0, 0));
		settextstyle(50, 0, _T("黑体"));
		outtextxy(280, 100, _T("全部通关！"));
	});
}