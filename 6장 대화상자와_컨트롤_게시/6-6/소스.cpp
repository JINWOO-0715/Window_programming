#include <Windows.h>
#include <time.h>
#include <math.h>
#include "resource.h"
#pragma comment(lib, "msimg32.lib")

struct Shape {
	int left;
	int top;
	int bottom;
	int right;
	int speed;
	int view;
	int r;
	int g;
	int b;


};
BOOL CALLBACK Dlg6_1Proc(HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam);

#ifdef UNICODE
#pragma comment(linker, "/entry:wWinMainCRTStartup /subsystem:console") 
#else
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console") 
#endif

typedef struct _Point {
	int x;
	int y;

	_Point& operator=(_Point& rhs)
	{
		x = rhs.x;
		y = rhs.y;

		return *this;
	}
} Point;

using namespace std;

#define WINDOW_X 1280
#define WINDOW_Y 720

#define FRAME_X 135
#define FRAME_Y 150

HINSTANCE g_hInstance;
LPCTSTR lpszClass = "Window Class Name";
LPCTSTR lpszWindowName = "Window Program 5-5";

// 함수 선언
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow)
{
	HWND hWnd;
	MSG Message;
	WNDCLASSEX WndClass;
	g_hInstance = hInstance;

	// 윈도우 클래스 구조체 값 설정
	WndClass.cbSize = sizeof(WndClass);
	WndClass.style = CS_HREDRAW | CS_VREDRAW;
	WndClass.lpfnWndProc = (WNDPROC)WndProc;
	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hInstance = hInstance;
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	WndClass.lpszMenuName = NULL;
	WndClass.lpszClassName = lpszClass;
	WndClass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	// 윈도우 클래스 등록
	RegisterClassEx(&WndClass);

	RECT rt = { 0, 0, WINDOW_X, WINDOW_Y };
	AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, false);

	// 윈도우 생성
	hWnd = CreateWindow(lpszClass, lpszWindowName, WS_OVERLAPPEDWINDOW, 50, 50,
		rt.right - rt.left, rt.bottom - rt.top, NULL, (HMENU)NULL, hInstance, NULL);

	// 윈도우 출력
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	// 이벤트 루프 처리
	while (GetMessage(&Message, 0, 0, 0))
	{
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}

	return Message.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	HDC hdc, memdc;
	static RECT crt; // 직사각형모양 범위 선언
	PAINTSTRUCT ps;
	static bool selection;
	static int startX, startY;
	static bool Drag;
	static int endX, endY;
	static int line_x;
	static int line_y;
	static HBITMAP hBitmap, hOldBitmap;
	static int mousex ;
	static int mousey;;
	// 메시지 처리하기
	switch (uMsg)
	{
	case WM_CREATE:
	{

		GetClientRect(hWnd, &crt);
		Drag = false;

		SetTimer(hWnd, 0, 150, NULL);
	}
	break;
	case WM_TIMER:
	{
		InvalidateRgn(hWnd, NULL, false);
	}
	break;
	case WM_PAINT:
	{
		hdc = BeginPaint(hWnd, &ps);

		memdc = CreateCompatibleDC(hdc);
		hBitmap = CreateCompatibleBitmap(hdc, crt.right, crt.bottom);
		hOldBitmap = (HBITMAP)SelectObject(memdc, hBitmap);
		Rectangle(memdc, 0, 0, WINDOW_X, WINDOW_Y);



		BitBlt(hdc, 0, 0, crt.right, crt.bottom, memdc, 0, 0, SRCCOPY);

		DeleteObject(SelectObject(memdc, hOldBitmap));
		DeleteDC(memdc);

		EndPaint(hWnd, &ps);
	}
	break;
	case WM_CHAR:
	{
		switch (wParam)
		{
		case 'j': case 'J':
		{
		}
		break;
		case 'e': case 'E':
		{
		}
		break;
		case 's': case 'S':
		{
		}
		break;
		case 't': case 'T':
		{
		}
		break;
		}
	}
	break;
	case WM_KEYDOWN:
	{
		DialogBox(g_hInstance, MAKEINTRESOURCE(IDD_DIALOG1), hWnd, Dlg6_1Proc);

		switch (wParam)
		{
		case VK_UP:
		{
		}
		break;
		case VK_DOWN:
		{
		}
		break;
		case VK_LEFT:
		{
		}
		break;
		case VK_RIGHT:
		{
		}
		break;
		}
	}
	break;

	case WM_LBUTTONDOWN:
	{
		 mousex = LOWORD(lParam);
		 mousey = HIWORD(lParam);
		line_x = mousex;
		line_y = mousey;
		selection = true;
	}

	break; 
	case WM_MOUSEMOVE:
	{
		if (selection)
		{
			memdc = GetDC(hWnd);
			SetROP2(memdc, R2_NOT); //반전 모드
			MoveToEx(memdc, mousex, mousey, NULL);
			LineTo(memdc, line_x, line_y); //전단계를 다시 그려서 흰색으로 만듬
			line_x = LOWORD(lParam);
			line_y = HIWORD(lParam);
			MoveToEx(memdc, mousex, mousey, NULL);
			LineTo(memdc, line_x, line_y); //새로운 선을 그음
			ReleaseDC(hWnd, memdc);

		}

		break;
	}
	case WM_LBUTTONUP:
	{
		selection = false;
		memdc =GetDC(hWnd);
	     MoveToEx(memdc, mousex, mousey, NULL);
		 LineTo(memdc, line_x, line_y);
		ReleaseDC(hWnd, memdc);
		InvalidateRect(hWnd, NULL, TRUE);
	}
	break;
	
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);

	}

BOOL CALLBACK Dlg6_1Proc(HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam)
{

	switch (iMsg) {
	case WM_INITDIALOG:

		break;

	case WM_COMMAND:
		switch (LOWORD(wParam))
		{

		case ID_EXIT:
			EndDialog(hDlg, 0);
			break;
		case ID_COLOR1:
			break;
		case ID_COLOR2:
			break;
		case ID_COLOR3:
			break;
		case ID_GRID: //그리기
			break;
		case ID_MOVE:
			break;
		case ID_STOP:
			break;
		case ID_RECTANGLE:
			break;
		case ID_CIRCLE:
			break;
	
		}
		break;
	}
	return 0;
}
