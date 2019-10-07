#include <stdio.h>
#include <Windows.h>
#include <time.h>
#include <math.h>
#include <atlimage.h>
#include <stdlib.h>
#include "resource.h"

#pragma comment(lib, "msimg32.lib")
#define WINDOW_X 1000
#define WINDOW_Y 1280

#ifdef UNICODE
#pragma comment(linker, "/entry:wWinMainCRTStartup /subsystem:console") 
#else
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console") 
#endif
HINSTANCE g_hInstance;

LPCTSTR lpszClass = "Window Class Name";
LPCTSTR lpszWindowName = "Window Program 5-5";
BOOL CALLBACK Dlg6_1Proc(HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam);
// 함수 선언
LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM IParam);
typedef struct _Brick
{
	bool view = false;
	int shape;
	POINT position; //자신의 위치
	int direction; //자신의 방향 
	CImage sprite_image[6]; // 자신의 이미지 
	POINT sprite_Size;
	int sprite_entirecount;
	int sprite_currentindex;
	int Move_speed;
	int select;
	RECT boundingBox;// 충돌처리
	POINT RealSize; // 실제사이즈
	void init() // 초기화 
	{
		sprite_image[0].Load(TEXT("./1.bmp"));
		sprite_image[1].Load(TEXT("./2.bmp"));
		sprite_image[2].Load(TEXT("./3.bmp"));
		sprite_image[3].Load(TEXT("./4.bmp"));
		sprite_image[4].Load(TEXT("./5.bmp"));
		sprite_image[5].Load(TEXT("./6.bmp"));


		sprite_Size.x = 40;
		sprite_Size.y = 40;
		sprite_entirecount = 1;
		sprite_currentindex = 0;
	
		RealSize.x = 20;
		RealSize.y = 20;

		boundingBox.left = position.x;
		boundingBox.top = position.y;
		boundingBox.right = position.x + RealSize.x;
		boundingBox.bottom = position.y + RealSize.y;
		Move_speed = 20;

	}
	void Draw(HDC hdc, HWND hwnd)
	{
		if (select == 0)
		{
			int SpriteWidth = sprite_image[0].GetWidth() / sprite_Size.x;
			int SpriteHeight = sprite_image[0].GetHeight() / sprite_Size.y;

			int xCoord = sprite_currentindex % SpriteWidth;
			int yCoord = sprite_currentindex / SpriteWidth;

			sprite_image[0].Draw(hdc, position.x, position.y, RealSize.x, RealSize.y,
				xCoord * sprite_Size.x, yCoord * sprite_Size.y, sprite_Size.x, sprite_Size.y);

	}
		if (select == 1)
		{
			int SpriteWidth = sprite_image[1].GetWidth() / sprite_Size.x;
			int SpriteHeight = sprite_image[1].GetHeight() / sprite_Size.y;

			int xCoord = sprite_currentindex % SpriteWidth;
			int yCoord = sprite_currentindex / SpriteWidth;

			sprite_image[1].Draw(hdc, position.x, position.y, RealSize.x, RealSize.y,
				xCoord * sprite_Size.x, yCoord * sprite_Size.y, sprite_Size.x, sprite_Size.y);

		}		if (select == 2)
		{
			int SpriteWidth = sprite_image[2].GetWidth() / sprite_Size.x;
			int SpriteHeight = sprite_image[2].GetHeight() / sprite_Size.y;

			int xCoord = sprite_currentindex % SpriteWidth;
			int yCoord = sprite_currentindex / SpriteWidth;

			sprite_image[2].Draw(hdc, position.x, position.y, RealSize.x, RealSize.y,
				xCoord * sprite_Size.x, yCoord * sprite_Size.y, sprite_Size.x, sprite_Size.y);

		}		if (select == 3)
		{
			int SpriteWidth = sprite_image[3].GetWidth() / sprite_Size.x;
			int SpriteHeight = sprite_image[3].GetHeight() / sprite_Size.y;

			int xCoord = sprite_currentindex % SpriteWidth;
			int yCoord = sprite_currentindex / SpriteWidth;

			sprite_image[3].Draw(hdc, position.x, position.y, RealSize.x, RealSize.y,
				xCoord * sprite_Size.x, yCoord * sprite_Size.y, sprite_Size.x, sprite_Size.y);

		}		if (select == 4)
		{
			int SpriteWidth = sprite_image[4].GetWidth() / sprite_Size.x;
			int SpriteHeight = sprite_image[4].GetHeight() / sprite_Size.y;

			int xCoord = sprite_currentindex % SpriteWidth;
			int yCoord = sprite_currentindex / SpriteWidth;

			sprite_image[4].Draw(hdc, position.x, position.y, RealSize.x, RealSize.y,
				xCoord * sprite_Size.x, yCoord * sprite_Size.y, sprite_Size.x, sprite_Size.y);

		}		if (select == 5)
		{
			int SpriteWidth = sprite_image[5].GetWidth() / sprite_Size.x;
			int SpriteHeight = sprite_image[5].GetHeight() / sprite_Size.y;

			int xCoord = sprite_currentindex % SpriteWidth;
			int yCoord = sprite_currentindex / SpriteWidth;

			sprite_image[5].Draw(hdc, position.x, position.y, RealSize.x, RealSize.y,
				xCoord * sprite_Size.x, yCoord * sprite_Size.y, sprite_Size.x, sprite_Size.y);

		}


	}
	void Update()
	{
		(++sprite_currentindex) %= sprite_entirecount;
		boundingBox.left = position.x;
		boundingBox.top = position.y;
		boundingBox.right = position.x + RealSize.x;
		boundingBox.bottom = position.y + RealSize.y;
		Move();
	
	}
	void Move()
	{
		position.y += Move_speed;
	}

}Brick;
struct COLOR {
	int r;
	int g;
	int b;
	int view;
};
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
HWND hMainWnd;
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
	hMainWnd = hWnd;
	UpdateWindow(hWnd);

	// 이벤트 루프 처리
	while (GetMessage(&Message, 0, 0, 0))
	{
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}
	

	return Message.wParam;
}

