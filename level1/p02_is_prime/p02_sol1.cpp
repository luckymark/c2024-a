//
// Created by Emerson on 2024/9/23.
//

#include <iostream>
using namespace std;
int main() {
    int n;
    int flag = 1;
    cin >> n;
    if(n <= 0) return 0;
    if(n == 1 || n == 2) flag = 1;
    for(int i = 2;i <= n-1;++i) {
        if(n % i == 0) {
            flag = 0;
        }
    }
    if(flag == 1) {
        cout << "is Prime" << endl;
    }else {
        cout << "isn't Prime" << endl;
    }
}