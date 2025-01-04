#include <iostream>
#include <vector>
#include <chrono> // 用于计算时间

// 埃拉托斯特尼筛法
void sieveOfEratosthenes(int n) {
    std::vector<bool> isPrime(n + 1, true); // 初始化所有数为素数
    isPrime[0] = isPrime[1] = false;        // 0 和 1 非素数

    for (int p = 2; p * p <= n; ++p) {
        if (isPrime[p]) {
            // 标记 p 的倍数为非素数
            for (int i = p * p; i <= n; i += p) {
                isPrime[i] = false;
            }
        }
    }

    // 打印所有素数
    for (int p = 2; p <= n; ++p) {
        if (isPrime[p]) {
            std::cout << p << " ";
        }
    }
    std::cout << std::endl;
}

int main() {
    int n = 1000; // 上限
    std::cout << "2 到 1000 以内的所有素数为：" << std::endl;

    // 记录起始时间
    auto start = std::chrono::high_resolution_clock::now();

    // 调用筛法函数
    sieveOfEratosthenes(n);

    // 记录结束时间
    auto end = std::chrono::high_resolution_clock::now();

    // 计算并打印总时间
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    std::cout << "总计算时间: " << duration.count() << " 微秒" << std::endl;

    return 0;
}