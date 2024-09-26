#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<time.h>
#include<math.h>
bool isprime(unsigned long long n) {
	int a = sqrt(n);
	for(int i = 2; i <= a; ++i) {
		if(n % i == 0) return false;
	}
	return true;
}
int main() {
	clock_t tprev = clock();
	for(int i = 2; i < 1000; ++i) {
		if(isprime(i)) {
			printf("%d\n", i);
		}
	}
	clock_t tnow = clock();
	printf("消耗了%ld毫秒", tnow - tprev);
	return 0;
}
