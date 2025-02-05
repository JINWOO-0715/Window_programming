#include<Windows.h>
#include<stdio.h>
#include<stdlib.h>
#include <math.h>
#include"resource.h"
#define BSIZE 25
HINSTANCE g_hInst;
LPCTSTR lpszClass = "WinDow Class Name";
LPCTSTR lpszWindowName = "windows program 1-2";
BOOL InCircle(int x, int y, int mx, int my);
float LengthPts(int x1, int y1, int x2, int y2);
LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM IParam);

typedef struct _car1 {

	int x;
	int y;
	int speed;
	bool go;

}_car;
struct Signal
{
	int x1, x2;
	int y1, y2;
	int R, G, B;
	int choice;
};

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
	WndClass.lpszMenuName = NULL;
	WndClass.lpszClassName = lpszClass;
	WndClass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	WndClass.lpszMenuName = MAKEINTRESOURCE(MYMENU);
	RegisterClassEx(&WndClass);

	hWnd = CreateWindow
	(lpszClass, lpszWindowName, WS_SYSMENU | WS_THICKFRAME | WS_MAXIMIZEBOX | WS_MINIMIZEBOX | WS_HSCROLL | WS_VSCROLL, 100, 50, 740, 760, NULL, (HMENU)NULL, hlnsatance, NULL);

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
	static  bool selection = false;

	static _car car[4];
	static Signal sig[3];
	static int mx, my;
	static int i = 0;
	static int timerspeed = 0;
	static int ballx1 = 320;
	static int bally1 = 320;
	static int ballx2 = 350;
	static int bally2 = 350;

	switch (iMessage)
	{
	case WM_CREATE:

		car[0].x = 400;
		car[0].y = 0;
		car[0].speed = 10;
		car[0].go = true;
		car[1].x = 350;
		car[1].y = 700;
		car[1].speed = 10;
		car[1].go = true;
		car[2].x = 700;
		car[2].y = 400;
		car[2].speed = 10;
		car[2].go = true;
		car[3].x = 0;
		car[3].y = 350;
		car[3].speed = 10;
		car[3].go = true;
		sig[0].R = 255;
		sig[0].G = 0;
		sig[0].B = 0;
		sig[0].choice = 0;
		sig[0].x1 = 510;
		sig[0].y1 = 0;
		sig[0].x2 = 560;
		sig[0].y2 = 50;
		sig[1].R = 255;
		sig[1].G = 255;
		sig[1].B = 0;
		sig[1].choice = 0;
		sig[1].x1 = 570;
		sig[1].y1 = 0;
		sig[1].x2 = 620;
		sig[1].y2 = 50;
		sig[2].R = 0;
		sig[2].G = 0;
		sig[2].B = 255;
		sig[2].choice = 0;
		sig[2].x1 = 630;
		sig[2].y1 = 0;
		sig[2].x2 = 680;
		sig[2].y2 = 50;

		break;
	case WM_TIMER:
		switch (wParam)
		{
		case 1:
			if (car[0].go == true)
			{
				car[0].y += car[0].speed;
			}

			if (car[0].y == 280)
			{
				car[0].go = false;
			}

			break;
		case 2:
			if (car[1].go == true)
			{
				car[1].y -= car[1].speed;
			}
			if (car[1].y == 450)
			{
				car[1].go = false;
			}

			break;
		case 3:
			if (car[2].go == true)
			{
				car[2].x -= car[2].speed;
			}
			if (car[2].x == 450)
			{
				car[2].go = false;
			}

			break;
		case 4:
			if (car[3].go == true)
			{
				car[3].x += car[3].speed;
			}

			if (car[3].x == 280)
			{
				car[3].go = false;


			}
			break;
		case 5:
			ballx1 += 5;
			ballx2 += 5;
			bally1 += 5;
			bally2 += 5;
			break;
		case 6:
			ballx1 -= 5;
			ballx2 -= 5;
			bally1 -= 5;
			bally2 -= 5;


			break;


		}

		InvalidateRect(hWnd, NULL, TRUE);
		break;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case ID_GAME_START:

			SetTimer(hWnd, 1, timerspeed + 30, NULL);
			SetTimer(hWnd, 2, timerspeed + 35, NULL);
			SetTimer(hWnd, 3, timerspeed + 85, NULL);
			SetTimer(hWnd, 4, timerspeed + 65, NULL);
			break;
		case ID_GAME_END :
			car[0].go = false;
			car[1].go = false;
			car[2].go = false;
			car[3].go = false;
			break;
		case ID_SPEED_FAST:
			timerspeed -= 10;
			KillTimer(hWnd, 1);
			KillTimer(hWnd, 2);
			KillTimer(hWnd, 3);

			KillTimer(hWnd, 4);

			SetTimer(hWnd, 1, 30 + timerspeed, NULL);
			SetTimer(hWnd, 2, 35 + timerspeed, NULL);
			SetTimer(hWnd, 3, 85 + timerspeed, NULL);
			SetTimer(hWnd, 4, 65 + timerspeed, NULL);
			break;
		case ID_SPEED_SLOW:
			timerspeed += 10;
			KillTimer(hWnd, 1);
			KillTimer(hWnd, 2);
			KillTimer(hWnd, 3);

			KillTimer(hWnd, 4);

			SetTimer(hWnd, 1, 30 + timerspeed, NULL);
			SetTimer(hWnd, 2, 35 + timerspeed, NULL);
			SetTimer(hWnd, 3, 85 + timerspeed, NULL);
			SetTimer(hWnd, 4, 65 + timerspeed, NULL);
	
			break;
		case ID_SIGNAL_R:
			hDC = GetDC(hWnd);
		 // 원 안에 있으면 ‘참’
			car[0].speed = 0;
			car[1].speed = 0;
			car[2].speed = 0;
			car[3].speed = 0;
			SetTimer(hWnd, 5, 55, NULL);
			sig[0].choice = 1;
			sig[1].choice = 0;
			sig[2].choice = 0;
			InvalidateRect(hWnd, NULL, TRUE);
		
		
			
			break;
		case ID_SIGNAL_B:
			car[0].speed = 10;
			car[1].speed = 10;
			car[2].speed = 10;
			car[3].speed = 10;
			sig[0].choice = 0;
			sig[1].choice = 0;
			sig[2].choice = 1;
			InvalidateRect(hWnd, NULL, TRUE);

			break;
		case ID_SIGNAL_Y:
		
			car[0].speed = 0;
			car[1].speed = 0;
			car[2].speed = 0;
			car[3].speed = 0;
			SetTimer(hWnd, 5, 55, NULL);
			sig[0].choice = 0;
			sig[1].choice = 1;
			sig[2].choice = 0;
			InvalidateRect(hWnd, NULL, TRUE);

			break;
		}

		break;
	case WM_CHAR:
		if (wParam == '-')
		{

			timerspeed += 10;
			KillTimer(hWnd, 1);
			KillTimer(hWnd, 2);
			KillTimer(hWnd, 3);

			KillTimer(hWnd, 4);

			SetTimer(hWnd, 1, 30 + timerspeed, NULL);
			SetTimer(hWnd, 2, 35 + timerspeed, NULL);
			SetTimer(hWnd, 3, 85 + timerspeed, NULL);
			SetTimer(hWnd, 4, 65 + timerspeed, NULL);
		}
		else if (wParam == '+') // 속도 올리기 
		{
			timerspeed -= 10;
			KillTimer(hWnd, 1);
			KillTimer(hWnd, 2);
			KillTimer(hWnd, 3);

			KillTimer(hWnd, 4);

			SetTimer(hWnd, 1, 30 + timerspeed, NULL);
			SetTimer(hWnd, 2, 35 + timerspeed, NULL);
			SetTimer(hWnd, 3, 85 + timerspeed, NULL);
			SetTimer(hWnd, 4, 65 + timerspeed, NULL);
		}

		InvalidateRect(hWnd, NULL, TRUE);
		break;
	case  WM_LBUTTONDOWN: { //마우스 입력
		mx = LOWORD(IParam);
		my = HIWORD(IParam);
		if (InCircle(sig[0].x1 + 25, sig[1].y1 + 25, mx, my)) // 원의 중심점, 마우스 좌표 비교
		{
			selection = true; // 원 안에 있으면 ‘참’
			car[0].speed = 0;
			car[1].speed = 0;
			car[2].speed = 0;
			car[3].speed = 0;
			SetTimer(hWnd, 5, 55, NULL);
		}
		else if (InCircle(sig[1].x1 + 25, sig[1].y1 + 25, mx, my))
		{
			selection = true;

		}
		else if (InCircle(sig[2].x1 + 25, sig[1].y1 + 25, mx, my))
		{
			selection = true;
			car[0].speed = 10;
			car[1].speed = 10;
			car[2].speed = 10;
			car[3].speed = 10;
		}

		InvalidateRect(hWnd, NULL, TRUE);

		break;
	}
	case WM_LBUTTONUP: // 마우스 입력
		InvalidateRect(hWnd, NULL, TRUE);
		selection = false;
		break;
	case WM_PAINT: {

		hDC = BeginPaint(hWnd, &ps);
		Rectangle(hDC, 0, 0, 700, 700);
		MoveToEx(hDC, 400, 0, NULL);
		LineTo(hDC, 400, 700);
		MoveToEx(hDC, 450, 0, NULL);
		LineTo(hDC, 450, 700);
		MoveToEx(hDC, 350, 0, NULL);
		LineTo(hDC, 350, 700);
		MoveToEx(hDC, 0, 350, NULL);
		LineTo(hDC, 700, 350);
		MoveToEx(hDC, 0, 400, NULL);
		LineTo(hDC, 700, 400);
		MoveToEx(hDC, 0, 450, NULL);
		LineTo(hDC, 700, 450);
		Rectangle(hDC, 500, 0, 700, 50);

		hBrush = CreateSolidBrush(RGB(0, 0, 255));
		oldBrush = (HBRUSH)SelectObject(hDC, hBrush);
		Ellipse(hDC, ballx1, bally1, ballx2, bally2);
		DeleteObject(oldBrush);

		for (i = 0; i < 3; i++)
		{
			hBrush = CreateSolidBrush(RGB(sig[i].R, sig[i].G, sig[i].B));
			oldBrush = (HBRUSH)SelectObject(hDC, hBrush);
			Ellipse(hDC, sig[i].x1, sig[i].y1, sig[i].x2, sig[i].y2);
			DeleteObject(oldBrush);
			if(sig[i].choice==1){
			hpen = CreatePen(PS_SOLID, 3, RGB(1, 1, 1));
			oldpen = (HPEN)SelectObject(hDC, hpen);
			Ellipse(hDC, sig[i].x1, sig[i].y1, sig[i].x2, sig[i].y2);
			SelectObject(hDC, oldpen);
			DeleteObject(oldpen);
			}
		}


		hBrush = CreateSolidBrush(RGB(255, 255, 0));
		oldBrush = (HBRUSH)SelectObject(hDC, hBrush);
		hpen = CreatePen(PS_SOLID, 0, RGB(1, 1, 1));
		Rectangle(hDC, car[2].x, car[2].y, car[2].x + 70, car[2].y + 20); // 왼오 1번
		Rectangle(hDC, car[3].x, car[3].y, car[3].x + 70, car[3].y + 20);// 왼오 2번
		Rectangle(hDC, car[1].x, car[1].y, car[1].x + 20, car[1].y + 70); //위아래 1번
		Rectangle(hDC, car[0].x, car[0].y, car[0].x + 20, car[0].y + 70); //위아래 2번
		if (ballx1 == 450 && bally2 == 480)
		{
			KillTimer(hWnd, 5);
			SetTimer(hWnd, 6, 20, NULL);

		}
		else if (ballx1 == 320 && bally2 == 350)
		{
			KillTimer(hWnd, 6);

		}


		if (car[0].y > 630)
		{
			Rectangle(hDC, car[0].x, 0, car[0].x + 20, car[0].y - 630);
		}

		if (car[0].y > 700)
		{
			car[0].y = 0;
		}
		if (car[1].y < 110)
		{
			Rectangle(hDC, car[1].x, 0, car[1].x + 20, car[1].y - 630);
		}
		if (car[1].y < -20)
		{
			car[1].y = 700;
		}
		if (car[2].x < 110)
		{
			Rectangle(hDC, 0, car[2].y, car[2].x - 630, car[2].y + 20);
		}
		if (car[2].x < -30)
		{
			car[2].x = 700;
		}
		if (car[3].x > 630)
		{
			Rectangle(hDC, 0, car[3].y, car[3].x - 630, car[3].y + 20);
		}
		if (car[3].x > 700)
		{
			car[3].x = 0;
		}

		if (car[0].go == false && car[1].go == false)
		{

			car[0].go = true;

			car[1].go = true;


		}
		if (car[2].go == false && car[3].go == false)
		{

			car[2].go = true;

			car[3].go = true;


		}


		EndPaint(hWnd, &ps);
		break;
	}
	case WM_DESTROY:

		PostQuitMessage(0);
		return 0;


	}

	return(DefWindowProc(hWnd, iMessage, wParam, IParam));

}
BOOL InCircle(int x, int y, int mx, int my)
{
	if (LengthPts(x, y, mx, my) < BSIZE)
		return true;
	else
		return false;
}
float LengthPts(int x1, int y1, int x2, int y2)
{
	return (sqrt((x2 - x1)*(x2 - x1) + (y2 - y1)*(y2 - y1)));
}