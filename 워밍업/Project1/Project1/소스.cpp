#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#define HANG 4
#define YEOL 5

void seven(int _array[HANG][YEOL]);
void triple(int _array[HANG][YEOL]);
void upscale(int _array[HANG][YEOL]);
void choice();
void max(int _array[HANG][YEOL]);
void makeArray(int _array[HANG][YEOL], int number);
bool checkoverlap(int _checkNumber, int _array[HANG][YEOL]);
void downscale(int _array[HANG][YEOL]);
void min(int _array[HANG][YEOL]);
void retry(int _array[HANG][YEOL]);
void plusfive(int _array[HANG][YEOL]);
void three(int _array[HANG][YEOL]);
int hang[HANG][YEOL];
void rearrange(int _array[HANG][YEOL], int length);

int main()
{
	int j, i, a;
	char ginung;
	while (1)
	{
		printf_s("  �ִ� ���ڸ� �Է��ϼ���");
		rewind(stdin);
		scanf_s("%d", &a);

		if (a >20)
		{
			break;
		}
	}

	srand((unsigned int)time(NULL));

	makeArray(hang, a);


	for (i = 0; i < HANG; i++)
	{
		for (j = 0; j < YEOL; j++)
		{
			printf_s("%3d ", hang[i][j]);
		}
		printf_s(" \n");
	}
	printf_s(" \n");

	while (1)
	{
		choice();
		rewind(stdin);
		scanf_s("%c", &ginung);
		if (ginung == 'A')
			upscale(hang);
		else if (ginung == 'D')
			downscale(hang);
		else if (ginung == 't')
			triple(hang);
		else if (ginung == 's')
			seven(hang);
		else if (ginung == 'M')
			max(hang);
		else if (ginung == 'N')
			min(hang);
		else if (ginung == 'p')
			retry(hang);
		else if (ginung == 'R')
			rearrange(hang, HANG*YEOL);
		else if (ginung == 'Q')
			exit(0);
		else if (ginung == '1')
			plusfive(hang);
		else if (ginung == '2')
			three(hang);
		else
		{
			printf("�߸��� �Է��Դϴ� �ٽ� �Է����ּ���");

		}
	}



	return 0;
}

void choice()
{
	printf_s("���ϴ� ����� �Է��ϼ���\n");
	printf_s("A :1�� 1���� �������� �࿡ ���� ������������ ����\n");
	printf_s("D :4�� 5���� �������� �������� ������������ ���� \n");
	printf_s("t: 3�� ��� ����ϱ� (3�� ��� �ܿ��� 0���� ��� \n");
	printf_s("M: �ִ밪 ��� \n");
	printf_s("N: �ּҰ� ���  \n");
	printf_s("1: Ȧ������ ���ڿ� 5�� ���Ͽ� ��� \n");
	printf_s("2: ¦������ ���ڿ� 7�� ���� ��� \n");
	printf_s("p: �ٽ� �Է¹ޱ� ���� \n");
	printf_s("R: �����ϰ� ������ \n");
	printf_s("Q: ���α׷� ���� \n");
}

bool checkoverlap(int _checkNumber, int _array[HANG][YEOL])
{
	for (int i = 0; i < HANG; i++)
	{
		for (int j = 0; j < YEOL; j++)
		{
			if (_array[i][j] == _checkNumber)
			{
				return true;
			}
		}
	}
	return false;
}

void max(int _array[HANG][YEOL])
{
	int temp = _array[0][0];
	for (int i = 0; i < HANG; i++)
	{
		for (int j = 0; j < YEOL; j++)
		{
			if (_array[i][j] > temp)

			{
				temp = _array[i][j];
			}


		}

	}
	printf_s("�ִ��� %d �Դϴ�", temp);

}

void min(int _array[HANG][YEOL])
{
	int temp = _array[0][0];
	for (int i = 0; i < HANG; i++)
	{
		for (int j = 0; j < YEOL; j++)
		{
			if (_array[i][j] < temp)

			{
				temp = _array[i][j];
			}


		}

	}
	printf_s("�ּڰ��� %d �Դϴ�", temp);

}

void upscale(int _array[HANG][YEOL])
{
	int temparry[20];
	int k = 0;

	int temp, i, j;
	for (i = 0; i < HANG; i++)
	{
		for (j = 0; j < YEOL; j++)
		{
			temparry[k] = _array[i][j];
			k++;

		}
		printf_s(" \n");
	}

	for (i = 0; i < HANG*YEOL - 1; i++)
	{
		for (j = 0; j < HANG*YEOL - 1; j++)
		{
			if (temparry[j] < temparry[j + 1])
			{
				temp = temparry[j];
				temparry[j] = temparry[j + 1];
				temparry[j + 1] = temp;
			}
		}
	}

	k = 0;

	for (i = 0; i < HANG; i++)
	{
		for (j = 0; j < YEOL; j++)
		{
			_array[i][j] = temparry[k];
			k++;
		}
	}


	for (i = 0; i < HANG; i++)
	{
		for (j = 0; j < YEOL; j++)
		{
			printf_s("%3d ", _array[i][j]);


		}
		printf_s(" \n");
	}


}

