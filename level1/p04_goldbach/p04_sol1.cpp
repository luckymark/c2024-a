//
// Created by Emerson on 2024/9/24.
//
#include <iostream>
#include <vector>
using namespace std;

bool isPrime(int num) {
    if (num <= 1) return false;
    for (int i = 2; i * i <= num; ++i) {
        if (num % i == 0) return false;
    }
    return true;
}

void yanzheng(int n) {
    vector<int> primes;
    for (int i = 2; i < n; ++i) {
        if (isPrime(i)) {
            primes.push_back(i);
        }
    }
    for (int even = 4; even <= n; even += 2) {
        bool found = false;
        for (int i = 0; i < primes.size(); ++i) {
            for (int j = i; j < primes.size() && primes[i] + primes[j] <= even; ++j) {
                if (primes[i] + primes[j] == even) {
                    cout << even << " = " << primes[i] << " + " << primes[j] << endl;
                    found = true;
                    break;
                }
            }
            if (found) break;
        }
        if (!found) {
            cout << even << " 不能表示为两个素数之和" << endl;
        }
    }
}

int main() {
    int n = 100;
    yanzheng(n);
    return 0;
}


