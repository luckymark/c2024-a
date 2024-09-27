#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<math.h>
//free res after using it
char *encrypt(char *ori, int id) {
	int len = strlen(ori);
	char *res = (char *) malloc(sizeof(char) * len + 1);
	if(len % 2 == 1) {
		for(int i = 0; i < len; ++i) {
			res[i] = ori[(2 * i >= len ? 2 * i - len : 2 * i)] + id;
		}
	}
	else {
		for(int i = 0; i < len; ++i) {
			res[i] = ori[(2 * i >= len ? 2 * i - len + 1 : 2 * i)] + id;
		}
	}
	res[len] = '\0';
	return res;
}
//same,free res
char *decrypt(char *code, int id) {
	int len = strlen(code);
	char *res = (char *) malloc(sizeof(char) * len + 1);
	if(len % 2 == 1) {
		for(int i = 0; i < len; ++i) {
			res[(2 * i >= len ? 2 * i - len : 2 * i)] = code[i] - id;
		}
	}
	else {
		for(int i = 0; i < len; ++i) {
			res[(2 * i >= len ? 2 * i - len + 1 : 2 * i)] = code[i] - id;
		}
	}
	res[len] = '\0';
	return res;
}
int main() {
	char input[100];
	scanf("%s",input);
	char *enc = encrypt(input, 16);
	printf("%s\n", enc);
	char* dec = decrypt(input, 16);
	printf("%s\n", input);
	free(enc);
	free(dec);
	return 0;
}
