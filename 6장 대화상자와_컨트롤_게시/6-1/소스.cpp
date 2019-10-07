#include<Windows.h>
#include<stdio.h>
#include<stdlib.h>
#include <time.h>
#include <string.h>
#include "resource.h"
#define RIGHTDOWN 1
#define RIGHTUP 2
#define LEFTUP 3
#define LEFTDOWN 4
HINSTANCE g_hInst;
LPCTSTR lpszClass = "WinDow Class Name";
LPCTSTR lpszWindowName = "windows program 1-2";
struct CIRCLE {
	int left;
	int right;
	int top;
	int bottom;
	int r;
	int g;
	int b;
	int shape;
	int speed;
	int dir;
	int dir2;
	HBRUSH hBrush;
		HBRUSH oldBrush;
	POINT point[3];
	void init()
	{
		 left=50;
		 right=90;
		 top=50;
		 bottom=90;
		 r=200;
		 g=200;
		 b=200;
		 shape=2;
		 speed=40;
		  dir  = LEFTUP;
		  dir2 = LEFTUP;
	}
	void draw(HWND hwnd, HDC hdc)
	{
		if (shape == 1)
		{
			hBrush = CreateSolidBrush(RGB(r, g, b));
			oldBrush = (HBRUSH)SelectObject(hdc, hBrush);
			Rectangle(hdc, left, top, right, bottom);
			DeleteObject(hBrush);
		}
		if (shape == 2)
		{
			hBrush = CreateSolidBrush(RGB(r, g, b));
			oldBrush = (HBRUSH)SelectObject(hdc, hBrush);
			Ellipse(hdc, left, top, right, bottom);
			DeleteObject(hBrush);

		}
		if (shape == 3)
		{
			hBrush = CreateSolidBrush(RGB(r, g, b));
			oldBrush = (HBRUSH)SelectObject(hdc, hBrush);
			point[0] = { left,top };
			point[1] = { right,top };
			point[2] = { (left + right) / 2 ,(bottom) };
			Polygon(hdc, point, 3);
			DeleteObject(hBrush);
		}
	
	}
	void update()
	{


		if (right > 600 && dir2 == RIGHTDOWN) //오른쪽 벽 충돌체크1

		{
			dir = LEFTUP;
			dir2 = LEFTUP;

		}
		else if (right > 600 && dir2 == RIGHTUP)  //오른쪽 벽 충돌체크2
		{
			dir = LEFTDOWN;
			dir2 = LEFTDOWN;
		}
		else if (left < 0 && dir2 == LEFTUP) // 왼쪽 벽 충돌체크 1
		{
			dir = RIGHTDOWN;
			dir2 = RIGHTDOWN;

		}
		else if (left < 0 && dir2 == LEFTDOWN) // 왼쪽 벽 충돌체크 2
		{
			dir = RIGHTUP;
			dir2 = RIGHTUP;
		}
		else if (top < 0 && dir2 == LEFTDOWN)
		{
			dir = LEFTUP;
			dir2 = LEFTUP;
		}
		else if (top < 0 && dir2 == RIGHTUP)
		{
			dir = RIGHTDOWN;
			dir2 = RIGHTDOWN;
		}
		else if (bottom > 600 && dir2 == LEFTUP)
		{
			dir = LEFTDOWN;
			dir2 = LEFTDOWN;
		}
		else if (bottom > 600 && dir2 == RIGHTDOWN)
		{
			dir = RIGHTUP;
			dir2 = RIGHTUP;
		}
		switch (dir) // 방향 과 속도 
		{
		case RIGHTDOWN:
			left += speed;
			top += speed;
			right += speed;
			bottom += speed;
			break;
		case RIGHTUP:
			left += speed;
			top -= speed;
			right += speed;
			bottom -= speed;

			break;
		case LEFTUP:
			left -= speed;
			top += speed;
			right -= speed;
			bottom += speed;

			break;
		case LEFTDOWN:
			left -= speed;
			top -= speed;
			right -= speed;
			bottom -= speed;

			break;
		}
	}	void update2()
	{


		if (right > 400 && dir2 == RIGHTDOWN) //오른쪽 벽 충돌체크1

		{
			dir = LEFTUP;
			dir2 = LEFTUP;

		}
		else if (right > 400 && dir2 == RIGHTUP)  //오른쪽 벽 충돌체크2
		{
			dir = LEFTDOWN;
			dir2 = LEFTDOWN;
		}
		else if (left < 0 && dir2 == LEFTUP) // 왼쪽 벽 충돌체크 1
		{
			dir = RIGHTDOWN;
			dir2 = RIGHTDOWN;

		}
		else if (left < 0 && dir2 == LEFTDOWN) // 왼쪽 벽 충돌체크 2
		{
			dir = RIGHTUP;
			dir2 = RIGHTUP;
		}
		else if (top < 0 && dir2 == LEFTDOWN)
		{
			dir = LEFTUP;
			dir2 = LEFTUP;
		}
		else if (top < 0 && dir2 == RIGHTUP)
		{
			dir = RIGHTDOWN;
			dir2 = RIGHTDOWN;
		}
		else if (bottom > 400 && dir2 == LEFTUP)
		{
			dir = LEFTDOWN;
			dir2 = LEFTDOWN;
		}
		else if (bottom > 400 && dir2 == RIGHTDOWN)
		{
			dir = RIGHTUP;
			dir2 = RIGHTUP;
		}
		switch (dir) // 방향 과 속도 
		{
		case RIGHTDOWN:
			left += speed;
			top += speed;
			right += speed;
			bottom += speed;
			break;
		case RIGHTUP:
			left += speed;
			top -= speed;
			right += speed;
			bottom -= speed;

			break;
		case LEFTUP:
			left -= speed;
			top += speed;
			right -= speed;
			bottom += speed;

			break;
		case LEFTDOWN:
			left -= speed;
			top -= speed;
			right -= speed;
			bottom -= speed;

			break;
		}
	}

};
CIRCLE g_circle;
CIRCLE g_circle2;

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM IParam);
BOOL CALLBACK Dlg6_1Proc(HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam);


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

	RegisterClassEx(&WndClass);

	hWnd = CreateWindow
	(lpszClass, lpszWindowName, WS_SYSMENU | WS_THICKFRAME | WS_MAXIMIZEBOX | WS_MINIMIZEBOX | WS_HSCROLL | WS_VSCROLL, 100, 50, 650, 650, NULL, (HMENU)NULL, hlnsatance, NULL);

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

	HDC hdc, memdc;
	static RECT crt; // 직사각형모양 범위 선언
	PAINTSTRUCT ps;

	switch (iMessage)
	{
	case WM_CREATE:

		g_circle.init();
		SetTimer(hWnd, 0, 150, NULL);
	
		break;
	case WM_TIMER:
	{	hdc = GetDC(hWnd);
	g_circle.update();
	InvalidateRgn(hWnd, NULL, true);
	ReleaseDC(hWnd, hdc);
	}
	break;
	case WM_CHAR:
		break;
	case  WM_LBUTTONDOWN: //마우스 입력
		break;
	case  WM_LBUTTONUP: //마우스 입력
		break;

	case WM_INITDIALOG:
		break;
	case WM_COMMAND:
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		memdc = CreateCompatibleDC(hdc);
		Rectangle(hdc, 0, 0, 500, 500);
		g_circle.draw(hWnd, hdc);

		BitBlt(hdc, 0, 0, crt.right, crt.bottom, memdc, 0, 0, SRCCOPY);
		
		DeleteDC(memdc);
		EndPaint(hWnd, &ps);
		break;
	case WM_KEYDOWN:
		// 아무 키나 누르면 대화상자를 띄운다.
		DialogBox(g_hInst, MAKEINTRESOURCE(IDD_DIALOG1), hWnd, Dlg6_1Proc);
		break;

	case WM_DESTROY:

		PostQuitMessage(0);
		return 0;


	}

	return(DefWindowProc(hWnd, iMessage, wParam, IParam));
}
BOOL CALLBACK Dlg6_1Proc(HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	HDC hdc, memdc;
	static RECT crt; // 직사각형모양 범위 선언
	PAINTSTRUCT ps;

	switch (iMsg) {
	case WM_INITDIALOG:
		CheckRadioButton(hDlg, ID_COLOR_1, ID_COLOR_2, ID_COLOR_3);
		CheckRadioButton(hDlg, ID_RECTANGLE, ID_CIRCLE, ID_SQURE);
		g_circle.init();
		g_circle2.init();
		SetTimer(hDlg, 0, 150, NULL);
		break;
	case WM_PAINT:
		hdc = BeginPaint(hDlg, &ps);
		memdc = CreateCompatibleDC(hdc);

		
		g_circle2.draw(hDlg, hdc);
		BitBlt(hdc, 0, 0, crt.right, crt.bottom, memdc, 0, 0, SRCCOPY);

		DeleteDC(memdc);
		EndPaint(hDlg, &ps);

		break;
	case WM_TIMER:
	{
		hdc = GetDC(hDlg);
		g_circle.update();
		g_circle2.update2();

		InvalidateRgn(hDlg, NULL, true);
		ReleaseDC(hDlg, hdc);
	}
	break;

	case WM_COMMAND:
		switch (LOWORD(wParam)) {

		case ID_MOM_EXIT:
			PostQuitMessage(0);
			break;
		case ID_MOM_FREE:
			g_circle.speed = 30;
			break;
		case ID_MOM_STOP:
			g_circle.speed = 0;
			break;
		case ID_DIA_EXIT:
			EndDialog(hDlg, 0);
			break;
		case ID_DIA_FREE:
			g_circle2.speed = 30;
			break;
		case ID_DIA_STOP:
			g_circle2.speed = 0;
			break;
		case ID_CIRCLE:
			g_circle.shape = 2;
			g_circle2.shape = 2;
			break;
		case ID_SQURE:
			g_circle.shape = 3;
			g_circle2.shape = 3;
			break;
		case ID_RECTANGLE:
			g_circle.shape = 1;
			g_circle2.shape = 1;

			break;

		case ID_COLOR_1:
			g_circle.r = 100;
			g_circle.g = 0;
			g_circle.b = 0;

			g_circle2.r = 100;
			g_circle2.g = 0;
			g_circle2.b = 0;
			break;
		case ID_COLOR_2:
			g_circle.r = 0;
			g_circle.g = 100;
			g_circle.b = 0;

			g_circle2.r = 0;
			g_circle2.g = 100;
			g_circle2.b = 0;

			break;
		case ID_COLOR_3:
			g_circle.r = 0;
			g_circle.g = 0;
			g_circle.b = 100;

			g_circle2.r = 0;
			g_circle2.g = 0;
			g_circle2.b = 100;

			break;
		}
		break;
	}
	return 0;
}
