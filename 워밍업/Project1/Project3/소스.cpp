#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>
#define max 80

void Showmenu();
typedef struct _Point {
	int x = 0;
	int y = 0;
} Point;

typedef struct _Rectangle {
	Point position;
	int width = 0;
	int height = 0;
	int area = 0;

} Rectangle;
/*
void choice(struct _Rectangle q)
{
	int rn, i, j;
	rn = rand() % 8;
	for (i = 0; i < max;)
		printf_s("8개의 값 : %3d %3d %3d %3d %3d %3d");
	
}*/

int main()
{
	
	Rectangle p[40];
	int Rnumber[max];

	int temp,rn;
	char keyboard;

	srand((unsigned int)time(NULL));
	FILE *fp = fopen("rendem.txt", "w");

	for (int i = 0; i < max; i++)
	{
		rn = rand() % 101;
  	Rnumber[i] = rn;
	fscanf(fp, "%d", &Rnumber[i]);

	}
	
	fclose(fp);
	Showmenu();

	/*
	keyboard = getchar();
	while (1)
	{
		switch (keyboard)
		{
		case 65:
		case 97:
			//void ScaleReaarange() 사각형의 크기에 따라 정렬하여 출력
		case 68:
		case 100:
			// void WideReaarange() 사각형의 가로 크기에 따라 정렬하여 출력
		case 83:
		case 115:
			//void ???
		case 82:
		case 114:
			// void Readingpile 파일에서 데이터를 읽어 출력한다.
		case 81:
		case 113:
			exit(0);




		}


	}*/
}


void Showmenu()
{
	printf_s(" a/A : 사각형의 크기에 따라 정렬하여 출력한다.\n");
	printf_s(" d/D: 사각형의 가로의 크기에 따라 정렬하여 출력한다.\n");
	printf_s(" s/S: 파일에 사각형의 구조체의 값 (x, y, 가로, 세로, 면적)을 마지막으로 정렬한 순서대로 한 줄 씩 저장한다.\n");
	printf_s(" r/R: 파일에서 데이터를 읽어 출력한다.\n");
	printf_s(" q/Q: 프로그램 종료\n");
}
	/*p[1].width = abs(p[3].position.x - p[2].position.x);
	p[1].height = abs(p[3].position.y - p[2].position.y);
	p[1].area = p[1].width * p[1].height;
	printf_s(" %3d,%3d,%3d,%3d,%3d,%3d,%3d", p[2].position.x, p[2].position.y,p[3].position.x, p[3].position.y, p[1].width,
		p[1].height, p[1].area);

	return 0;
}*for (i = 0; i < max; i++)
	{

		printf_s("%d,%d", p[i].position.x, p[i].position.y);
		printf_s("\n");
	}*/
		