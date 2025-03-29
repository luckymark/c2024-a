#include <iostream>
#include <cmath>
using namespace std;

bool isPrime(int n) {
    if (n <= 1) return false; // 小于等于1的数不是素数
    if (n <= 3) return true;  // 2和3是素数
    if (n % 2 == 0 || n % 3 == 0) return false; // 排除能被2和3整除的数

    // 只需检查到sqrt(n)即可
    for (int i = 5; i * i <= n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0) return false;
    }
    return true;
}

int main() {
    int n;
    cout << "请输入一个正整数: ";
    cin >> n;

    if (isPrime(n)) {
        cout << n << " 是素数。" << endl;
    } else {
        cout << n << " 不是素数。" << endl;
    }

    return 0;
}