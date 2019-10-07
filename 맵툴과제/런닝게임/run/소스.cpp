#include <Windows.h>
#include <math.h>
#include<stdio.h>
#include<stdlib.h>
#include <time.h>
#include <string.h>
#include "resource.h"
#pragma comment(lib, "msimg32.lib")

#ifdef UNICODE
#pragma comment(linker, "/entry:wWinMainCRTStartup /subsystem:console") 
#else
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console") 
#endif

#define WINDOW_X 1600
#define WINDOW_Y 800
#define ID_BLOCK_1 11111
#define ID_BLOCK_2 11112
#define ID_BLOCK_3 11113

#define ID_STOP 1
#define ID_MOVE 2
#define ID_SELECT 3
#define ID_DONE 4
#define ID_NEXT 5
#define ID_PREV 6
#define ID_LIST 7000
#define block1 2222
#define block2 2223
#define block3 2224



struct MAP

{
	POINT pos;
	POINT size;
	int kind;
	bool view = false;
	int jump = 0;
	bool object_view = false;
	int monster_type;
	MAP& operator = (const MAP& rhs)
	{
		pos = rhs.pos;
		size = rhs.size;
		kind = rhs.kind;
	}


};
HINSTANCE g_hInstance;
LPCTSTR lpszClass = "ParentClass";
LPCTSTR lpszChildClass = "ChildClass";
LPCTSTR lpszWindowName = "Window Program 7-3 : 차일드 윈도우와 컨트롤을 이용하여 연결된 그림 만들기";


// 함수 선언
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK ChildWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

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

	// 차일드 윈도우1 클래스 등록
	WndClass.hCursor = LoadCursor(NULL, IDC_HELP);
	WndClass.hbrBackground = (HBRUSH)GetStockObject(GRAY_BRUSH);
	WndClass.lpszClassName = lpszChildClass;
	WndClass.lpfnWndProc = (WNDPROC)ChildWndProc;
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
static int selection;
static int background_count = 0;
static int background_type[3];
static int PLAY =0 ;
static int nx = 0;


int Current_kind;
MAP map[15][45];

bool IsPointinRecTangle(POINT m, MAP rc)
{
	if ((rc.pos.x <= m.x) && (m.x <= (rc.pos.x + rc.size.x))

		&& (rc.pos.y <= m.y) && (m.y <= (rc.pos.y + rc.size.y)))

	{
		return true;
	}
	else
	{
		return false;
	}

}
bool CrushRectanGle(POINT m, MAP rc)
{
	if ((rc.pos.x <= m.x) && (m.x <= (rc.pos.x + rc.size.x))

		&& (rc.pos.y <= m.y) && (m.y <= (rc.pos.y + rc.size.y)))

	{
		return true;
	}
	else
	{
		return false;
	}

}