Brick block[375];
static bool grid = true;
 int board_y = 20;
 int board_x = 10;
 COLOR  color[8];

 int r = 255, g=255, b = 255;
	 int blockindex;
	static int speed = 150;

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM IParam)
{
	srand((unsigned int)time(NULL));
	HDC hDC, memdc;
	static RECT crt; // 직사각형모양 범위 선언
	PAINTSTRUCT ps;

	static int startX, startY;
	static bool Drag;
	static int endX, endY;
	static HBITMAP hBitmap, hOldBitmap;

	static int choice = 0;

	switch (iMessage)
	{
	case WM_CREATE:
		
		GetClientRect(hWnd, &crt);
		Drag = false;
		for (int i = 0; i < 375; i++)
		{
			block[i].init();

			block[i].position.x = 0;
			block[i].position.y = 0;
		}
		color[0].r = 255;
		color[0].g = 0;
		color[0].b = 0;


		color[1].r = 0;
		color[1].g = 255;
		color[1].b = 0;

		color[2].r = 0;
		color[2].g = 0;
		color[2].b = 255;

		color[3].r = 255;
		color[3].g = 255;
		color[3].b = 0;

		color[4].r = 255;
		color[4].g = 0;
		color[4].b = 255;

		color[5].r = 0;
		color[5].g = 255;
		color[5].b = 255;

		color[6].r = 255;
		color[6].g = 255;
		color[6].b = 255;


		HBRUSH hBrush, oldBrush;
		blockindex = 0;
		block[blockindex].view = true;
		SetTimer(hWnd, 1, speed, NULL);
	
		break;
	case WM_TIMER:

		
		if (block[blockindex].view == true)
		{
			block[blockindex].position.y += block[blockindex].Move_speed;

			InvalidateRect(hWnd, NULL, TRUE);
		}


		if (board_y == 20)
		{
			for (int i = 0; i < blockindex; i++)
			{
				if (block[i].view == true)
				{
					block[i].position.y = 380;
				}
			}
			if (block[blockindex].position.y > 360)
			{
	
			
	
				blockindex++;

				block[blockindex].view = true;
				block[blockindex].select = rand() % 6;

			}
		}

		else if (board_y == 25)
		{
			for (int i = 0; i < blockindex; i++)
			{
				if (block[i].view == true)
				{
					block[i].position.y = 480;
				}
			}
			if (block[blockindex].position.y > 470)
			{
				
				blockindex++;

				block[blockindex].view = true;
				block[blockindex].select = rand() % 6;

				InvalidateRect(hWnd, NULL, TRUE);

			}
		
		}


		SetTimer(hWnd, 1, speed, NULL);

		InvalidateRect(hWnd, NULL, TRUE);
		break;
	case WM_KEYDOWN:
		
		if (wParam == VK_DOWN)
		{
			block[blockindex].position.y += block[blockindex].Move_speed;
		
		}
		else if (wParam == VK_LEFT)
		{
			if (block[blockindex].position.x > 0)
			{
				block[blockindex].position.x -= block[blockindex].Move_speed;
			}

		}

		else if (wParam == VK_RIGHT)
		{
			if (block[blockindex].position.x < 20*board_y)
			{
				block[blockindex].position.x += block[blockindex].Move_speed;
			}
			
		}
		else if(wParam == VK_RETURN)
		{
			DialogBox(g_hInstance, MAKEINTRESOURCE(IDD_DIALOG1), hWnd, Dlg6_1Proc);
		}
			
		InvalidateRect(hWnd, NULL, TRUE);
		break;
	case WM_COMMAND:
		break;
	case WM_PAINT:
		hDC = BeginPaint(hWnd, &ps);
	
		memdc = CreateCompatibleDC(hDC);
		hBitmap = CreateCompatibleBitmap(hDC, crt.right, crt.bottom);
		hOldBitmap = (HBITMAP)SelectObject(memdc, hBitmap);
		Rectangle(memdc, 0, 0, WINDOW_X, WINDOW_Y);
	
		if (grid == true)
		{
			for (int i = 0; i < board_x; i++)
			{
				for (int j = 0; j < board_y; j++)
				{
					hBrush = CreateSolidBrush(RGB(r, g, b));
					oldBrush = (HBRUSH)SelectObject(memdc, hBrush);
					Rectangle(memdc, i * 20, j * 20, (i + 1) * 20, (j + 1) * 20);
					DeleteObject(hBrush);


				}
			}

		}
		
		for (int i = 0; i < 375; i++)
		{
			if (block[i].view == true)
			{
				block[i].Draw(memdc, hWnd);
			}
	
		}


		BitBlt(hDC, 0, 0, crt.right, crt.bottom, memdc, 0, 0, SRCCOPY); // 더블 버퍼링 

		DeleteObject(SelectObject(memdc, hOldBitmap));
		DeleteDC(memdc);

		EndPaint(hWnd, &ps);
		break;

	case WM_DESTROY:

		PostQuitMessage(0);
		return 0;


	}

	return(DefWindowProc(hWnd, iMessage, wParam, IParam));
}


