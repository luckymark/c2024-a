#include<Windows.h>
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

int getConsoleWidthAAA(HANDLE* houtput,CONSOLE_SCREEN_BUFFER_INFO* binfo) {
	*houtput = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(*houtput, binfo);
	int width = binfo->srWindow.Right - binfo->srWindow.Left;
	return width;
}
int main() {
	HANDLE a;
	CONSOLE_SCREEN_BUFFER_INFO b;
	char ch[100] = { 0 };
	scanf("%s", ch);
	int len = strlen(ch);
	int spaces = 0;
	bool movingright = true;
	while(1) {
		system("cls");
		int width = getConsoleWidthAAA(&a, &b);
		for(int i = 0; i < spaces; ++i) {
			printf(" ");
		}
		printf("%s", ch);
		if(movingright) {
			++spaces;
			if(spaces + len >= width) movingright = false;
		}
		else {
			--spaces;
			if(spaces <= 0) movingright = true;
		}
		Sleep(400);
	}
	return 0;
}
