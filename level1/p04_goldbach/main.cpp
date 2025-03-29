//哥德巴赫猜想：
//每一个大于2的偶数，都可以表示为两个素数之和

#include <iostream>

using namespace std;


bool isPrime(int n) {
    if (n <= 1)
        return false;
    if (n == 2 || n == 3)
        return true;
    if (n % 2 == 0 || n % 3 == 0)
        return false;

    for (int i = 5; i * i <= n; i += 6) { // 只需检查奇数因子
        if (n % i == 0 || n % (i + 2) == 0)
            return false;
    }
    return true;
}

bool goldbachConjecture(int evenNumber, int* prime1, int* prime2) {
    for (int i = 1; i <= evenNumber / 2; ++i) {
        if (isPrime(i) && isPrime(evenNumber - i)) {
            *prime1 = i;
            *prime2 = evenNumber - i;
            return true;
        }
    }
    return false;
}

int main() {
    cout << "验证100以内的哥德巴赫猜想:" << std::endl;
    for (int evenNumber = 4; evenNumber <= 100; evenNumber += 2) {
        int prime1, prime2;
        bool result = goldbachConjecture(evenNumber, &prime1, &prime2);
        if (result) {
            cout << evenNumber << " = " << prime1 << " + " << prime2 << endl;
        } else {
            cout << evenNumber << " 不能表示为两个素数之和" << endl;
        }
    }
    return 0;
}