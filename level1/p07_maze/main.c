#include<stdio.h>
#include<stdlib.h>
void printmaze(char maze[11][11]) {
	for(int i = 0; i < 11; ++i) {
		for(int j = 0; j < 11; ++j) {
			printf("%c ", maze[i][j]);
		}
		printf("\n");
	}
}
int main() {
	//0 barrier, 1 people, space space
	char maze[11][11] = {
		{'0','0','0','0','0','0','0','0','0','0','0'},
		{'0','0',' ','0','0',' ','0','0',' ',' ',' '},
		{'0',' ',' ',' ',' ',' ',' ','0',' ','0','0'},
		{'0',' ','0',' ',' ','0',' ','0',' ',' ','0'},
		{'0',' ','0',' ','0','0',' ','0','0',' ','0'},
		{'0',' ','0',' ','0','0',' ','0','0',' ','0'},
		{'0',' ','0','0',' ',' ',' ','0','0',' ','0'},
		{'0',' ','0','0',' ','0','0','0','0',' ','0'},
		{'1',' ','0','0',' ','0','0','0','0',' ','0'},
		{'0',' ',' ','0',' ',' ',' ',' ',' ',' ','0'},
		{'0','0','0','0','0','0','0','0','0','0','0'}
	};
	char choice = ' ';
	int personpos[2] = { 8,0 };
	while(1) {
		system("cls");
		printmaze(maze);
		int _x = personpos[1], _y = personpos[0];
		if(_x == 10 && _y == 1) {
			printf("Success!\n");
			system("pause");
			return 0;
		}
		scanf("%c", &choice);
		switch(choice) {
			case 'w':
			case 'W':
				if(maze[_y - 1][_x] == ' ') {
					maze[_y - 1][_x] = '1';
					maze[_y][_x] = ' ';
					--personpos[0];
				}
				else {
					printf("Invalid move.\n");
					system("pause");
				}
				break;
			case 's':
			case 'S':
				if(maze[_y + 1][_x] == ' ') {
					maze[_y + 1][_x] = '1';
					maze[_y][_x] = ' ';
					++personpos[0];
				}
				else {
					printf("Invalid move.\n");
					system("pause");
				}
				break;
			case 'a':
			case 'A':
				if(maze[_y][_x - 1] == ' ') {
					maze[_y][_x - 1] = '1';
					maze[_y][_x] = ' ';
					--personpos[1];
				}
				else {
					printf("Invalid move.\n");
					system("pause");
				}
				break;
			case 'd':
			case 'D':
				if(maze[_y][_x + 1] == ' ') {
					maze[_y][_x + 1] = '1';
					maze[_y][_x] = ' ';
					++personpos[1];
				}
				else {
					printf("Invalid move.\n");
					system("pause");
				}
				break;
		}
	}
	return 0;
}
