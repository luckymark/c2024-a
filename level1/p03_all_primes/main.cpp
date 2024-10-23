//此代码依据埃拉托斯特尼，以实现高效的质数筛查
//算法耗时在0.1ms这个数量级上
//不知道为什么在VS上输出的时间是正常的，但在CLION上输出的时间就是0
//换了好几个方法，有点调不好
#include <iostream>
#include <vector>
#include <chrono>
#include <ratio>
#include <ctime>
using namespace std;

vector<int> sieveOfEratosthenes(int n) {
    vector<bool> isPrime(n + 1, true);  //初始大小n+1,即为0-n，全部初始化为true
    vector<int> primes;
    isPrime[0] = isPrime[1] = false; // 0和1不是素数

    for (int i = 2; i * i <= n; ++i) {
        if (isPrime[i]) {
            for (int j = i * i; j <= n; j += i) {
                isPrime[j] = false;
            }
        }
    }

    for (int i = 2; i <= n; ++i) {
        if (isPrime[i]) {
            primes.push_back(i);
        }
    }
    return primes;
}

int main() {
    int n = 1000;
    auto start = std::chrono::high_resolution_clock::now();

    vector<int>primes = sieveOfEratosthenes(n);

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed(end - start);
    cout << "2-1000以内的所有素数:" << endl;
    for (int prime : primes) {
        cout << prime << " ";
    }
    cout << endl;
    cout << "It took me " << elapsed.count() << " seconds.";
    return 0;
}