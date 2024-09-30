#include<stdbool.h>
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
bool isPrime(int n) {
    if(n < 2) return false;
    for(int i = 2; i <= sqrt(n); ++i) {
        if(n % i == 0) return false;
    }
    return true;
}
bool Goldbach(int limit) {
    for(int n = 4; n <= limit; n += 2) {
        bool found = false;
        for(int i = 2; i <= n / 2; ++i) {
            if(isPrime(i) && isPrime(n - i)) {
                found = true;
                break;
            }
        }
        if(!found) return false;
    }
    return true;
}
int main() {
    for(int i = 2; i < 100; i += 2) {
        if(Goldbach(i)) printf("%d follows GoldBash conjecture.\n", i);
        else printf("%d doesn't follow Goldbash conjecture.\n", i);
    }
    return 0;
}