BOOL CALLBACK Dlg6_1Proc(HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	static int selection;
	static HWND hCombo;

	static int gender;
	static HWND hlist;
	switch (iMsg) {
	case WM_INITDIALOG:

		return true;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{

		case ID_GRID_ON:
			grid = true;
			break;
		case ID_GRID_OFF:
			grid = false;
			break;
		case ID_SPEED_LOW:
			speed = 400;

			break;
		case ID_SPEED_MID:
			speed = 150;
			break;
		case ID_SPEED_MAX:
			speed = 50;
			break;
		case ID_BOARD_10:
			board_x = 10;
			board_y = 20;
			break;
		case ID_BOARD_15:
			board_x = 15;
			board_y = 25;
			break;
		case ID_GOTO_LEFT:
			if (block[blockindex].position.x > 0)
			{
				block[blockindex].position.x -= block[blockindex].Move_speed;
			}
			break;
		case ID_GOTO_RIGHT:
			if (block[blockindex].position.x < 20 * board_y)
			{
				block[blockindex].position.x += block[blockindex].Move_speed;
			}
			break;
		case ID_COLOR_1:

			r += 254;
			g += 1;
			b += 1;
			if (r > 255 && g > 254 && b > 254)
			{
				r = 254;
				g = 1;
				b = 1;
			}
			color[0].view = true;
			break;
		case ID_COLOR_2:
			r += 1;
			g += 254;
			b += 1;
			if (r > 255 && g > 254 && b > 254)
			{
				r = 1;
				g = 255;
				b = 1;
			}
			color[1].view = true;
			break;
		case ID_COLOR_3:
			r += 1;
			g += 1;
			b += 254;
			if (r > 254 && g > 254 && b > 254)
			{
				r = 1;
				g = 1;
				b = 255;
			}
			color[0].view = true;
			break;
		case ID_TURN_LEFT:
			if (block[blockindex].select == 1)
			{
				block[blockindex].select = 0;
			}
			else if (block[blockindex].select == 0)
			{
				block[blockindex].select = 1;
			}

			else if (block[blockindex].select == 2)
			{
				block[blockindex].select = 3;
			}
			else if (block[blockindex].select == 3)
			{
				block[blockindex].select = 4;
			}
			else if (block[blockindex].select == 4)
			{
				block[blockindex].select = 5;
			}
			else if (block[blockindex].select == 5)
			{
				block[blockindex].select = 3;
			}
			break;
		case ID_TURN_RIGHT:
			if (block[blockindex].select == 1)
			{
				block[blockindex].select = 0;

			}
			else if (block[blockindex].select == 0)
			{
				block[blockindex].select = 1;
			}

			else if (block[blockindex].select == 5)
			{
				block[blockindex].select = 4;
			}
			else if (block[blockindex].select == 4)
			{
				block[blockindex].select = 3;
			}
			else if (block[blockindex].select == 3)
			{
				block[blockindex].select = 2;
			}
			else if (block[blockindex].select == 2)
			{
				block[blockindex].select = 5;
			}
			break;
		case ID_EXIT:
			EndDialog(hDlg, 0);

			break;
		}
		break;
	}
	return 0;
}