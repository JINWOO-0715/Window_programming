
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

#define MAX_NUMBER 10
#define BLACK 0
#define WHITE 1
#define PAN 2

void MakePan();
void PrintPan();

int badukPan[MAX_NUMBER][MAX_NUMBER];

int black_x = 2;
int black_y = 2;

int white_x = 8;
int white_y = 7;

int keyboard = 0;

int main()
{
	int order = 0;
	while (1)
	{
		system("cls");
		MakePan();


		PrintPan();
	
		keyboard = _getch();
		if (order == 0)
		{
			switch (keyboard)
			{

			case 87: case 119:
			{

				if (black_x != 0)
				{
					if (black_x - 1 == white_x && black_y == white_y)
					{
						break;
					}
					badukPan[black_x][black_y] = PAN;
					black_x = black_x - 1;
					badukPan[black_x][black_y] = BLACK;
				}
				else {
					printf_s("\a");

				}

				break;

			case 65:
			case 97:
				if (black_y != 0)
				{
					if (black_y - 1 == white_y && black_x == white_x)
					{
						break;
					}

					badukPan[black_x][black_y] = PAN;
					black_y = black_y - 1;
					badukPan[black_x][black_y] = BLACK;
				}
				else {
					printf_s("\a");
					break;
			case 83:
			case 115:
				if (black_x != MAX_NUMBER - 1)
				{

					if (black_x + 1 == white_x && black_y == white_y)
					{
						break;
					}
					badukPan[black_x][black_y] = PAN;
					black_x = black_x + 1;
					badukPan[black_x][black_y] = BLACK;
				}
				else {
					printf_s("\a");
				}
				break;
			case 68:
			case 100:
				if (black_y != MAX_NUMBER - 1)
				{
					if (black_y + 1 == white_y && black_x == white_x)
					{
						break;
					}
					badukPan[black_x][black_y] = PAN;
					black_y = black_y + 1;
					badukPan[black_x][black_y] = BLACK;
				}
				else {
					printf_s("\a");
				}
				}
				break;
			} order = 1;
			}
	


			if (order == 1)
			{
				switch (keyboard)
				{

		case 73:
		case 105:
			if (white_x != 0)
			{
				if (white_x - 1 == black_x && white_y == black_y)
				{
					break;
				}
				badukPan[white_x][white_y] = PAN;
				white_x = white_x - 1;
				badukPan[white_x][white_y] = WHITE;
			}
			else {
				printf_s("\a");
			}
			break;
		case 74:
		case 106:
			if (white_y != 0)
			{
				if (white_y - 1 == black_y && white_x == black_x)
				{
					break;
				}
				badukPan[white_x][white_y] = PAN;
				white_y = white_y - 1;
				badukPan[white_x][white_y] = WHITE;
			}
			else {
				printf_s("\a");
			}
			break;
		case 75:
		case 107:
			if (white_x != MAX_NUMBER - 1)
			{
				if (white_x + 1 == black_x && white_y == black_y)
				{
					break;
				}
				badukPan[white_x][white_y] = PAN;
				white_x = white_x + 1;
				badukPan[white_x][white_y] = WHITE;
			}
			else {
				printf_s("\a");
			}
			break;
		case 76:
		case 108:
			if (white_y != MAX_NUMBER - 1)
			{
				if (white_y + 1 == black_y && white_x == black_x)
				{
					break;
				}
				badukPan[white_x][white_y] = PAN;
				white_y = white_y + 1;
				badukPan[white_x][white_y] = WHITE;
			}
			else {
				printf_s("\a");
			}
			break;
			}
		
		break;
		}
	}
}

void MakePan()
{
	for (int i = 0; i < MAX_NUMBER; i++)
	{
		for (int j = 0; j < MAX_NUMBER; j++)
		{
			if (i == black_x && j == black_y)
				badukPan[i][j] = BLACK;
			else if (i == white_x && j == white_y)
				badukPan[i][j] = WHITE;
			else
				badukPan[i][j] = PAN;
		}
	}
}

void PrintPan()
 {
	for (int i = 0; i < MAX_NUMBER; i++)
	{
		for (int j = 0; j < MAX_NUMBER; j++)
		{
			switch (badukPan[i][j])
			{
			case BLACK:
				printf_s(" ¡Ü ");
				break;
			case WHITE:
				printf_s(" ¡Û ");
				break;
			case PAN:
				printf_s(" + ");
				break;
			}
		}
		printf("\n");
	}
}