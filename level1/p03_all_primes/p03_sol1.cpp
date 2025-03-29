//
// Created by Emerson on 2024/9/23.
//
#include <iostream>
#include <chrono>
using namespace std;
int main() {
    auto start = chrono::high_resolution_clock::now();
    for (int n = 2; n <= 1000; ++n) {
        int flag = 1;
        if (n == 2) flag = 1;
        for (int i = 2; i <= n - 1; ++i) {
            if (n % i == 0) {
                flag = 0;
            }
        }
        if (flag == 1) {
            cout << n <<"is Prime" << endl;
        }
        else {
            cout << n <<"isn't Prime" << endl;
        }
    }
    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);
    cout << "程序运行时间为" << duration.count() << "毫秒" << endl;
    return 0;
}