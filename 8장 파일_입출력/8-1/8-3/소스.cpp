#include <windows.h> // 윈도우 헤더 파일
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#pragma warning(disable : 4996)

HINSTANCE g_hInst;

LPCTSTR lpszClass = "Window Class Name";

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage,

	WPARAM wParam, LPARAM lParam);
int x = 1200, y = 800;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,

	LPSTR lpszCmdParam, int nCmdShow)

{

	HWND hWnd;

	MSG Message;

	WNDCLASSEX WndClass;

	g_hInst = hInstance;

	WndClass.cbSize = sizeof(WndClass);

	WndClass.style = CS_HREDRAW | CS_VREDRAW;

	WndClass.lpfnWndProc = (WNDPROC)WndProc;

	WndClass.cbClsExtra = 0;

	WndClass.cbWndExtra = 0;

	WndClass.hInstance = hInstance;

	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);

	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);

	WndClass.hbrBackground =

		(HBRUSH)GetStockObject(WHITE_BRUSH);

	WndClass.lpszMenuName = NULL;

	WndClass.lpszClassName = lpszClass;

	WndClass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	RegisterClassEx(&WndClass);

	hWnd = CreateWindow

	(lpszClass, "windows program 1 - 1",

		WS_OVERLAPPEDWINDOW,

		0, 0, x + 20, y + 50,

		NULL, (HMENU)NULL,

		hInstance, NULL);

	ShowWindow(hWnd, nCmdShow);

	UpdateWindow(hWnd);

	while (GetMessage(&Message, 0, 0, 0)) {

		TranslateMessage(&Message);

		DispatchMessage(&Message);

	}

	return Message.wParam;

}
typedef struct XYPos
{
	int x;
	int y;
	int h;
	int j;
	int pos;
	int Swithch;
	POINT point[3];
}XYPos;
LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM

	wParam, LPARAM lParam)

