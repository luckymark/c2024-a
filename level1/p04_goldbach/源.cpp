#include <iostream>
#include <vector>

// 函数用于检查一个数是否为质数
bool isPrime(int n) {
    if (n <= 1) return false;
    if (n <= 3) return true;
    if (n % 2 == 0 || n % 3 == 0) return false;
    for (int i = 5; i * i <= n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0) return false;
    }
    return true;
}

// 函数用于验证哥德巴赫猜想
void verifyGoldbachConjecture(int limit) {
    for (int i = 4; i <= limit; i += 2) {
        bool found = false;
        for (int j = 2; j <= i / 2; ++j) {
            if (isPrime(j) && isPrime(i - j)) {
                std::cout << i << " = " << j << " + " << (i - j) << std::endl;
                found = true;
                break;
            }
        }
        if (!found) {
            std::cout << "哥德巴赫猜想在 " << i << " 处不成立！" << std::endl;
        }
    }
}

int main() {
    int limit = 100;
    verifyGoldbachConjecture(limit);
    return 0;
}