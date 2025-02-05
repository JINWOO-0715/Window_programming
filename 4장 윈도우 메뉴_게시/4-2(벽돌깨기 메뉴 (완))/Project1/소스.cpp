#include<Windows.h>
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include <math.h>
#include "resource.h"

#define RIGHTDOWN 1
#define RIGHTUP 2
#define LEFTUP 3
#define LEFTDOWN 4
HINSTANCE g_hInst;
LPCTSTR lpszClass = "WinDow Class Name";
LPCTSTR lpszWindowName = "windows program 1-2";

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM IParam);

struct Ball {
	int x, y; //원의 x,y좌표
};

struct Brick {
	int xpos, ypos;
	int hitCount; // 공에 맞은 벽돌의 횟수 0 이면 없어짐
	int movecount;
	int removecount;
};
bool InRectangle(int barx, int bary, int moux, int mouy,int barsizex ,int barsizey);
int WINAPI WinMain(HINSTANCE hlnsatance, HINSTANCE hPrevlstance,
	LPSTR lpzsCmdParam, int nCmdShow)

{

	HWND hWnd;
	MSG Message;
	WNDCLASSEX WndClass;
	g_hInst = hlnsatance;

	WndClass.cbSize = sizeof(WndClass);
	WndClass.style = CS_HREDRAW | CS_VREDRAW;
	WndClass.lpfnWndProc = (WNDPROC)WndProc;
	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hInstance = hlnsatance;
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);

	WndClass.lpszClassName = lpszClass;
	WndClass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	WndClass.lpszMenuName = MAKEINTRESOURCE(ID_MENU);
	RegisterClassEx(&WndClass);

	hWnd = CreateWindow
	(lpszClass, lpszWindowName, WS_SYSMENU | WS_THICKFRAME | WS_MAXIMIZEBOX | WS_MINIMIZEBOX | WS_HSCROLL | WS_VSCROLL, 100, 50, 1200, 800, NULL, (HMENU)NULL, hlnsatance, NULL);

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	while (GetMessage(&Message, 0, 0, 0))
	{
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}
	return Message.wParam;
}


LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM IParam)
{
	PAINTSTRUCT ps;
	HDC hDC;
	HPEN hpen, oldpen;
	HBRUSH hBrush, oldBrush;
	static char buf[10];
	static bool goright = true;
	static bool goleft = false;
	static int bricknum = 4;

	static Ball ball;
	static int speed = 2;
	
	static int barx = 20, bary = 600;
	static int brickspeed = 1;
	static bool selection = false;
	static int dir = RIGHTDOWN;
	static int dir2 = RIGHTDOWN;
	static int removecount = 0;
	static int 	removecount2 = 0;
	static int barsizex = 200;
	static int barsizey = 20;
	static int choice = 0;
	static Brick brick[4][10];	srand(unsigned(time));
	static int angle;
	static int mx, my;
	switch (iMessage)
	{
	case WM_CREATE:
	
	

		for (int i = 0; i < bricknum; i++)
		{
			for (int j = 0; j < 10; j++)
			{
				brick[i][j].xpos = j * 100;
				brick[i][j].ypos = i * 50;
				brick[i][j].hitCount = 2;
			}
		}
	
		ball.x = 100;
		ball.y = 500;

		
		break;
	case WM_TIMER:

		for (int i = 0; i < bricknum; i++)
		{
			for (int j = 0; j < 10; j++)
			{
				if (goleft == true && goright == false) // 왼쪽으로 가야할 때
				{
					brick[i][j].xpos -= 2;
				}
				if (goleft == false && goright == true) // 왼쪽으로 가야할 때
				{
					brick[i][j].xpos += 2;
				}
			}
		}


		switch (dir) // 방향 과 속도 
		{
		case RIGHTDOWN:
			ball.x += speed;
			ball.y += speed;
			break;
		case RIGHTUP:
			ball.x += speed;
			ball.y -= speed;
			break;
		case LEFTUP:
			ball.x -= speed;
			ball.y += speed;
			break;
		case LEFTDOWN:
			ball.x -= speed;
			ball.y -= speed;
			break;
		}
		InvalidateRect(hWnd, NULL, TRUE);
		break;
	case WM_CHAR:
	{
		hDC = GetDC(hWnd); // 속도 낮추기 
		if (wParam == '-')
		{
			speed -= 1;
		}
		else if (wParam == '+') // 속도 올리기 
		{
			speed += 1;
		}
		InvalidateRect(hWnd, NULL, TRUE);
		break;
	}
	case  WM_LBUTTONDOWN: //마우스 입력
		mx = LOWORD(IParam);
		my = HIWORD(IParam);
		if (InRectangle(barx, bary, mx, my,barsizex,barsizey))
			selection = true;
		InvalidateRect(hWnd, NULL, TRUE);
		break;
	case WM_LBUTTONUP: // 마우스 입력
		InvalidateRect(hWnd, NULL, TRUE);
		selection = false;
		break;

	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case ID_GAME_START :
			SetTimer(hWnd, 1, 1000 / 60, NULL);
			break;
		case ID_GAME_END:
			PostQuitMessage(0);
			break;
		case ID_SPEED_FAST:
			speed = 8;
			break;
		case ID_SPEED_MEDIUM:
			speed = 5;
			break;
		case ID_SPEED_SLOW:
			speed = 3;
			break;
		case ID_SIZE_L:
			barsizex = 280;
			InvalidateRect(hWnd, NULL, TRUE);
			break;
		case ID_SIZE_M:
			barsizex = 220;
			InvalidateRect(hWnd, NULL, TRUE);
				break;
		case ID_SIZE_S:
			barsizex = 160;
			InvalidateRect(hWnd, NULL, TRUE);		
			break;
		case ID_BALL_CIRCLE:
			choice = 0;
			InvalidateRect(hWnd, NULL, TRUE);
			break;
		case ID_BALL_RECTANGLE:
			choice = 1;
			InvalidateRect(hWnd, NULL, TRUE);
			break;
		case ID_BRICK_2:
			bricknum = 2;
			InvalidateRect(hWnd, NULL, TRUE);
			break;
		case ID_BRICK_3:
			bricknum = 3;
			InvalidateRect(hWnd, NULL, TRUE);
			break;
		case ID_BRICK_4:
			bricknum = 4;
			InvalidateRect(hWnd, NULL, TRUE);
			break;
		}
	case WM_MOUSEMOVE:  // 마우스 움직임
		mx = LOWORD(IParam);
		my = HIWORD(IParam);
		if (selection)
		{
			barx = mx;

			InvalidateRect(hWnd, NULL, TRUE);
		}

	case WM_PAINT:
		hDC = BeginPaint(hWnd, &ps);
		Rectangle(hDC, 0, 0, 1100, 700);


		if ((ball.x >= barx && ball.x <= barx + barsizex) && ball.y + barsizey > bary && dir2 == RIGHTDOWN) //바 충돌체크 1
		{
			dir = RIGHTUP;
			dir2 = RIGHTUP;
		}

		else if (((ball.x >= barx && ball.x <= barx + barsizex) && ball.y + barsizey > bary && dir2 == LEFTUP))//바 충돌체크 2
		{
			dir = LEFTDOWN;
			dir2 = LEFTDOWN;
		}

		else if (ball.x > 1080 && dir2 == RIGHTDOWN) //오른쪽 벽 충돌체크1

		{
			dir = LEFTUP;
			dir2 = LEFTUP;

		}
		else if (ball.x > 1080 && dir2 == RIGHTUP)  //오른쪽 벽 충돌체크2
		{
			dir = LEFTDOWN;
			dir2 = LEFTDOWN;
		}
		else if (ball.x < 0 && dir2 == LEFTUP) // 왼쪽 벽 충돌체크 1
		{
			dir = RIGHTDOWN;
			dir2 = RIGHTDOWN;

		}
		else if (ball.x < 0 && dir2 == LEFTDOWN) // 왼쪽 벽 충돌체크 2
		{
			dir = RIGHTUP;
			dir2 = RIGHTUP;
		}
		else if (ball.y < 0 && dir2 == LEFTDOWN)
		{
			dir = LEFTUP;
			dir2 = LEFTUP;
		}
		else if ((ball.y < 0 && dir2 == RIGHTUP))
		{
			dir = RIGHTDOWN;
			dir2 = RIGHTDOWN;
		}
		for (int j = 0; j < bricknum ; j++)
		{
			for (int i = 0; i < 10; i++)
			{
				if (ball.y - brick[j][i].ypos < 80 && ball.x >= brick[j][i].xpos && ball.x < brick[j][i].xpos + 100 && brick[j][i].hitCount == 2 && dir2 == RIGHTUP)
					// 공과 블록의 충돌체크1
				{
					brick[j][i].hitCount -= 1;
					dir = RIGHTDOWN;
					dir2 = RIGHTDOWN;
					removecount++;



				}
				else if (ball.y - brick[j][i].ypos < 80 && ball.x >= brick[j][i].xpos&&ball.x < brick[j][i].xpos + 100 && brick[j][i].hitCount == 2 && dir2 == LEFTDOWN)
				{// 공과 블록의 충돌체크2
					brick[j][i].hitCount -= 1;
					dir = LEFTUP;
					dir2 = LEFTUP;
					removecount++;

				}
				else if (ball.y - brick[j][i].ypos < 80 && ball.x >= brick[j][i].xpos&&ball.x < brick[j][i].xpos + 100 && brick[j][i].hitCount == 1 && dir2 == RIGHTUP)
				{// 공과 블록의 충돌체크2
					brick[j][i].hitCount -= 1;
					dir = RIGHTDOWN;
					dir2 = RIGHTDOWN;
					removecount--;
					removecount2++;

				}
				else if (ball.y - brick[j][i].ypos < 80 && ball.x >= brick[j][i].xpos&&ball.x < brick[j][i].xpos + 100 && brick[j][i].hitCount == 1 && dir2 == LEFTDOWN)
				{// 공과 블록의 충돌체크2
					brick[j][i].hitCount -= 1;
					dir = LEFTUP;
					dir2 = LEFTUP;
					removecount--;
					removecount2++;

				}

			}
		}
		if (ball.y > 700)
		{
			PostQuitMessage(0);
		}
		
		for (int i = 0; i < bricknum; i++)
		{
			for (int j = 0; j < 10; j++)
			{
				if ((brick[i][j].xpos) > 1000)
				{
					goright = false;
					goleft = true;
				}
				else if ((brick[i][j].xpos) < 0)
				{
					goright = true;
					goleft = false;
				}

				if (brick[i][j].hitCount == 2)
				{
					hBrush = CreateSolidBrush(RGB(255, 0, 255));
					oldBrush = (HBRUSH)SelectObject(hDC, hBrush);
					Rectangle(hDC, brick[i][j].xpos, brick[i][j].ypos, brick[i][j].xpos + 100, brick[i][j].ypos + 50);
					DeleteObject(hBrush);

				}
				else if (brick[i][j].hitCount == 1)
				{
					hBrush = CreateSolidBrush(RGB(255, 0, 0));
					oldBrush = (HBRUSH)SelectObject(hDC, hBrush);
					Rectangle(hDC, brick[i][j].xpos , brick[i][j].ypos + 50, brick[i][j].xpos + 100, brick[i][j].ypos + 100);
					DeleteObject(hBrush);

				}

			}
		}
		wsprintf(buf, "%d %d", removecount, removecount2);
		TextOut(hDC, 400, 400, buf, strlen(buf));
		hBrush = CreateSolidBrush(RGB(0, 0, 255));
		oldBrush = (HBRUSH)SelectObject(hDC, hBrush);
		if (choice ==0)
		{
		Ellipse(hDC, ball.x, ball.y, ball.x + 20, ball.y + 20);
		}
		else
		{
			Rectangle(hDC, ball.x, ball.y, ball.x + 20, ball.y + 20);
		}
		DeleteObject(hBrush);
		hBrush = CreateSolidBrush(RGB(255, 10, 100));
		oldBrush = (HBRUSH)SelectObject(hDC, hBrush);
		Rectangle(hDC, barx, bary, barx + barsizex, bary + barsizey); // 바
		DeleteObject(hBrush);
		EndPaint(hWnd, &ps);

		break;

	case WM_DESTROY:

		PostQuitMessage(0);
		return 0;


	}

	return(DefWindowProc(hWnd, iMessage, wParam, IParam));
}
bool InRectangle(int barx, int bary, int moux, int mouy,int barsizex,int barsizey)
{
	if ((barx <= moux && barx + barsizex >= moux) && (bary <= mouy && bary + barsizey >= mouy))
	{
		return true;
	}
	else
	{
		return false;
	}

}
