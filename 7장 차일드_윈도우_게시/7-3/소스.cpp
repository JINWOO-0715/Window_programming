#include <Windows.h>
#include <math.h>
#include<stdio.h>
#include<stdlib.h>
#include <time.h>
#include <string.h>
#include"resource.h"
#pragma comment(lib, "msimg32.lib")

#ifdef UNICODE
#pragma comment(linker, "/entry:wWinMainCRTStartup /subsystem:console") 
#else
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console") 
#endif

#define WINDOW_X 1600
#define WINDOW_Y 800

#define ID_STOP 1
#define ID_MOVE 2
#define ID_SELECT 3
#define ID_DONE 4
#define ID_NEXT 5
#define ID_PREV 6
#define ID_LIST 7000
#define Picture_x 550
#define Picture_y 550
void DrawBitmap(HDC hdc, int x, int y, HBITMAP hBit);
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

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
   HDC hdc, memdc,page_memdc;

   static RECT crt; // 직사각형모양 범위 선언
   PAINTSTRUCT ps;
   static HBITMAP page[10];
   static BITMAP page_bit[10];
   static HBITMAP hBitmap, hOldBitmap;

   HWND hWndChild;

   RECT childrt = { 30, 30, 600, 600 };

   static HWND hButtonLeft, hButtonRight;
   static HWND hEdit, hButtonPaintpan, hListBox;

   static HFONT hFont;
   static HWND hlist;
   static int nx = 0;
   static HWND hButton[5];

   static char Items[][256] = { "1","2","3","4" ,"5" ,"6" ,"7" ,"8" ,"9" };
   static int selection;
   static int selection_index=0;
   static int selection_store[10];

   // 메시지 처리하기
   switch (uMsg)
   {
   case WM_CREATE:
   {
	   
      GetClientRect(hWnd, &crt);

      AdjustWindowRect(&childrt, WS_OVERLAPPEDWINDOW, false);


	page[0]= (HBITMAP)LoadBitmap(g_hInstance, MAKEINTRESOURCE(IDB_BITMAP1));
	page[1] = (HBITMAP)LoadBitmap(g_hInstance, MAKEINTRESOURCE(IDB_BITMAP2));
	page[2] = (HBITMAP)LoadBitmap(g_hInstance, MAKEINTRESOURCE(IDB_BITMAP3));
	page[3] = (HBITMAP)LoadBitmap(g_hInstance, MAKEINTRESOURCE(IDB_BITMAP4));
	page[4] = (HBITMAP)LoadBitmap(g_hInstance, MAKEINTRESOURCE(IDB_BITMAP5));
	page[5] = (HBITMAP)LoadBitmap(g_hInstance, MAKEINTRESOURCE(IDB_BITMAP6));
	page[6] = (HBITMAP)LoadBitmap(g_hInstance, MAKEINTRESOURCE(IDB_BITMAP7));
	page[7] = (HBITMAP)LoadBitmap(g_hInstance, MAKEINTRESOURCE(IDB_BITMAP8));
	page[8] = (HBITMAP)LoadBitmap(g_hInstance, MAKEINTRESOURCE(IDB_BITMAP9));
	    CreateWindow("button", "이동", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON ,
		   900, 300, 50, 50, hWnd, (HMENU)ID_MOVE, g_hInstance, NULL);

	   CreateWindow("button", "선택", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		  900, 200, 50, 50, hWnd, (HMENU)ID_SELECT, g_hInstance, NULL);
	  
	  /*CreateWindow("button", "이동", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
	   900, 300, 50, 50, hWnd, (HMENU)ID_MOVE, g_hInstance, NULL);*/
	  CreateWindow("button", "멈춤", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		  900, 400, 50, 50, hWnd, (HMENU)ID_STOP, g_hInstance, NULL);
	  CreateWindow("button", "완성", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		  900, 500, 50, 50, hWnd, (HMENU)ID_DONE, g_hInstance, NULL);
	   CreateWindow("button", "◀", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		  10, 300, 50, 50, hWnd, (HMENU)ID_PREV, g_hInstance, NULL);
	   CreateWindow("button", "▶", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		   800, 300, 50, 50, hWnd, (HMENU)ID_NEXT, g_hInstance, NULL);
	   hlist= CreateWindow("listbox", NULL, WS_CHILD | WS_VISIBLE |  WS_BORDER | LBS_STANDARD,
		1000,180, 400, 400, hWnd, (HMENU)ID_LIST, g_hInstance, NULL);


		for (int i = 0; i < 10; i++)
		{
			SendMessage(hlist, LB_ADDSTRING, 0, (LPARAM)Items[i]); // 값이 들어그는
			
		}

   }
   break;
   case WM_PAINT:
   {
      hdc = BeginPaint(hWnd, &ps);

      memdc = CreateCompatibleDC(hdc);
      hBitmap = CreateCompatibleBitmap(hdc, crt.right, crt.bottom);
      hOldBitmap = (HBITMAP)SelectObject(memdc, hBitmap);
      FillRect(memdc, &crt, (HBRUSH)GetStockObject(WHITE_BRUSH)); //도화지 색 변경

	  
	  if (selection_store[selection_index-1] == 1)
	  {
		  DrawBitmap(memdc, Picture_x, Picture_y, page[0]);

	  }
	  else if (selection_store[selection_index-1 ] == 2)
	  {
		  DrawBitmap(memdc, Picture_x, Picture_y, page[1]);

	  }
	  else if (selection_store[selection_index-1] == 3)
	  {
		  DrawBitmap(memdc, Picture_x, Picture_y, page[2]);

	  }
	  else if (selection_store[selection_index - 1] == 4)

	  {
		  DrawBitmap(memdc, Picture_x, Picture_y, page[3]);

	  }
	  else if (selection_store[selection_index - 1] == 5)
	  {
		  DrawBitmap(memdc, Picture_x, Picture_y, page[4]);

	  }
	  else if (selection_store[selection_index - 1] == 6)
	  {
		  DrawBitmap(memdc, Picture_x, Picture_y, page[5]);

	  }
	  else if (selection_store[selection_index - 1] == 7)
	  {
		  DrawBitmap(memdc, Picture_x, Picture_y, page[6]);

	  }
	  else if (selection_store[selection_index - 1] == 8)
	  {
		  DrawBitmap(memdc, Picture_x, Picture_y, page[7]);

	  }
	  else if (selection_store[selection_index - 1] == 9)
	  {
		  DrawBitmap(memdc, Picture_x, Picture_y, page[8]);

	  }
	  else  if (selection_store[selection_index - 1] == 10)
	  {
		  DrawBitmap(memdc, Picture_x, Picture_y, page[9]);
	  }


	  printf("%d", selection_index);

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
		   selection_store[selection_index] = selection;
		   InvalidateRect(hWnd, NULL, false);
		   selection_index++;
	
		   break;

	   case ID_NEXT:
		   selection_index++;
		   InvalidateRect(hWnd, NULL, false);
		   break;
	   case ID_PREV:
		   selection_index--;
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

LRESULT CALLBACK ChildWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
   HDC hdc, memdc;
   static RECT c1crt; // 직사각형모양 범위 선언
   PAINTSTRUCT ps;

   static HBITMAP hChildBitmap, hChildOldBitmap;

   static HBRUSH hBrush;
   static HBRUSH hOldBrush;

   switch (uMsg)
   {
   case WM_CREATE:
   {
      GetClientRect(hWnd, &c1crt);
      SetTimer(hWnd, 0, 1, NULL);
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
      hChildBitmap = CreateCompatibleBitmap(hdc, c1crt.right, c1crt.bottom);
      hChildOldBitmap = (HBITMAP)SelectObject(memdc, hChildBitmap);
      FillRect(memdc, &c1crt, (HBRUSH)GetStockObject(GRAY_BRUSH)); //도화지 색 변경

      BitBlt(hdc, 0, 0, c1crt.right, c1crt.bottom, memdc, 0, 0, SRCCOPY);

      DeleteObject(SelectObject(memdc, hChildOldBitmap));
      DeleteDC(memdc);

      EndPaint(hWnd, &ps);
   }
   break;
   case WM_DESTROY:
      PostQuitMessage(0);
      break;
   }

   return DefWindowProc(hWnd, uMsg, wParam, lParam);
}
void DrawBitmap(HDC hdc, int x, int y, HBITMAP hBit)
{
	HDC MemDC;
	HBITMAP OldBitmap;
	int bx, by;
	BITMAP bit;

	MemDC = CreateCompatibleDC(hdc);
	OldBitmap = (HBITMAP)SelectObject(MemDC, hBit);

	GetObject(hBit, sizeof(BITMAP), &bit);
	bx = bit.bmWidth;
	by = bit.bmHeight;

	BitBlt(hdc, 100, 100, bx, by, MemDC, 0, 0, SRCCOPY);

	SelectObject(MemDC, OldBitmap);
	DeleteDC(MemDC);
}

