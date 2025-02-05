#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <atlimage.h>

#pragma comment(lib, "msimg32.lib")

HINSTANCE g_hInst;
LPCTSTR lpszClass = "WinDow Class Name";
LPCTSTR lpszWindowName = "windows program 5-4";

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM IParam);

CImage g_Background;
CImage g_Move;
CImage g_Click;

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
	switch (iMessage)
	{
	case WM_CREATE:
		g_Background.Load(TEXT("./sprite/background.png"));
		g_Move.Load(TEXT("./sprite/move.png"));
		break;
	case WM_TIMER:
		switch (wParam)
		{
			break;
		}
		InvalidateRect(hWnd, NULL, TRUE);
		break;
	case WM_CHAR:
		break;
	case  WM_LBUTTONDOWN: //마우스 입력
		break;
	case  WM_LBUTTONUP: //마우스 입력
		break;
	case WM_COMMAND:
		break;
	case WM_PAINT:
		hDC = BeginPaint(hWnd, &ps);
		g_Background.Draw(hDC, 0, 0, 1200, 800);
		g_Move.Draw(hDC, 600, 400, 135, 150,0,0,135,150);  // 
	

		EndPaint(hWnd, &ps);
		break;

	case WM_DESTROY:

		PostQuitMessage(0);
		return 0;


	}

	return(DefWindowProc(hWnd, iMessage, wParam, IParam));
}