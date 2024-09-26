#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<math.h>
bool isprime(unsigned long long n) {
	int a = sqrt(n);
	for(int i = 2; i <= a; ++i) {
		if(n % i == 0) return false;
	}
	return true;
}
int main() {
	unsigned long long a;
	scanf("%llu", &a);
	(isprime(a) ? printf("%llu is a prime", a) : printf("%llu is not a prime", a));
	return 0;
}
