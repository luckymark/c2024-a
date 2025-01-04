#include <iostream>
#include <cmath> // 用于 sqrt 函数

// 判断是否为素数的函数
bool isPrime(int n) {
    if (n <= 1) {
        return false; // 1 及以下的数不是素数
    }
    if (n == 2) {
        return true; // 2 是素数
    }
    if (n % 2 == 0) {
        return false; // 排除偶数
    }

    // 检查从 3 到 sqrt(n) 的奇数
    for (int i = 3; i <= std::sqrt(n); i += 2) {
        if (n % i == 0) {
            return false; // 如果能整除，则不是素数
        }
    }
    return true; // 否则是素数
}

int main() {
    int n;
    std::cout << "请输入一个正整数: ";
    std::cin >> n;

    if (isPrime(n)) {
        std::cout << n << " 是素数。" << std::endl;
    }
    else {
        std::cout << n << " 不是素数。" << std::endl;
    }

    return 0;
}