void downscale(int _array[HANG][YEOL])
{
	int temparry[20];
	int k = 0;

	int temp, i, j;
	for (i = 0; i < HANG; i++)
	{
		for (j = 0; j < YEOL; j++)
		{
			temparry[k] = _array[i][j];
			k++;

		}
		printf_s(" \n");
	}

	for (i = 0; i < HANG*YEOL - 1; i++)
	{
		for (j = 0; j < HANG*YEOL - 1; j++)
		{
			if (temparry[j] > temparry[j + 1])
			{
				temp = temparry[j];
				temparry[j] = temparry[j + 1];
				temparry[j + 1] = temp;
			}
		}
	}

	k = 0;

	for (i = 0; i < HANG; i++)
	{
		for (j = 0; j < YEOL; j++)
		{
			_array[i][j] = temparry[k];
			k++;
		}
	}


	for (i = 0; i < HANG; i++)
	{
		for (j = 0; j < YEOL; j++)
		{
			printf_s("%3d ", _array[i][j]);


		}
		printf_s(" \n");
	}


}

void triple(int _array[HANG][YEOL])

{
	for (int i = 0; i < HANG; i++)
	{
		for (int j = 0; j < YEOL; j++)
		{
			if (_array[i][j] % 3 == 0)
				printf_s("%3d", _array[i][j]);
			else
			{
				_array[i][j] = 0;
				printf_s("%3d", _array[i][j]);
			}

		}
		printf_s("\n");
	}

}

void seven(int _array[HANG][YEOL])
{

	for (int i = 0; i < HANG; i++)
	{
		for (int j = 0; j < YEOL; j++)
		{
			if (_array[i][j] % 7 == 0)
				printf_s("%3d", _array[i][j]);
			else
			{
				_array[i][j] = 0;
				printf_s("%3d", _array[i][j]);
			}

		}
		printf_s("\n");
	}
}

void retry(int _array[HANG][YEOL])
{

	int j, i, a;

	printf_s("  �ִ� ���ڸ� �Է��ϼ���");
	scanf_s("%d", &a);
	if (a < 20)
	{
		printf_s("20 ����ū ���� �Է��ϼ���");
	}

	srand((unsigned int)time(NULL));
	makeArray(hang, a);
	

	for (i = 0; i < HANG; i++)
	{
		for (j = 0; j < YEOL; j++)
		{
			printf_s("%3d ", hang[i][j]);
		}
		printf_s(" \n");
	}
}

void plusfive(int _array[HANG][YEOL])
{
	for (int i = 0; i < HANG; i++)
	{
		for (int j = 0; j < YEOL; j++)
		{
			if (i % 2 == 0)
				_array[i][j] = _array[i][j] + 5;
		}
	}

	for (int i = 0; i < HANG; i++)
	{
		for (int j = 0; j < YEOL; j++)
		{
			printf_s("%3d ", hang[i][j]);
		}
		printf_s(" \n");
	}
}

void three(int _array[HANG][YEOL])
{
	{
		for (int i = 0; i < HANG; i++)
		{
			for (int j = 0; j < YEOL; j++)
			{
				if (j % 2 == 1)
					_array[i][j] = _array[i][j] - 7;
			}
		}

		for (int i = 0; i < HANG; i++)
		{
			for (int j = 0; j < YEOL; j++)
			{
				printf_s("%3d ", hang[i][j]);
			}
			printf_s(" \n");
		}
	}
}

void rearrange(int _array[HANG][YEOL], int length)
{
	int temparry[20];
	int k = 0;
	int temp, i, j;
	for (i = 0; i < HANG; i++)
	{
		for (j = 0; j < YEOL; j++)
		{
			temparry[k] = _array[i][j];
			k++;
		}
	}
	srand(time(NULL));
	
	for (i = length - 1; i >= 0; i--)
	{
		k = rand() % length;
		temp = temparry[i];
		temparry[i] = temparry[k];
		temparry[k] = temp;
	}
	k = 0;

	for (i = 0; i < HANG; i++)
	{
		for (j = 0; j < YEOL; j++)
		{
			_array[i][j] = temparry[k];
			k++;
		}
	}
	for (i = 0; i < HANG; i++)
	{
		for (j = 0; j < YEOL; j++)
		{
			printf_s("%3d ", hang[i][j]);
		}
		printf_s(" \n");
	}
	printf_s(" \n");

}

void makeArray(int _array[HANG][YEOL], int number)
{
	int i = 0;
	int j = 0;
	int random_number = 0;

	while (1)
	{
		random_number = (rand() % number) + 1;
		if (checkoverlap(random_number, _array) == false)
		{
			_array[i][j] = random_number;

			j++;

			if (i == HANG && j == YEOL)
				return;

			if (j == YEOL + 1)
			{
				i++;
				j = 0;
			}
		}
	}

	for (int i = 0; i < HANG; i++)
	{
		for (int j = 0; j < YEOL; j++)
		{
			printf_s("%3d ", _array[i][j]);
		}
		printf_s(" \n");
	}
}