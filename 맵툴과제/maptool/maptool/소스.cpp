#include <Windows.h>
#include <time.h>
#include <math.h>
#pragma comment(lib, "msimg32.lib")
#define MAP_SIZE1 10 
#define GRID_ON 11111
#define GRID_OFF 11112
#define OBJECT 11112
#define ITEM 11112
#define MONSER 11112
#define MAP_SIZE2 6

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
struct OBject {
	int x;
	int y;
	bool view;
	RECT BoundingBox;

	


};	
struct MAP {

	POINT map;
	RECT BoundingBox;
	bool view = true;

};
MAP Map[MAP_SIZE1][MAP_SIZE1];

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
	HPEN hpen, oldpen;
	HBRUSH hBrush, oldBrush;

	static int startX, startY;
	static bool Drag;
	static int endX, endY;

	static HBITMAP hBitmap, hOldBitmap;
	static int radian =60;

	// 메시지 처리하기
	switch (uMsg)
	{
	case WM_CREATE:
	{
		GetClientRect(hWnd, &crt);
		Drag = false;

		for (int j = 0; j < MAP_SIZE1; j++)
		{
			for (int i = 0; i < MAP_SIZE1; i++)
			{
				Map[i][j].map.x = (i + 1) * 60 - 30;
				Map[i][j].map.y = (j + 1) * 60 - 30;
			}
		}

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

		for (int j = 0; j < MAP_SIZE1; j++)
		{
			for (int i = 0; i < MAP_SIZE1; i++)
			{
				Rectangle(memdc, Map[i][j].map.x - (radian / 2), Map[i][j].map.y - (radian / 2),
					Map[i][j].map.x + (radian / 2), Map[i][j].map.y + (radian / 2));
			}
		}

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
		int mousex = LOWORD(lParam);
		int mousey = HIWORD(lParam);
	}
	break;
	case WM_LBUTTONUP:
	{


	}
	break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);

}