{

	PAINTSTRUCT ps;

	HDC hDC;
	HBRUSH hBrush1, hBrush2, hBrush3, hBrush4, oldBrush;
	HPEN hPen1, hPen2, oldPen;
	char temp[80];
	static XYPos XYpos[5] = {};


	static int Wide = 40, Line = 40;
	static int m, n;
	static int Choice = 0;
	static int random1 = 255;
	static int random2 = 255;
	static int h = 0, j = 0;
	static int count = 0;
	FILE *fw;
	FILE *fr;
	static int switch_on1 = 0, switch_on2 = 0, switch_on3 = 0, switch_on4 = 0, switch_on5 = 0;
	hBrush1 = CreateSolidBrush(RGB(0, 255, 0)); // GDI: 브러시 만들기
	hBrush2 = CreateSolidBrush(RGB(0, 0, 255)); // GDI: 브러시 만들기
	hBrush4 = CreateSolidBrush(RGB(0, 150, 150));
	hBrush3 = CreateSolidBrush(RGB(255, 0, 0));
	hPen1 = CreatePen(PS_SOLID, 3, RGB(255, 0, 0));
	hPen2 = CreatePen(PS_SOLID, 3, RGB(0, 0, 0));
	switch (iMessage)
	{
	case WM_CREATE:

	case WM_CHAR:
		if (wParam == 's')
		{
			Wide = 30;
			Line = 30;
		}
		else if (wParam == 'm')
		{
			Wide = 40;
			Line = 40;
		}
		else if (wParam == 'l')
		{
			Wide = 50;
			Line = 50;
		}
		else if (wParam == 'e' || wParam == 'E')
		{
			if (switch_on1 == 0)//1번
			{
				XYpos[0].x = rand() % Wide;
				XYpos[0].y = rand() % Line;

				XYpos[0].pos = 1;
				switch_on1 = 1;
			}
			else if (switch_on1 != 0 && switch_on2 == 0)//2번
			{
				XYpos[1].x = rand() % Wide;
				XYpos[1].y = rand() % Line;

				XYpos[1].pos = 1;
				switch_on2 = 1;
			}
			else if (switch_on1 != 0 && switch_on2 != 0 && switch_on3 == 0)//3번
			{
				XYpos[2].x = rand() % Wide;
				XYpos[2].y = rand() % Line;
				XYpos[2].pos = 1;
				switch_on3 = 1;
			}
			else if (switch_on1 != 0 && switch_on2 != 0 && switch_on3 != 0 && switch_on4 == 0)//4번
			{
				XYpos[3].x = rand() % Wide;
				XYpos[3].y = rand() % Line;

				XYpos[3].pos = 1;
				switch_on4 = 1;
			}
			else if (switch_on1 != 0 && switch_on2 != 0 && switch_on3 != 0 && switch_on4 != 0 && switch_on5 == 0)//5번
			{
				XYpos[4].x = rand() % Wide;
				XYpos[4].y = rand() % Line;

				XYpos[4].pos = 1;
				switch_on5 = 1;
			}
			else if (switch_on1 != 0 && switch_on2 != 0 && switch_on3 != 0 && switch_on4 != 0 && switch_on5 != 0)//다차면 다시 1번
			{
				switch_on1 = 0, switch_on2 = 0, switch_on3 = 0, switch_on4 = 0, switch_on5 = 0;
				for (int i = 0; i < 5; i++) {
					XYpos[i].h = 0;
					XYpos[i].j = 0;
				}
				XYpos[0].x = rand() % Wide;
				XYpos[0].y = rand() % Line;

				XYpos[0].pos = 1;
				switch_on1 = 0;
			}
		}
		else if (wParam == 'r' || wParam == 'R')
		{
			if (switch_on1 == 0)//1번
			{
				XYpos[0].x = rand() % Wide;
				XYpos[0].y = rand() % Line;

				XYpos[0].pos = 2;
				switch_on1 = 1;
			}
			else if (switch_on1 != 0 && switch_on2 == 0)//2번
			{
				XYpos[1].x = rand() % Wide;
				XYpos[1].y = rand() % Line;

				XYpos[1].pos = 2;
				switch_on2 = 1;
			}
			else if (switch_on1 != 0 && switch_on2 != 0 && switch_on3 == 0)//3번
			{
				XYpos[2].x = rand() % Wide;
				XYpos[2].y = rand() % Line;

				XYpos[2].pos = 2;
				switch_on3 = 1;
			}
			else if (switch_on1 != 0 && switch_on2 != 0 && switch_on3 != 0 && switch_on4 == 0)//4번
			{
				XYpos[3].x = rand() % Wide;
				XYpos[3].y = rand() % Line;

				XYpos[3].pos = 2;
				switch_on4 = 1;
			}
			else if (switch_on1 != 0 && switch_on2 != 0 && switch_on3 != 0 && switch_on4 != 0 && switch_on5 == 0)//5번
			{
				XYpos[4].x = rand() % Wide;
				XYpos[4].y = rand() % Line;

				XYpos[4].pos = 2;
				switch_on5 = 1;

			}
			else if (switch_on1 != 0 && switch_on2 != 0 && switch_on3 != 0 && switch_on4 != 0 && switch_on5 != 0)//다차면 다시 1번
			{
				switch_on1 = 0, switch_on2 = 0, switch_on3 = 0, switch_on4 = 0, switch_on5 = 0;
				for (int i = 0; i < 5; i++) {
					XYpos[i].h = 0;
					XYpos[i].j = 0;
				}
				XYpos[0].x = rand() % Wide;
				XYpos[0].y = rand() % Line;

				XYpos[0].pos = 2;
				switch_on1 = 1;
			}

		}
		else if (wParam == 't' || wParam == 'T')
		{
			if (switch_on1 == 0)//1번
			{
				XYpos[0].x = rand() % Wide;
				XYpos[0].y = rand() % Line;

				XYpos[0].pos = 3;
				switch_on1 = 1;
			}
			else if (switch_on1 != 0 && switch_on2 == 0)//2번
			{
				XYpos[1].x = rand() % Wide;
				XYpos[1].y = rand() % Line;

				XYpos[1].pos = 3;
				switch_on2 = 1;
			}
			else if (switch_on1 != 0 && switch_on2 != 0 && switch_on3 == 0)//3번
			{
				XYpos[2].x = rand() % Wide;
				XYpos[2].y = rand() % Line;

				XYpos[2].pos = 3;
				switch_on3 = 1;
			}
			else if (switch_on1 != 0 && switch_on2 != 0 && switch_on3 != 0 && switch_on4 == 0)//4번
			{
				XYpos[3].x = rand() % Wide;
				XYpos[3].y = rand() % Line;

				XYpos[3].pos = 3;
				switch_on4 = 1;
			}
			else if (switch_on1 != 0 && switch_on2 != 0 && switch_on3 != 0 && switch_on4 != 0 && switch_on5 == 0)//5번
			{
				XYpos[4].x = rand() % Wide;
				XYpos[4].y = rand() % Line;

				XYpos[4].pos = 3;
				switch_on5 = 1;
			}
			else if (switch_on1 != 0 && switch_on2 != 0 && switch_on3 != 0 && switch_on4 != 0 && switch_on5 != 0)//다차면 다시 1번
			{
				switch_on1 = 0, switch_on2 = 0, switch_on3 = 0, switch_on4 = 0, switch_on5 = 0;
				for (int i = 0; i < 5; i++) {
					XYpos[i].h = 0;
					XYpos[i].j = 0;
				}
				XYpos[0].x = rand() % Wide;
				XYpos[0].y = rand() % Line;
				XYpos[0].pos = 3;
				switch_on1 = 1;
			}

		}
		else if (wParam == '1')
		{
			XYpos[0].Swithch = 1;
			Choice = 1;

		}
		else if (wParam == '2')
		{
			XYpos[1].Swithch = 2;
			Choice = 2;

		}
		else if (wParam == '3')
		{
			XYpos[2].Swithch = 3;
			Choice = 3;

		}
		else if (wParam == '4')
		{
			XYpos[3].Swithch = 4;
			Choice = 4;

		}
		else if (wParam == '5')
		{

			XYpos[4].Swithch = 5;
			Choice = 5;
		}
		else if (wParam == 'a')//DELETE
		{
			for (int i = 0; i < 5; i++)
			{
				if (Choice == i + 1)
				{
					XYpos[i] = { 0 };

				}
			}
		}
		else if (wParam == '+')
		{
			for (int i = 0; i < 5; i++)
			{
				if (Choice == i + 1)
				{

					XYpos[i].h += 1;
					XYpos[i].j += 1;
				}
			}
		}
		else if (wParam == '-')
		{
			for (int i = 0; i < 5; i++)
			{
				if (Choice == i + 1)
				{

					XYpos[i].h -= 1;
					XYpos[i].j -= 1;
				}
			}
		}
		else if (wParam == 'q' || wParam == 'Q')
		{
			PostQuitMessage(0);
		}
		InvalidateRect(hWnd, NULL, TRUE);
		break;
	case WM_KEYDOWN:
		if (wParam == VK_LEFT)
		{
			for (int i = 0; i < 5; i++)
			{
				if (Choice == i + 1)
				{
					if (XYpos[i].x == 0)
					{
						XYpos[i].x = 0;
					}
					else
					{
						XYpos[i].x -= 1;
					}
				}
			}
		}
		else if (wParam == VK_RIGHT)
		{

			for (int i = 0; i < 5; i++)
			{
				if (Choice == i + 1)
				{
					if (XYpos[i].x == Wide)
					{
						XYpos[i].x = Wide;
					}
					else
					{
						XYpos[i].x += 1;
					}
				}
			}
		}
		else if (wParam == VK_UP)
		{

			for (int i = 0; i < 5; i++)
			{
				if (Choice == i + 1)
				{
					if (XYpos[i].y == 0)
					{
						XYpos[i].y = 0;
					}
					else
					{
						XYpos[i].y -= 1;
					}
				}
			}
		}
		else if (wParam == VK_DOWN)
		{

			for (int i = 0; i < 5; i++)
			{
				if (Choice == i + 1)
				{
					if (XYpos[i].y == Line)
					{
						XYpos[i].y = Line;
					}
					else
					{
						XYpos[i].y += 1;
					}
				}
			}
		}

		else if (wParam == VK_F1)
		{
			fw = fopen("save.txt", "wt");
			for (int i = 0; i < 5; i++)
			{
				fprintf(fw, " %d %d %d %d %d %d ", XYpos[i].h, XYpos[i].j, XYpos[i].pos,  XYpos[i].Swithch, XYpos[i].x, XYpos[i].y);

			}

			// 원 사각 삼각

			fclose(fw);
			break;
		}
		else if (wParam == VK_F2)
		{
			fr = fopen("save.txt", "rt");
			for (int i = 0; i < 5; i++)
			{
				fscanf(fr, " %d %d %d %d %d %d ", &XYpos[i].h, &XYpos[i].j,  &XYpos[i].pos, &XYpos[i].Swithch, &XYpos[i].x, &XYpos[i].y);

			}

			// 원 사각 삼각
			fclose(fr);
			InvalidateRect(hWnd, NULL, TRUE);
			break;
		}

		InvalidateRect(hWnd, NULL, TRUE);
		break;
		/*case WM_KEYUP:
			if (wParam == VK_LEFT)

			else if (wParam == VK_RIGHT)

			else if (wParam == VK_DOWN)

			else if (wParam == VK_UP)

				ReleaseDC(hWnd, hDC);
			}*/

	case WM_PAINT:

		hDC = BeginPaint(hWnd, &ps);
		m = x / Wide;
		n = y / Line;
		for (int j = 0; j < Line; j++) {
			for (int i = 0; i < Wide; i++) {
				Rectangle(hDC, i *m, j * n, i * m + m, j * n + n); //가로100 세로 70 칸 100개
			}
		}
		{
			for (int i = 0; i < 5; i++)
			{
				XYpos[i].point[0] = { ((XYpos[i].x*m + m) + XYpos[i].x * m) / 2, XYpos[i].y*n };
				XYpos[i].point[1] = { XYpos[i].x*m + XYpos[i].h, XYpos[i].y*n + n + XYpos[i].j };
				XYpos[i].point[2] = { XYpos[i].x*m + m + XYpos[i].h,XYpos[i].y*n + n };
			}

			for (int i = 0; i < 5; i++)
			{
				oldPen = (HPEN)SelectObject(hDC, hPen2);
				if (XYpos[i].pos == 1)
				{
					if (Choice == XYpos[i].Swithch&& XYpos[i].Swithch != 0)
					{
						oldPen = (HPEN)SelectObject(hDC, hPen1);
						oldBrush = (HBRUSH)SelectObject(hDC, hBrush2); // 새로운 브러시 선택하기
						Ellipse(hDC, XYpos[i].x  *m, XYpos[i].y  * n, XYpos[i].x  * m + m + XYpos[i].h, XYpos[i].y  * n + n + XYpos[i].j); // 선택핚 브러시로 도형 그리기
						SelectObject(hDC, oldBrush);
					}
					else
					{

						oldBrush = (HBRUSH)SelectObject(hDC, hBrush2); // 새로운 브러시 선택하기
						Ellipse(hDC, XYpos[i].x  *m, XYpos[i].y  * n, XYpos[i].x  * m + m + XYpos[i].h, XYpos[i].y  * n + n + XYpos[i].j); // 선택핚 브러시로 도형 그리기
						SelectObject(hDC, oldBrush);
					}
				}
				else if (XYpos[i].pos == 2)
				{
					if (Choice == XYpos[i].Swithch&& XYpos[i].Swithch != 0)
					{
						oldPen = (HPEN)SelectObject(hDC, hPen1);
						oldBrush = (HBRUSH)SelectObject(hDC, hBrush1); // 새로운 브러시 선택하기
						Rectangle(hDC, XYpos[i].x * m, XYpos[i].y * n, XYpos[i].x *m + m + XYpos[i].h, XYpos[i].y * n + n + XYpos[i].j);
						SelectObject(hDC, oldBrush);
					}
					else
					{
						oldBrush = (HBRUSH)SelectObject(hDC, hBrush1); // 새로운 브러시 선택하기
						Rectangle(hDC, XYpos[i].x * m, XYpos[i].y * n, XYpos[i].x *m + m + XYpos[i].h, XYpos[i].y * n + n + XYpos[i].j);
						SelectObject(hDC, oldBrush);
					}
				}

				else if (XYpos[i].pos == 3)
				{
					if (Choice == XYpos[i].Swithch&& XYpos[i].Swithch != 0)
					{
						oldPen = (HPEN)SelectObject(hDC, hPen1);
						oldBrush = (HBRUSH)SelectObject(hDC, hBrush4); // 새로운 브러시 선택하기
						Polygon(hDC, XYpos[i].point, 3);// 선택핚 브러시로 도형 그리기
						SelectObject(hDC, oldBrush);
					}
					else
					{
						oldBrush = (HBRUSH)SelectObject(hDC, hBrush4); // 새로운 브러시 선택하기
						Polygon(hDC, XYpos[i].point, 3);// 선택핚 브러시로 도형 그리기
						SelectObject(hDC, oldBrush);
					}
				}

			}


		}
		DeleteObject(hBrush1);
		DeleteObject(hBrush2);
		DeleteObject(hBrush4);
		EndPaint(hWnd, &ps);

		break;

	case WM_DESTROY:
		HideCaret(hWnd);
		DestroyCaret();
		PostQuitMessage(0);

		return 0;

	}

	return(DefWindowProc(hWnd, iMessage, wParam, lParam));

}