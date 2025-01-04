#include <iostream>
#include <stack>
#include <utility>

// 非递归汉诺塔实现
void hanoiNonRecursive(int n, char from, char to, char aux) {
    std::stack<std::pair<int, char>> stack; // 用于模拟递归调用栈
    stack.push({ n, from }); // 初始状态

    while (!stack.empty()) {
        auto current = stack.top();
        stack.pop();

        int num = current.first;
        char src = current.second;
        char dest = (src == from && num % 2 != 0) ? to : aux; // 目标柱子
        char temp = (src == from && num % 2 != 0) ? aux : to; // 辅助柱子

        if (num == 1) {
            std::cout << "将盘子 1 从 " << src << " 移动到 " << dest << std::endl;
        }
        else {
            // 模拟递归调用
            stack.push({ num - 1, temp });
            stack.push({ 1, src });
            stack.push({ num - 1, src });
        }
    }
}

int main() {
    int n;

    // 输入盘子的数量
    std::cout << "请输入盘子的数量: ";
    std::cin >> n;

    // 调用非递归汉诺塔函数
    hanoiNonRecursive(n, 'A', 'C', 'B');

    return 0;
}