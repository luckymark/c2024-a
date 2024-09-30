#include<stdio.h>
void hanoi(int n, char from, char to, char aux) {
	if(n == 1) {
		printf("%c -> %c\n", from, to);
		return;
	}
	hanoi(n - 1, from, aux, to);
	printf("%c -> %c\n", from, to);
	hanoi(n - 1, aux, to, from);
}
void hanota(int n) {
	hanoi(n, 'A', 'C', 'B');
}
int main() {
	int a;
	scanf("%d", &a);
	hanota(a);
	return 0;
}
