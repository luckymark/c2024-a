//
// Created by Emerson on 2024/9/24.
//
#include <iostream>
using namespace std;

void hanoi(int n, char from_rod, char to_rod, char aux_rod) {
    if (n == 1) {
        cout <<"移动盘子" << n << " " <<from_rod << " -> " << to_rod << endl;
        return;
    }
    hanoi(n - 1, from_rod, aux_rod, to_rod);//把n-1个盘子当成一个整体，从A移到B，借助C
    cout << "移动盘子" << n << " "<<from_rod << " -> " << to_rod << endl;
    hanoi(n - 1, aux_rod, to_rod, from_rod);//交换B和A的位置，把A当成辅助柱子，B当成起点柱子
}

int main() {
    int n = 64;
    char from_rod = 'A';
    char to_rod = 'C';
    char aux_rod = 'B';

    cout << "汉诺塔的解决方案:\n";
    hanoi(n, from_rod, to_rod, aux_rod);
    return 0;
}