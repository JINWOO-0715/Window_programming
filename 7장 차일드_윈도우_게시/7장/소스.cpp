#include <Windows.h>
#include <time.h>
#include <math.h>

#pragma comment(lib, "msimg32.lib")
#define Radians  3.141592f
#define ID_RECTANGLE 100
#define ID_SQURE 101
#define ID_ELLIPSE 102

#define ID_MAX 103
#define ID_MID 104
#define ID_MIN 105

#define ID_STAR_SPEED 111
#define ID_STAR_SIZE 1112

#define ID_COLOR1 106
#define ID_COLOR2 107
#define ID_COLOR3 108

#define ID_REVERSE 109
#define ID_EXIT 110




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
struct gravity
{
	float x;
	float y;
	int radian;
	float angle;
	int shape;
	int r;
	int g;
	int b;
	int direction = 1;
	int speed = 10;
};
struct Track
{
	float x;
	float y;
	int radian;
	int size;
	float angle;


};

gravity star;
Track track;



// 함수 선언
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK ChildProc(HWND, UINT, WPARAM, LPARAM);
void Draw_Ellipse(HDC *hdc, int radius, int x, int y);

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

	// 자식 윈도우 
	WndClass.hCursor = LoadCursor(NULL, IDC_HELP);
	WndClass.lpfnWndProc = ChildProc;
	WndClass.lpszClassName = "Child";

	WndClass.hbrBackground = (HBRUSH)GetStockObject(GRAY_BRUSH);
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
static int index = 0;;
static int shape_choice = ID_ELLIPSE;
static int shape_size = ID_MAX;
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	HDC hdc, memdc;
	static RECT crt; // 직사각형모양 범위 선언
	PAINTSTRUCT ps;
	static HWND hspeed, hsize;
	static int startX, startY;
	static bool Drag;
	static int endX, endY;
	int TempPos;
	int size = 750;
	static HBITMAP hBitmap, hOldBitmap;

	static 	POINT rectangle[900];
	static 	POINT rectangle2[1400];
	static 	POINT rectangle3[1800];

	static 	POINT squre[300];
	static 	POINT squre3[450];
	static 	POINT squre2[600];


	// 메시지 처리하기

	switch (uMsg)
	{

	case WM_CREATE:
	{
		GetClientRect(hWnd, &crt);

		CreateWindow("Child", NULL, WS_CHILD | WS_VISIBLE,
			0, 0, 600, 600, hWnd, NULL, g_hInstance, NULL);
		CreateWindow("button", "원", WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON,
			800, 200, 50, 50, hWnd, (HMENU)ID_ELLIPSE, g_hInstance, NULL);
		CreateWindow("button", "사각형", WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON,
			800, 250, 50, 50, hWnd, (HMENU)ID_RECTANGLE, g_hInstance, NULL);
		CreateWindow("button", "삼각형", WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON,
			800, 300, 50, 50, hWnd, (HMENU)ID_SQURE, g_hInstance, NULL);

		CreateWindow("button", "대", WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON,
			900, 200, 50, 50, hWnd, (HMENU)ID_MAX, g_hInstance, NULL);
		CreateWindow("button", "중", WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON,
			900, 250, 50, 50, hWnd, (HMENU)ID_MID, g_hInstance, NULL);
		CreateWindow("button", "소", WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON,
			900, 300, 50, 50, hWnd, (HMENU)ID_MIN, g_hInstance, NULL);

		CreateWindow("button", "색상1", WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX,
			1000, 200, 100, 50, hWnd, (HMENU)ID_COLOR1, g_hInstance, NULL);
		CreateWindow("button", "색상2", WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX,
			1000, 250, 100, 50, hWnd, (HMENU)ID_COLOR2, g_hInstance, NULL);
		CreateWindow("button", "색상3", WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX,
			1000, 300, 100, 50, hWnd, (HMENU)ID_COLOR3, g_hInstance, NULL);

		hspeed = CreateWindow("scrollbar", NULL, WS_CHILD | WS_VISIBLE | SBS_HORZ,
			800, 400, 300, 50, hWnd, (HMENU)ID_STAR_SPEED, g_hInstance, NULL);

		hsize = CreateWindow("scrollbar", NULL, WS_CHILD | WS_VISIBLE | SBS_HORZ,
			800, 500, 300, 50, hWnd, (HMENU)ID_STAR_SIZE, g_hInstance, NULL);


		CreateWindow("button", "반대로이동", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			800, 50, 150, 50, hWnd, (HMENU)ID_REVERSE, g_hInstance, NULL);
		CreateWindow("button", "종료", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			1000, 50, 150, 50, hWnd, (HMENU)ID_EXIT, g_hInstance, NULL);

		SetScrollRange(hsize, SB_CTL, 0, 200, TRUE);
		SetScrollPos(hsize, SB_CTL, 0, TRUE);

		SetScrollRange(hspeed, SB_CTL, 0, 150, TRUE);
		SetScrollPos(hspeed, SB_CTL, 0, TRUE);

		Drag = false;
		SetTimer(hWnd, 0, 150, NULL);


		break;
	}
	break;
	case WM_TIMER:
	{
		InvalidateRgn(hWnd, NULL, false);
		break;
	}
	break;
	case WM_HSCROLL:
		if ((HWND)lParam == hspeed)
			TempPos = star.speed;
		if ((HWND)lParam == hsize)
			TempPos = star.radian;
		switch (LOWORD(wParam)) {
		case SB_LINELEFT: TempPos = max(0, TempPos - 1); break;
		case SB_LINERIGHT: TempPos = min(255, TempPos + 1); break;
		case SB_PAGELEFT: TempPos = max(0, TempPos - 10); break;
		case SB_PAGERIGHT: TempPos = min(255, TempPos + 10); break;
		case SB_THUMBTRACK: TempPos = HIWORD(wParam); break;
		}
		if ((HWND)lParam == hspeed)
			star.speed = TempPos;
		if ((HWND)lParam == hsize)
			star.radian = TempPos;
		SetScrollPos((HWND)lParam, SB_CTL, TempPos, TRUE);
		InvalidateRect(hWnd, NULL, false);
		break;
	case WM_COMMAND:
	{
		switch (LOWORD(wParam)) {
		case ID_RECTANGLE:
			shape_choice = ID_RECTANGLE;
			index = 0;
			break;
		case ID_SQURE:
			shape_choice = ID_SQURE;
			index = 0;
			break;
		case ID_ELLIPSE:
			shape_choice = ID_ELLIPSE;
			index = 0;
			break;
		case ID_MAX:
			track.radian = 250;
			shape_size = ID_MAX;
			index = 0;
			break;
		case ID_MID:
			track.radian = 200;
			shape_size = ID_MID;
			index = 0;
			break;

		case ID_MIN:
			track.radian = 150;
			shape_size = ID_MIN;
			index = 0;
			break;

		case ID_COLOR1:
			star.r = 100;
			star.g = 0;
			star.b = 0;

			break;
		case ID_COLOR2:
			star.r = 0;
			star.g = 100;
			star.b = 0;
			break;
		case ID_COLOR3:
			star.r = 0;
			star.g = 0;
			star.b = 100;
			break;

		case ID_REVERSE:

			if (star.direction == 1)
			{
				star.direction = 2;
			}
			else if (star.direction == 2)
			{
				star.direction = 1;

			}

			break;
		case ID_EXIT:
			PostQuitMessage(0);
			break;
		}
		break;
	}
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
	case WM_RBUTTONDOWN:
	{
		int mousex = LOWORD(lParam);
		int mousey = HIWORD(lParam);
	}
	break;
	case WM_LBUTTONDOWN:
	{
		int mousex = LOWORD(lParam);
		int mousey = HIWORD(lParam);
	}
	break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);

}
LRESULT CALLBACK ChildProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{

	HDC hdc, memdc2;
	static RECT crt; // 직사각형모양 범위 선언
	PAINTSTRUCT ps;
	HPEN hpen, oldpen;
	HBRUSH hBrush, oldBrush;
	static int startX, startY;
	static bool Drag;
	static int endX, endY;

	static HBITMAP hBitmap, hOldBitmap;

	static bool bEllipse = true;
	static float radian_data = 20;
	static float m_degree_data = 10;



	switch (iMessage)
	{
	case WM_CREATE:
		GetClientRect(hWnd, &crt);
		track.x = 300;
		track.y = 300;
		track.radian = 250;
		track.size = 3;
		track.angle = 10;
		star.radian = 20;


		static 	POINT rectangle[900];
		static 	POINT rectangle2[1400];
		static 	POINT rectangle3[1800];

		static 	POINT squre[300];
		static 	POINT squre3[450];
		static 	POINT squre2[600];


		for (int i = 0; i < 250; i++)
		{
			rectangle[i].x = i;
			rectangle[i].y = 0;

		}
		for (int i = 250; i < 500; i++)
		{
			rectangle[i].x = 250;
			rectangle[i].y = i - 250;

		}
		for (int i = 500; i < 750; i++)
		{
			rectangle[i].x = 250 - (i - 500);
			rectangle[i].y = 250;

		}
		for (int i = 750; i < 900; i++)
		{
			rectangle[i].x = 0;
			rectangle[i].y = 250 - (i - 750);

		} // 소 사각형

		for (int i = 0; i < 350; i++)
		{
			rectangle2[i].x = i;
			rectangle2[i].y = 0;

		}
		for (int i = 350; i < 700; i++)
		{
			rectangle2[i].x = 350;
			rectangle2[i].y = i - 350;

		}
		for (int i = 700; i < 1050; i++)
		{
			rectangle2[i].x = 350 - (i - 700);
			rectangle2[i].y = 350;

		}
		for (int i = 1050; i < 1400; i++)
		{
			rectangle2[i].x = 0;
			rectangle2[i].y = 350 - (i - 1050);

		} // 중사각형

		for (int i = 0; i < 450; i++)
		{
			rectangle3[i].x = i;
			rectangle3[i].y = 0;

		}
		for (int i = 450; i < 900; i++)
		{
			rectangle3[i].x = 450;
			rectangle3[i].y = i - 450;

		}
		for (int i = 900; i < 1350; i++)
		{
			rectangle3[i].x = 450 - (i - 900);
			rectangle3[i].y = 450;

		}
		for (int i = 1350; i < 1800; i++)
		{
			rectangle3[i].x = 0;
			rectangle3[i].y = 450 - (i - 1350);

		} // 대사각형

		for (int i = 0; i < 100; i++)
		{
			squre[i].x = 300 + i;
			squre[i].y = 300 + i;
		}
		for (int i = 100; i < 200; i++)
		{
			squre[i].x = 400 - (2 * (i - 100));
			squre[i].y = 400;
		}
		for (int i = 200; i < 300; i++)
		{
			squre[i].x = 200 + (i - 200);
			squre[i].y = 400 - (i - 200);
		}// 소삼각형

		for (int i = 0; i < 200; i++)
		{
			squre2[i].x = 300 + i;
			squre2[i].y = 300 + i;
		}
		for (int i = 200; i < 400; i++)
		{
			squre2[i].x = 500 - (2 * (i - 200));
			squre2[i].y = 500;
		}
		for (int i = 400; i < 600; i++)
		{
			squre2[i].x = 100 + (i - 400);
			squre2[i].y = 500 - (i - 400);
		}// 대삼각형

		for (int i = 0; i < 150; i++)
		{
			squre3[i].x = 300 + i;
			squre3[i].y = 300 + i;
		}
		for (int i = 150; i < 300; i++)
		{
			squre3[i].x = 450 - (2 * (i - 150));
			squre3[i].y = 450;
		}
		for (int i = 300; i < 450; i++)
		{
			squre3[i].x = 150 + (i - 300);
			squre3[i].y = 450 - (i - 300);
		}// 중삼각형
		SetTimer(hWnd, 0, 150, NULL);
		Drag = false;

		break;
	case WM_TIMER:
	{
		switch (star.direction)
		{
		case 1:

			if (shape_choice == ID_ELLIPSE)
			{
				m_degree_data -= star.speed;
				radian_data = m_degree_data * 3.141592 / 180;
			}

			if (shape_choice == ID_RECTANGLE && shape_size == ID_MAX)
			{
				star.x = rectangle3[index].x;
				star.y = rectangle3[index].y;
				index += star.speed;


			}
			else if (shape_choice == ID_RECTANGLE && shape_size == ID_MID)
			{
				star.x = rectangle2[index].x;
				star.y = rectangle2[index].y;
				index += star.speed;

			}
			else if (shape_choice == ID_RECTANGLE && shape_size == ID_MIN)
			{
				star.x = rectangle[index].x;
				star.y = rectangle[index].y;
				index += star.speed;

			}
			if (shape_choice == ID_SQURE && shape_size == ID_MAX)
			{
				star.x = squre2[index].x;
				star.y = squre2[index].y;
				index += star.speed;

			}
			else if (shape_choice == ID_SQURE && shape_size == ID_MID)
			{
				star.x = squre3[index].x;
				star.y = squre3[index].y;
				index += star.speed;

			}
			else if (shape_choice == ID_SQURE && shape_size == ID_MIN)
			{
				star.x = squre[index].x;
				star.y = squre[index].y;
				index += star.speed;

			}


			break;
		case 2:
			if (shape_choice == ID_ELLIPSE)
			{
				m_degree_data += star.speed;
				radian_data = m_degree_data * 3.141592 / 180;
			}
			if (shape_choice == ID_RECTANGLE && shape_size == ID_MAX)
			{
				star.x = rectangle3[index].x;
				star.y = rectangle3[index].y;

				index -= star.speed;

			}
			else if (shape_choice == ID_RECTANGLE && shape_size == ID_MID)
			{
				star.x = rectangle2[index].x;
				star.y = rectangle2[index].y;

				index -= star.speed;
			}
			else if (shape_choice == ID_RECTANGLE && shape_size == ID_MIN)
			{
				star.x = rectangle[index].x;
				star.y = rectangle[index].y;

				index -= star.speed;
			}

			if (shape_choice == ID_SQURE && shape_size == ID_MAX)
			{
				star.x = squre[index].x;
				star.y = squre[index].y;

				index -= star.speed;
			}
			else if (shape_choice == ID_SQURE && shape_size == ID_MID)
			{
				star.x = squre3[index].x;
				star.y = squre3[index].y;

				index -= star.speed;
			}
			else if (shape_choice == ID_SQURE && shape_size == ID_MIN)
			{
				star.x = squre2[index].x;
				star.y = squre2[index].y;

				index -= star.speed;
			}


			break;
		}
		InvalidateRgn(hWnd, NULL, false);
	}
	break;
	case WM_PAINT:

		hdc = BeginPaint(hWnd, &ps);

		memdc2 = CreateCompatibleDC(hdc);
		hBitmap = CreateCompatibleBitmap(hdc, crt.right, crt.bottom);
		hOldBitmap = (HBITMAP)SelectObject(memdc2, hBitmap);
		Rectangle(memdc2, 0, 0, 600, 600);

		if (shape_choice == ID_RECTANGLE && shape_size == ID_MIN)
		{
			Polyline(memdc2, rectangle, 900);
		}
		if (shape_choice == ID_RECTANGLE && shape_size == ID_MID)
		{
			Polyline(memdc2, rectangle2, 1400);
		}
		if (shape_choice == ID_RECTANGLE && shape_size == ID_MAX)
		{
			Polyline(memdc2, rectangle3, 1800);
		}

		if (shape_choice == ID_ELLIPSE)
		{
			Draw_Ellipse(&memdc2, track.radian, track.x, track.y);
			star.x = track.x + (cos(radian_data) * track.radian);
			star.y = track.y + (sin(radian_data) * track.radian);

		}
		if (shape_choice == ID_SQURE && shape_size == ID_MIN)
		{
			Polyline(memdc2, squre, 300);
		}
		else if (shape_choice == ID_SQURE && shape_size == ID_MID)
		{
			Polyline(memdc2, squre3, 450);
		}
		else if (shape_choice == ID_SQURE && shape_size == ID_MAX)
		{
			Polyline(memdc2, squre2, 600);
		}


		//사각	Polyline(memdc2, rectangle, 900);

			//Polyline(memdc2, squre3, 450);



		hBrush = CreateSolidBrush(RGB(star.r, star.g, star.b));
		oldBrush = (HBRUSH)SelectObject(memdc2, hBrush);


		Draw_Ellipse(&memdc2, star.radian, star.x, star.y);

		DeleteObject(hBrush);


		BitBlt(hdc, 0, 0, crt.right, crt.bottom, memdc2, 0, 0, SRCCOPY);

		DeleteObject(SelectObject(memdc2, hOldBitmap));
		DeleteDC(memdc2);


		EndPaint(hWnd, &ps);
		break;

	case WM_LBUTTONDOWN:
		InvalidateRect(hWnd, NULL, false);
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}

	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}

void Draw_Ellipse(HDC *hdc, int radius, int x, int y)
{
	Ellipse(*hdc, x - radius, y - radius, x + radius, y + radius);
}