#include<iostream>
using namespace std;

int main() {
    //递归算法
    void hanoi(char,char,char,int);
    char x = 'A', y = 'B', z = 'C';//三个底座
    int n;
    cout << "input n:" ;
    cin >> n;
    cout << "the step of"<<" " << n << " " <<"disk" << " moving:" << endl;
    hanoi(x, y, z, n);
    return 0;
}
void hanoi(char x, char y, char z, int n) {
    void move(char, char);

    //整个hanoi函数只有当n = 1时才会执行移到盘子的动作；

    if (n == 1) {
        move(x, z);
    }
    else {
        hanoi(x, z, y, n - 1);//将n-1个盘子从A座借用C座移动到B座
        move(x, z);//将A座的最大盘子移到C座
        hanoi(y, x, z, n - 1);//将B座的n-1个盘子从B座借用A座移动到C座
    }

}
void move(char x,char y) {
    cout << x << "->" << y << endl;
}