bool Crush(MAP  r, MAP r2, int nx)
{
	if (((r.pos.x-nx)<(r2.pos.x+r2.size.x)) && (r.pos.y< (r2.pos.y+r2.size.y))&& (((r.pos.x-nx)+r.size.x)>r2.pos.x)&& ((r.pos.y+r.size.y)>r2.pos.y))
	{
		return true;
	}
	else
	{
		return false;
	}
}
bool up_Crush(MAP  r, MAP r2, int nx)
{
	if (r.pos.y < (r2.pos.y + r2.size.y)&& ((r.pos.y + r.size.y) > r2.pos.y))
	{
		return true;
	}
	else
	{
		return false;
	}
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	HDC hdc, memdc, bitDC , blockDC;

	static RECT crt; // 직사각형모양 범위 선언
	PAINTSTRUCT ps;
	static HBITMAP page[3];
	static HBITMAP BLOCK[3];
	static HBITMAP hBitmap, hOldBitmap;
	static POINT mouse;
	HWND hWndChild;

	RECT childrt = { 30, 30, 600, 600 };

	static HWND hButtonLeft, hButtonRight;
	static HWND hEdit, hButtonPaintpan, hListBox;

	static HFONT hFont;
	static HWND hlist;
	static HWND hButton[5];

	static char Items[][256] = { "1" };
	static char Items2[][256] = { "2" };
	static char Items3[][256] = { "3" };

	
	static int selection_index = 0;
	static int selection_store[10];

	// 메시지 처리하기
	switch (uMsg)
	{
	case WM_CREATE:
	{

		GetClientRect(hWnd, &crt);

		AdjustWindowRect(&childrt, WS_OVERLAPPEDWINDOW, false);

		CreateWindow("ChildClass", NULL,  WS_CHILD | WS_VISIBLE | WS_BORDER,
			100, 50, 600, 600, hWnd, NULL, g_hInstance, NULL);  // 차일드 윈도우 생성

		CreateWindow("button", "이동", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			900, 300, 50, 50, hWnd, (HMENU)ID_MOVE, g_hInstance, NULL);

		CreateWindow("button", "선택", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			900, 200, 50, 50, hWnd, (HMENU)ID_SELECT, g_hInstance, NULL);

		/*CreateWindow("button", "이동", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		 900, 300, 50, 50, hWnd, (HMENU)ID_MOVE, g_hInstance, NULL);*/
		CreateWindow("button", "멈춤", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			900, 400, 50, 50, hWnd, (HMENU)ID_STOP, g_hInstance, NULL);
		CreateWindow("button", "TEST", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			900, 500, 50, 50, hWnd, (HMENU)ID_DONE, g_hInstance, NULL);
		CreateWindow("button", "◀", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			10, 300, 50, 50, hWnd, (HMENU)ID_PREV, g_hInstance, NULL);
		CreateWindow("button", "▶", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			800, 300, 50, 50, hWnd, (HMENU)ID_NEXT, g_hInstance, NULL);
		hlist = CreateWindow("listbox", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | LBS_STANDARD,
			1000, 180, 100, 100, hWnd, (HMENU)ID_LIST, g_hInstance, NULL);

		hButton[0]=CreateWindow("button", "", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON|BS_BITMAP,
			900, 600, 100, 100, hWnd, (HMENU)ID_BLOCK_1, g_hInstance, NULL);
		hButton[1] = CreateWindow("button", "", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_BITMAP,
			1000, 600, 100, 100, hWnd, (HMENU)ID_BLOCK_2, g_hInstance, NULL);
		hButton[2] = CreateWindow("button", "", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_BITMAP,
			1100, 600, 100, 100, hWnd, (HMENU)ID_BLOCK_3, g_hInstance, NULL);
			SendMessage(hlist, LB_ADDSTRING, 0, (LPARAM)Items); // 값이 들어그는
			SendMessage(hlist, LB_ADDSTRING, 0, (LPARAM)Items2); // 값이 들어그는
			SendMessage(hlist, LB_ADDSTRING, 0, (LPARAM)Items3); // 값이 들어그는

			BLOCK[0] = LoadBitmap(g_hInstance, MAKEINTRESOURCE(ID_BLOCK2));
			BLOCK[1] = LoadBitmap(g_hInstance, MAKEINTRESOURCE(ID_BLOCK1));
			BLOCK[2] = LoadBitmap(g_hInstance, MAKEINTRESOURCE(ID_BLOCK2));


			SendMessage(hButton[0], BM_SETIMAGE, NULL,(LPARAM)BLOCK[0]);
			SendMessage(hButton[1], BM_SETIMAGE, NULL, (LPARAM)BLOCK[1]);
			SendMessage(hButton[2], BM_SETIMAGE, NULL, (LPARAM)BLOCK[2]);


	}
	break;
	case WM_LBUTTONDOWN:
	{


		break;
	}
	case WM_PAINT:
	{
		hdc = BeginPaint(hWnd, &ps);

		memdc = CreateCompatibleDC(hdc);
		hBitmap = CreateCompatibleBitmap(hdc, crt.right, crt.bottom);
		hOldBitmap = (HBITMAP)SelectObject(memdc, hBitmap);

		FillRect(memdc, &crt, (HBRUSH)GetStockObject(WHITE_BRUSH)); //도화지 색 변경


		bitDC = CreateCompatibleDC(memdc);


		
		BitBlt(hdc, 0, 0, crt.right, crt.bottom, memdc, 0, 0, SRCCOPY);

		DeleteObject(SelectObject(memdc, hOldBitmap));
		DeleteDC(memdc);

		EndPaint(hWnd, &ps);
	}
	case WM_COMMAND:
	{
		switch (LOWORD(wParam))
		{
		case ID_LIST:
			if (HIWORD(wParam) == CBN_SELCHANGE)
			{
				selection = SendMessage(hlist, LB_GETCURSEL, 0, 0);

			}
			break;
		case ID_SELECT:
			InvalidateRect(hWnd, NULL, false);
			background_type[background_count] = selection;
			background_count++;


			break;

		case ID_NEXT:
			background_count++;
			if (nx < 1200)
			{
				nx += 600;
			}
			
			InvalidateRect(hWnd, NULL, false);
			break;
		case ID_PREV:
			background_count--;
			if (nx > 0)
			{

				nx -= 600;
			}
			InvalidateRect(hWnd, NULL, false);
			break;
		case ID_BLOCK_1:
			Current_kind = block1;
			break;
		case ID_BLOCK_2:
			Current_kind = block2;

			break;
		case ID_BLOCK_3:
			Current_kind = block3;

			break;
		case ID_DONE:
			PLAY = 1;
			break;
		case ID_STOP:
			PLAY = 0;

			break;
		}

		break;
	}

	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

LRESULT CALLBACK ChildWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	HDC hdc, memdc, bitDC[3], blockDC;

	static RECT crt; // 직사각형모양 범위 선언
	PAINTSTRUCT ps;
	static HBITMAP page[3] ,oldbit1;
	static HBITMAP BLOCK[3] ,BackGround[3],bit_hero;
	static HBITMAP hBitmap, hOldBitmap;
	static MAP hero;

	HWND hWndChild;

	RECT childrt = { 30, 30, 600, 600 };
	static bool mouse_check = false;
	static HWND hButtonLeft, hButtonRight;
	static HWND hEdit, hButtonPaintpan, hListBox;

	static HFONT hFont;
	static HWND hlist;
	static float jump_gage = 0.0f;
	static HWND hButton[5];
	static POINT mouse;
	static char Items[][256] = { "1" };
	static char Items2[][256] = { "2" };
	static char Items3[][256] = { "3" };
	HBRUSH hBrush1, oldBrush;
	static int gtavity=1;
	static int selection_index = 0;
	static int selection_store[10];

	// 메시지 처리하기
	switch (uMsg)
	{
	case WM_CREATE:
	{
	
		GetClientRect(hWnd, &crt);
		for (int i = 0; i < 15; i++) // 그리드 (타일 그리기)
		{
			for (int j = 0; j < 45; j++)
			{
				int x = 40;
				int y = 40;
				map[i][j].pos.x = j * x;
				map[i][j].pos.y = i * y;
				map[i][j].size.x = x;
				map[i][j].size.y = y;

			}
		}
		hero.pos.x = 50;
		hero.pos.y = 100;

		hero.size.x = 40;
		hero.size.y = 40;
		AdjustWindowRect(&childrt, WS_OVERLAPPEDWINDOW, false);

	
		BLOCK[0] = LoadBitmap(g_hInstance, MAKEINTRESOURCE(ID_BLOCK1));
		BLOCK[1] = LoadBitmap(g_hInstance, MAKEINTRESOURCE(ID_BLOCK2));
		BLOCK[2] = LoadBitmap(g_hInstance, MAKEINTRESOURCE(ID_BLOCK3));

		bit_hero = LoadBitmap(g_hInstance, MAKEINTRESOURCE(ID_HERO));
		BackGround[0] = LoadBitmap(g_hInstance, MAKEINTRESOURCE(ID_BACKGROUND1));
		BackGround[1] = LoadBitmap(g_hInstance, MAKEINTRESOURCE(ID_BACKGROUND2));
		BackGround[2] = LoadBitmap(g_hInstance, MAKEINTRESOURCE(ID_BACKGROUND3));

		SendMessage(hButton[0], BM_SETIMAGE, NULL, (LPARAM)BLOCK[0]);
		SendMessage(hButton[1], BM_SETIMAGE, NULL, (LPARAM)BLOCK[1]);
		SendMessage(hButton[2], BM_SETIMAGE, NULL, (LPARAM)BLOCK[2]);

		SetTimer(hWnd, 0, 10, NULL);
	}
	break;
	case WM_TIMER:
	{ // 시간이 경과하면 메시지 자동 생성

		if (nx< 0 )
		{
			nx = 0;
		}
		if (nx > 1500)
		{
			nx = 0;
		}
		if (PLAY == 1)
		{
	
			
	
			hero.pos.y += (gtavity + 2);
	
			nx += 2;
			if (nx > 1799)
			{
				nx -= 0;
			}
			if (hero.jump == 1)
			{

				hero.pos.y -= 9;
				jump_gage += 0.05f;
				if (jump_gage > 0.8f)
				{
					hero.jump = 2;


				}

			}
			if (hero.jump == 2)
			{
				hero.pos.y += 9;
				jump_gage -= 0.05f;
				if (jump_gage < 0.0f)
				{
					hero.jump = 0;


				}
			}


			if (GetAsyncKeyState('W') & 0x8000 || GetAsyncKeyState('w') & 0x8000)
			{
				hero.jump = 1;

			}
			if (GetAsyncKeyState('a') & 0x8000 || GetAsyncKeyState('A') & 0x8000)
			{
				hero.pos.x -= 3;

			}
			if (GetAsyncKeyState('d') & 0x8000 || GetAsyncKeyState('D') & 0x8000)
			{
				hero.pos.x += 3;

			}
			for (int i = 0; i < 15; i++)
			{
				for (int j = nx / 40; j < 45; j++)
				{
					if (map[i][j].object_view == true)
					{
						if (Crush(map[i][j], hero, nx))
						{
					
							hero.pos.y -= (gtavity+2);
						}
	
					}


				}

			}
		
		}
		printf_s("%d \n", hero.pos.y);
	
		// 맵타일 충돌 체크 


		InvalidateRgn(hWnd, NULL, FALSE);
		break;
	}
	case WM_LBUTTONDOWN:
	{	mouse_check = true;
	mouse.x = LOWORD(lParam);
		mouse.y = HIWORD(lParam);

	
	}	InvalidateRect(hWnd, NULL, FALSE);
	break;
	case WM_MOUSEMOVE:
	{
		if(mouse_check)
		{
		mouse.x = LOWORD(lParam);
		mouse.y = HIWORD(lParam);
	
		if (nx < 599)
		{

			for (int i = 0; i < 15; i++) // 그리드 (타일 그리기)
			{
				for (int j = 0; j < 15; j++)
				{
					if (IsPointinRecTangle(mouse, map[i][j]))
					{
						map[i][j].kind = Current_kind;
						map[i][j].object_view = true;
					}

				}
			}


		}

		if (nx > 599 && nx < 1119)
		{


			for (int i = 0; i < 15; i++) // 그리드 (타일 그리기)
			{
				for (int j = 0; j < 15; j++)
				{
					if (IsPointinRecTangle(mouse, map[i][j]))
					{
						map[i][j + 15].kind = Current_kind;
						map[i][j + 15].object_view = true;
					}

				}
			}

		}
		if (nx > 1119 && nx < 1800)
		{

			for (int i = 0; i < 15; i++) // 그리드 (타일 그리기)
			{
				for (int j = 0; j < 15; j++)
				{
					if (IsPointinRecTangle(mouse, map[i][j]))
					{
						map[i][j + 30].kind = Current_kind;
						map[i][j + 30].object_view = true;
					}

				}
			}

		}
		
		InvalidateRect(hWnd, NULL, FALSE);
		
		}
		break;
	}
	case WM_LBUTTONUP:
		mouse_check = false;
		InvalidateRect(hWnd, NULL, FALSE);
		break;
	case WM_KEYDOWN:
	{


		InvalidateRect(hWnd, NULL, FALSE);
		break;
	}
	
	case WM_PAINT:
	{
		hdc = BeginPaint(hWnd, &ps);

		memdc = CreateCompatibleDC(hdc);
		hBitmap = CreateCompatibleBitmap(hdc, crt.right, crt.bottom);
		hOldBitmap = (HBITMAP)SelectObject(memdc, hBitmap);

		FillRect(memdc, &crt, (HBRUSH)GetStockObject(WHITE_BRUSH)); //도화지 색 변경

		bitDC[0] = CreateCompatibleDC(memdc);
		bitDC[1] = CreateCompatibleDC(memdc);
		bitDC[2] = CreateCompatibleDC(memdc);

		SelectObject(bitDC[0], BackGround[0]);
		SelectObject(bitDC[1], BackGround[1]);
		SelectObject(bitDC[2], BackGround[2]);
	
		BitBlt(memdc, 0 - nx, 0, 600, 600, bitDC[0], 0, 0, SRCCOPY);
		BitBlt(memdc, 600 - nx, 0, 600, 600, bitDC[1], 0, 0, SRCCOPY);
		BitBlt(memdc, 1200 - nx, 0, 600, 600, bitDC[2], 0, 0, SRCCOPY);
		if (nx > 1200)
		{
			BitBlt(memdc, 1800 - nx, 0, 600, 600, bitDC[0], 0, 0, SRCCOPY);
			BitBlt(memdc, 2400 - nx, 0, 600, 600, bitDC[1], 0, 0, SRCCOPY);

		}


		for (int i = 0; i < 15; i++)
		{
			for (int j = 0; j < 45; j++)
			{
				hBrush1 = (HBRUSH)GetStockObject(NULL_BRUSH);
				oldBrush = (HBRUSH)SelectObject(memdc, hBrush1);
				int x = 40;
				int y = 40;
				Rectangle(memdc, j * x, i * y, (j + 1) * x, (i + 1) * y);

				SelectObject(memdc, oldBrush);
				DeleteObject(hBrush1);
			}
		}

		blockDC		 = CreateCompatibleDC(memdc);

	
		if (nx < 599 && PLAY ==0)
		{
			for (int i = 0; i < 15; i++)
			{
				for (int j = 0; j < 15; j++)
				{
					switch (map[i][j].kind)
					{
					case block1:
						oldbit1 = (HBITMAP)SelectObject(blockDC, BLOCK[0]);

						StretchBlt(memdc, map[i][j].pos.x, map[i][j].pos.y, map[i][j].size.x, map[i][j].size.y, blockDC, 0, 0, 90, 30, SRCCOPY); //1024 * 640

						break;
					case block2:
						oldbit1 = (HBITMAP)SelectObject(blockDC, BLOCK[1]);

						StretchBlt(memdc, map[i][j].pos.x, map[i][j].pos.y, map[i][j].size.x, map[i][j].size.y, blockDC, 0, 0, 90, 30, SRCCOPY); //1024 * 640


						break;
					case block3:
						oldbit1 = (HBITMAP)SelectObject(blockDC, BLOCK[2]);

						StretchBlt(memdc, map[i][j].pos.x, map[i][j].pos.y, map[i][j].size.x, map[i][j].size.y, blockDC, 0, 0, 60, 30, SRCCOPY); //1024 * 640


						break;
					}
				}
			}
		}
		 if (nx < 1119 && nx >599 && PLAY == 0)
		{
			for (int i = 0; i < 15; i++)
			{
				for (int j = 0; j < 15; j++)
				{
					switch (map[i][j+15].kind)
					{
					case block1:
						oldbit1 = (HBITMAP)SelectObject(blockDC, BLOCK[0]);

						StretchBlt(memdc, map[i][j].pos.x, map[i][j].pos.y, map[i][j].size.x, map[i][j].size.y, blockDC, 0, 0, 90, 30, SRCCOPY); //1024 * 640

						break;
					case block2:
						oldbit1 = (HBITMAP)SelectObject(blockDC, BLOCK[1]);

						StretchBlt(memdc, map[i][j].pos.x, map[i][j].pos.y, map[i][j].size.x, map[i][j].size.y, blockDC, 0, 0, 90, 30, SRCCOPY); //1024 * 640


						break;
					case block3:
						oldbit1 = (HBITMAP)SelectObject(blockDC, BLOCK[2]);

						StretchBlt(memdc, map[i][j].pos.x, map[i][j].pos.y, map[i][j].size.x, map[i][j].size.y, blockDC, 0, 0, 60, 30, SRCCOPY); //1024 * 640


						break;
					}
				}
			}
		}
		 if (nx < 1800 && nx >1119 && PLAY == 0)
		{
			for (int i = 0; i < 15; i++)
			{
				for (int j = 0; j < 15; j++)
				{
					switch (map[i][j+30].kind)
					{
					case block1:
						oldbit1 = (HBITMAP)SelectObject(blockDC, BLOCK[0]);

						StretchBlt(memdc, map[i][j].pos.x, map[i][j].pos.y, map[i][j].size.x, map[i][j].size.y, blockDC, 0, 0, 90, 30, SRCCOPY); //1024 * 640

						break;
					case block2:
						oldbit1 = (HBITMAP)SelectObject(blockDC, BLOCK[1]);

						StretchBlt(memdc, map[i][j].pos.x, map[i][j].pos.y, map[i][j].size.x, map[i][j].size.y, blockDC, 0, 0, 90, 30, SRCCOPY); //1024 * 640


						break;
					case block3:
						oldbit1 = (HBITMAP)SelectObject(blockDC, BLOCK[2]);

						StretchBlt(memdc, map[i][j].pos.x, map[i][j].pos.y, map[i][j].size.x, map[i][j].size.y, blockDC, 0, 0, 60, 30, SRCCOPY); //1024 * 640


						break;
					}
				}
			}
		}

		 if (PLAY == 1)
		 {
			 for (int i = 0; i < 15; i++)
			 {
				 for (int j = nx / 40; j < 45; j++)
				 {
					 switch (map[i][j].kind)
					 {
					 case block1:
						 oldbit1 = (HBITMAP)SelectObject(blockDC, BLOCK[0]);
						
						 StretchBlt(memdc, map[i][j].pos.x-nx, map[i][j].pos.y, map[i][j].size.x, map[i][j].size.y, blockDC, 0, 0, 90, 30, SRCCOPY); //1024 * 640

						 break;
					 case block2:
						 oldbit1 = (HBITMAP)SelectObject(blockDC, BLOCK[1]);

						 StretchBlt(memdc, map[i][j].pos.x-nx, map[i][j].pos.y, map[i][j].size.x, map[i][j].size.y, blockDC, 0, 0, 90, 30, SRCCOPY); //1024 * 640


						 break;
					 case block3:
						 oldbit1 = (HBITMAP)SelectObject(blockDC, BLOCK[2]);

						 StretchBlt(memdc, map[i][j].pos.x- nx, map[i][j].pos.y, map[i][j].size.x, map[i][j].size.y, blockDC, 0, 0, 60, 30, SRCCOPY); //1024 * 640
						 break;
					 }

				 }
			 }
			 oldbit1 = (HBITMAP)SelectObject(blockDC, bit_hero);

			 StretchBlt(memdc, hero.pos.x, hero.pos.y, hero.size.x, hero.size.y, blockDC, 0, 0, 130, 130, SRCCOPY);
			 hero.view =true;

		 }
		
		 BitBlt(hdc, 0, 0, crt.right, crt.bottom, memdc, 0, 0, SRCCOPY);

		DeleteObject(SelectObject(memdc, hOldBitmap));
		DeleteDC(blockDC);

		DeleteDC(memdc);
		DeleteDC(bitDC[0]);
		DeleteDC(bitDC[1]);
		DeleteDC(bitDC[2]);

		EndPaint(hWnd, &ps);
	}
	
	case WM_COMMAND:
	{
		switch (LOWORD(wParam))
		{
		case ID_LIST:
			if (HIWORD(wParam) == CBN_SELCHANGE)
			{
				selection = SendMessage(hlist, LB_GETCURSEL, 0, 0);

			}
			break;
		case ID_SELECT:
			InvalidateRect(hWnd, NULL, false);

			break;

		case ID_NEXT:
			InvalidateRect(hWnd, NULL, false);
			break;
		case ID_PREV:
			InvalidateRect(hWnd, NULL, false);
			break;

		}

		break;
	}
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

