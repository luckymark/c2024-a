#pragma once
#include "Common.h"
#include "Game Logic.h"
#include <graphics.h>
// 语言的枚举类
enum Language : char {
	Chinese = 0,
	English = 1
};
// 当前的语言
// 所有的全局变量放在头文件中都需要extern
extern Language language;

// 读写设置
RELEASE_INLINE void		readsettings()	noexcept;
RELEASE_INLINE void		writesettings() noexcept;
// 打印提示信息
RELEASE_INLINE void		printhint(int x, int y, const TCHAR *str);
// 被占据时抛出的异常类
class Occupied {
public:
	// 构造时发出提示
	RELEASE_INLINE		Occupied() noexcept;
};
// 初始化操作
RELEASE_INLINE void		init() noexcept;
// 初始菜单
RELEASE_INLINE int		menu() noexcept;
// 鼠标在左上角的鼠标消息
const MOUSEMSG no_msg = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };
// 显示棋盘
RELEASE_INLINE void		printboard(const Five_Chess &game, const MOUSEMSG &msg = no_msg) noexcept;
// 选项界面
RELEASE_INLINE void		options() noexcept;
// 选边
RELEASE_INLINE int		side() noexcept;