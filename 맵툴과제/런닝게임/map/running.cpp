#include <windows.h> // 윈도우 헤더 파일
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <crtdbg.h>
#include "resource.h"

#define ob_1 69870
#define ob_2 69871
#define ob_3 69872
#define ob_4 69873


#define mon_1 69874
#define mon_2 69876
#define mon_3 69875
#define mon_4 69877

#define item_1 69878
#define item_2 69879
#define item_3 69880
#define item_4 69881


#ifdef UNICODE
#pragma comment(linker, "/entry:wWinMainCRTStartup /subsystem:console") 
#else
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console") 
#endif


#pragma warning(disable : 4996)


HINSTANCE g_hInst;

LPCTSTR lpszClass = "Window Class Name";
LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);


LRESULT CALLBACK ChildProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK Dlg6_1Proc(HWND, UINT, WPARAM, LPARAM);

int x = 1200, y = 800;
HWND hMainWnd;

int tile_y = 15;
int tile_x = 8;
int map_x = 500;
int map_y = 500;
static int bit_size_x, bit_size_y;
static bool mapview = false;
static int selection = 0;

struct MAP
{
	POINT pos;
	POINT size;
	int kind;
	bool viwe = false;
	bool monster_view = false;
	int monster_type;
	MAP& operator = (const MAP& rhs)
	{
		pos = rhs.pos;
		size = rhs.size;
		kind = rhs.kind;
	}


};
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

bool Crush(MAP  r, MAP r2)
{
	if ((r.pos.x < (r2.pos.x + r2.size.x)) && (r.pos.y < (r2.pos.y + r2.size.y)) && ((r.pos.x + r.size.x) > r2.pos.x) && ((r.pos.y + r.size.y) > r2.pos.y))
	{
		return true;
	}
	else
	{
		return false;
	}
}
MAP ** map;
int Current_kind;
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,

	LPSTR lpszCmdParam, int nCmdShow)

{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF); // 메모리 누수 체크
	HWND hWnd;

	MSG Message;

	WNDCLASSEX WndClass;

	g_hInst = hInstance;

	WndClass.cbSize = sizeof(WndClass);

	WndClass.style = CS_HREDRAW | CS_VREDRAW;

	WndClass.lpfnWndProc = (WNDPROC)WndProc;

	WndClass.cbClsExtra = 0;

	WndClass.cbWndExtra = 0;

	WndClass.hInstance = hInstance;

	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);


	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);

	WndClass.hbrBackground =

		(HBRUSH)GetStockObject(WHITE_BRUSH);

	WndClass.lpszMenuName = MAKEINTRESOURCE(IDR_MENU1);


	WndClass.lpszClassName = lpszClass;

	WndClass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	RegisterClassEx(&WndClass);

	WndClass.hCursor = LoadCursor(NULL, IDC_HELP);
	WndClass.hbrBackground = (HBRUSH)GetStockObject(GRAY_BRUSH);
	WndClass.lpszClassName = "ChildClass"; // 차일드 윈도우 클래스 이름
	WndClass.lpfnWndProc = ChildProc; // 차일드 윈도우 프로시저 지정
	RegisterClassEx(&WndClass); // 자식 윈도우 클래스를 등록

	hMainWnd = CreateWindow

	(lpszClass, "windows program 1 - 1",

		WS_OVERLAPPEDWINDOW,

		0, 0, x, y,

		NULL, (HMENU)NULL,

		hInstance, NULL);

	ShowWindow(hMainWnd, nCmdShow);

	UpdateWindow(hMainWnd);

	while (GetMessage(&Message, 0, 0, 0)) {

		TranslateMessage(&Message);

		DispatchMessage(&Message);

	}

	return Message.wParam;

}
LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{

	PAINTSTRUCT ps;
	HBRUSH hBrush1, oldBrush;
	HDC hDC, memDC, bitDC;
	static HBITMAP hBitmap1, hBitmap2, oldbit1, oldbit2;
	HPEN hPen, oldPen;
	static HBITMAP hBit_OBJECT[4], hBit_ITEM[4], hBit_MONSTER[4], hBit_BackGround[3];
	HWND hDlg = NULL;
	POINT g_Pos;

	POINT mouse;
	static int radian = 25;
	switch (iMessage)
	{
	case WM_CREATE:


		hBit_OBJECT[0] = LoadBitmap(g_hInst, MAKEINTRESOURCE(ID_OBJECT_1)); // 비트맵 로드

		hBit_OBJECT[1] = LoadBitmap(g_hInst, MAKEINTRESOURCE(ID_OBJECT_2)); // 비트맵 로드

		hBit_OBJECT[2] = LoadBitmap(g_hInst, MAKEINTRESOURCE(ID_OBJECT_3)); // 비트맵 로드

		hBit_OBJECT[3] = LoadBitmap(g_hInst, MAKEINTRESOURCE(ID_OBJECT_4)); // 비트맵 로드

		hBit_ITEM[0] = LoadBitmap(g_hInst, MAKEINTRESOURCE(ID_ITEM_1)); // 비트맵 로드

		hBit_ITEM[1] = LoadBitmap(g_hInst, MAKEINTRESOURCE(ID_ITEM_2)); // 비트맵 로드

		hBit_ITEM[2] = LoadBitmap(g_hInst, MAKEINTRESOURCE(ID_ITEM_3)); // 비트맵 로드

		hBit_ITEM[3] = LoadBitmap(g_hInst, MAKEINTRESOURCE(ID_ITEM_4)); // 비트맵 로드

		hBit_MONSTER[0] = LoadBitmap(g_hInst, MAKEINTRESOURCE(ID_MONSTER_1)); // 비트맵 로드

		hBit_MONSTER[1] = LoadBitmap(g_hInst, MAKEINTRESOURCE(ID_MONSTER_2)); // 비트맵 로드

		hBit_MONSTER[2] = LoadBitmap(g_hInst, MAKEINTRESOURCE(ID_MONSTER_3)); // 비트맵 로드

		hBit_MONSTER[3] = LoadBitmap(g_hInst, MAKEINTRESOURCE(ID_MONSTER_4)); // 비트맵 로드

		hBit_BackGround[0] = LoadBitmap(g_hInst, MAKEINTRESOURCE(ID_BACKGROUND_1));

		hBit_BackGround[1] = LoadBitmap(g_hInst, MAKEINTRESOURCE(ID_BACKGROUND_2));

		hBit_BackGround[2] = LoadBitmap(g_hInst, MAKEINTRESOURCE(ID_BACKGROUND_3));
		SetTimer(hWnd, 0, 1, NULL);

		break;
	case WM_CHAR:
	{
		InvalidateRect(hWnd, NULL, FALSE);
		break;
	}
	case WM_KEYDOWN:
	{


		InvalidateRect(hWnd, NULL, FALSE);
		break;
	}
	case WM_LBUTTONDOWN:
	{
		mouse.x = LOWORD(lParam);
		mouse.y = HIWORD(lParam);
		if (map)
		{
			for (int i = 0; i < tile_y; i++) // 그리드 (타일 그리기)
			{
				for (int j = 0; j < tile_x; j++)
				{
					if (map[i])
					{
						if (IsPointinRecTangle(mouse, map[i][j]))
						{
							map[i][j].kind = Current_kind;

						}


					}


				}
			}
		}


	}
	case WM_RBUTTONDOWN:
	{



		InvalidateRect(hWnd, NULL, FALSE);
		break;
	}

	case WM_TIMER:
	{ // 시간이 경과하면 메시지 자동 생성


		InvalidateRgn(hWnd, NULL, FALSE);
		break;
	}
	case WM_COMMAND:
		switch (LOWORD(wParam))

	case ID_DIA_OPEN:
		hDlg = CreateDialog(g_hInst, MAKEINTRESOURCE(IDD_DIALOG1), hWnd, (DLGPROC)Dlg6_1Proc);
		ShowWindow(hDlg, SW_SHOW);
		break;
	case ID_DIA_CLOSE:


		break;
	case WM_PAINT:
	{

		hDC = BeginPaint(hWnd, &ps);
		memDC = CreateCompatibleDC(hDC); // 주어진 DC와 호환되는 DC를 생성


		hBitmap1 = CreateCompatibleBitmap(hDC, x, y);
		oldbit1 = (HBITMAP)SelectObject(memDC, hBitmap1);
		Rectangle(memDC, 0, 0, x, y);

		bitDC = CreateCompatibleDC(memDC);


		if (selection == 0)
		{

			if (mapview == true)
			{
				SelectObject(bitDC, hBit_BackGround[0]);

				StretchBlt(memDC, 0, 0, map_x, map_y, bitDC, 0, 0, 1024, 640, SRCCOPY); //1024 * 640

			}


		}
		else if (selection == 1)
		{

			if (mapview == true)
			{
				SelectObject(bitDC, hBit_BackGround[1]);

				StretchBlt(memDC, 0, 0, map_x, map_y, bitDC, 0, 0, 1024, 640, SRCCOPY); //1024 * 640

			}


		}
		else if (selection == 2)
		{


			if (mapview == true)
			{
				SelectObject(bitDC, hBit_BackGround[2]);
				StretchBlt(memDC, 0, 0, map_x, map_y, bitDC, 0, 0, 1024, 640, SRCCOPY); //1024 * 640

			}


		}


		for (int j = 0; j < tile_y; j++)
		{
			for (int i = 0; i < tile_x; i++)
			{
				hBrush1 = (HBRUSH)GetStockObject(NULL_BRUSH);
				oldBrush = (HBRUSH)SelectObject(memDC, hBrush1);

				int x = (map_x / tile_x);
				int y = (map_y / tile_y);

				Rectangle(memDC, i * x, j * y, (i + 1) * x, (j + 1) * y);

				SelectObject(memDC, oldBrush);
				DeleteObject(hBrush1);
			}
		}


		if (map)
		{
			for (int i = 0; i < tile_y; i++) // 그리드 (타일 그리기)
			{
				for (int j = 0; j < tile_x; j++)
				{


					/*int x = (map_x / tile_x);
					int y = (map_y / tile_y);
					map[i][j].pos.x = i * x;
					map[i][j].pos.y = j * y;
					map[i][j].size.x = x;
					map[i][j].size.y = y;*/
					switch (map[i][j].kind)
					{
					case ob_1:

						oldbit1 = (HBITMAP)SelectObject(bitDC, hBit_OBJECT[0]);

						StretchBlt(memDC, map[i][j].pos.x, map[i][j].pos.y, map[i][j].size.x, map[i][j].size.y, bitDC, 0, 0, 120, 120, SRCCOPY); //1024 * 640


						break;
					case ob_2:

						oldbit1 = (HBITMAP)SelectObject(bitDC, hBit_OBJECT[1]);

						StretchBlt(memDC, map[i][j].pos.x, map[i][j].pos.y, map[i][j].size.x, map[i][j].size.y, bitDC, 0, 0, 120, 120, SRCCOPY); //1024 * 640
						map[i][j].viwe = true;
						break;
					case ob_3:

						oldbit1 = (HBITMAP)SelectObject(bitDC, hBit_OBJECT[2]);

						StretchBlt(memDC, map[i][j].pos.x, map[i][j].pos.y, map[i][j].size.x, map[i][j].size.y, bitDC, 0, 0, 120, 120, SRCCOPY); //1024 * 640

						break;
					case ob_4:

						oldbit1 = (HBITMAP)SelectObject(bitDC, hBit_OBJECT[3]);

						StretchBlt(memDC, map[i][j].pos.x, map[i][j].pos.y, map[i][j].size.x, map[i][j].size.y, bitDC, 0, 0, 120, 120, SRCCOPY); //1024 * 640
						map[i][j].viwe = true;
						break;
					case mon_1:

						oldbit1 = (HBITMAP)SelectObject(bitDC, hBit_MONSTER[0]);

						StretchBlt(memDC, map[i][j].pos.x, map[i][j].pos.y, map[i][j].size.x, map[i][j].size.y, bitDC, 0, 0, 90, 90, SRCCOPY); //1024 * 640


						break;
					case mon_2:

						oldbit1 = (HBITMAP)SelectObject(bitDC, hBit_MONSTER[1]);

						StretchBlt(memDC, map[i][j].pos.x, map[i][j].pos.y, map[i][j].size.x, map[i][j].size.y, bitDC, 0, 0, 90, 90, SRCCOPY); //1024 * 640
						map[i][j].viwe = true;
						map[i][j].monster_view = true;
						map[i][j].monster_type = 1;
						break;
					case mon_3:

						oldbit1 = (HBITMAP)SelectObject(bitDC, hBit_MONSTER[2]);

						StretchBlt(memDC, map[i][j].pos.x, map[i][j].pos.y, map[i][j].size.x, map[i][j].size.y, bitDC, 0, 0, 90, 90, SRCCOPY); //1024 * 640
						map[i][j].viwe = true;
						map[i][j].monster_view = true;
						map[i][j].monster_type = 2;
						break;
					case mon_4:

						oldbit1 = (HBITMAP)SelectObject(bitDC, hBit_MONSTER[3]);

						StretchBlt(memDC, map[i][j].pos.x, map[i][j].pos.y, map[i][j].size.x, map[i][j].size.y, bitDC, 0, 0, 90, 90, SRCCOPY); //1024 * 640
						map[i][j].viwe = true;
						map[i][j].monster_view = true;
						map[i][j].monster_type = 2;
						break;
					case item_1:

						oldbit1 = (HBITMAP)SelectObject(bitDC, hBit_ITEM[0]);

						StretchBlt(memDC, map[i][j].pos.x, map[i][j].pos.y, map[i][j].size.x, map[i][j].size.y, bitDC, 0, 0, 90, 90, SRCCOPY); //1024 * 640
						map[i][j].viwe = true;
						break;
					case item_2:

						oldbit1 = (HBITMAP)SelectObject(bitDC, hBit_ITEM[1]);

						StretchBlt(memDC, map[i][j].pos.x, map[i][j].pos.y, map[i][j].size.x, map[i][j].size.y, bitDC, 0, 0, 90, 90, SRCCOPY); //1024 * 640
						map[i][j].viwe = true;
						break;
					case item_3:

						oldbit1 = (HBITMAP)SelectObject(bitDC, hBit_ITEM[2]);

						StretchBlt(memDC, map[i][j].pos.x, map[i][j].pos.y, map[i][j].size.x, map[i][j].size.y, bitDC, 0, 0, 90, 90, SRCCOPY); //1024 * 640
						map[i][j].viwe = true;
						break;
					case item_4:

						oldbit1 = (HBITMAP)SelectObject(bitDC, hBit_ITEM[3]);

						StretchBlt(memDC, map[i][j].pos.x, map[i][j].pos.y, map[i][j].size.x, map[i][j].size.y, bitDC, 0, 0, 90, 90, SRCCOPY); //1024 * 640
						map[i][j].viwe = true;
						break;


					}

				}
			}

		}

		SelectObject(bitDC, oldbit1);

		BitBlt(hDC, 0, 0, 1200, 800, memDC, 0, 0, SRCCOPY);

		SelectObject(memDC, hBitmap1);
		DeleteDC(bitDC);
		DeleteDC(memDC);
		DeleteObject(hBitmap1);

		EndPaint(hWnd, &ps);
		break;
	}

	case WM_DESTROY:
	{

		if (map)
		{
			for (int i = 0; i < tile_y; i++)
			{
				if (map[i] != nullptr)
				{
					free(map[i]);
					map[i] = nullptr;
				}
			}
			if (map != nullptr)
			{
				free(map);
				map = nullptr;
			}
		}

		HideCaret(hWnd);
		DestroyCaret();
		KillTimer(hWnd, 1);
		PostQuitMessage(0);

		return 0;
	}
	}

	return(DefWindowProc(hWnd, iMessage, wParam, lParam));

}
BOOL CALLBACK Dlg6_1Proc(HWND hDlg, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	static HWND hlist;
	FILE *fr;
	FILE *fw;
	OPENFILENAME OFN;
	TCHAR str2[100], lpstrFile2[100] = "";
	TCHAR filter[100] = "텍스트 파일(*.txt)\0 *.txt; \0 문서 File \0 * .txt; *.doc \0";
	OPENFILENAME SFN;
	TCHAR str3[100], lpstrFile3[100] = "";
	char name[] = "BackGroun_1";
	char name2[] = "BackGroun_2";
	char name3[] = "BackGroun_3";
	TCHAR filter2[100] = "텍스트 파일(*.txt)\0 *.txt; \0 문서 File \0 * .txt; *.doc \0";

	switch (iMessage)
	{
		HBITMAP hBit_OBJECT[4], hBit_ITEM[4], hBit_MONSTER[4], hBit_BackGround[3];
		HWND hButton_OBJECT[4], hButton_ITEM[4], hButton_MONSTER[4];

	case WM_INITDIALOG:
	{

		hlist = GetDlgItem(hDlg, IDC_LIST1);

		SendMessage(hlist, LB_ADDSTRING, 0, (LPARAM)name);
		SendMessage(hlist, LB_ADDSTRING, 0, (LPARAM)name2);
		SendMessage(hlist, LB_ADDSTRING, 0, (LPARAM)name3);

		hBit_OBJECT[0] = LoadBitmap(g_hInst, MAKEINTRESOURCE(ID_OBJECT_1)); // 비트맵 로드
		hButton_OBJECT[0] = GetDlgItem(hDlg, ID_OBJECT1);
		SendMessage(hButton_OBJECT[0], BM_SETIMAGE, 0, (LPARAM)hBit_OBJECT[0]);

		hBit_OBJECT[1] = LoadBitmap(g_hInst, MAKEINTRESOURCE(ID_OBJECT_2)); // 비트맵 로드
		hButton_OBJECT[1] = GetDlgItem(hDlg, ID_OBJECT2);
		SendMessage(hButton_OBJECT[1], BM_SETIMAGE, 0, (LPARAM)hBit_OBJECT[1]);

		hBit_OBJECT[2] = LoadBitmap(g_hInst, MAKEINTRESOURCE(ID_OBJECT_3)); // 비트맵 로드
		hButton_OBJECT[2] = GetDlgItem(hDlg, ID_OBJECT3);
		SendMessage(hButton_OBJECT[2], BM_SETIMAGE, 0, (LPARAM)hBit_OBJECT[2]);

		hBit_OBJECT[3] = LoadBitmap(g_hInst, MAKEINTRESOURCE(ID_OBJECT_4)); // 비트맵 로드
		hButton_OBJECT[3] = GetDlgItem(hDlg, ID_OBJECT4);
		SendMessage(hButton_OBJECT[3], BM_SETIMAGE, 0, (LPARAM)hBit_OBJECT[3]);

		hBit_ITEM[0] = LoadBitmap(g_hInst, MAKEINTRESOURCE(ID_ITEM_1)); // 비트맵 로드
		hButton_ITEM[0] = GetDlgItem(hDlg, ID_ITEM1);
		SendMessage(hButton_ITEM[0], BM_SETIMAGE, 0, (LPARAM)hBit_ITEM[0]);

		hBit_ITEM[1] = LoadBitmap(g_hInst, MAKEINTRESOURCE(ID_ITEM_2)); // 비트맵 로드
		hButton_ITEM[1] = GetDlgItem(hDlg, ID_ITEM2);
		SendMessage(hButton_ITEM[1], BM_SETIMAGE, 0, (LPARAM)hBit_ITEM[1]);

		hBit_ITEM[2] = LoadBitmap(g_hInst, MAKEINTRESOURCE(ID_ITEM_3)); // 비트맵 로드
		hButton_ITEM[2] = GetDlgItem(hDlg, ID_ITEM3);
		SendMessage(hButton_ITEM[2], BM_SETIMAGE, 0, (LPARAM)hBit_ITEM[2]);

		hBit_ITEM[3] = LoadBitmap(g_hInst, MAKEINTRESOURCE(ID_ITEM_4)); // 비트맵 로드
		hButton_ITEM[3] = GetDlgItem(hDlg, ID_ITEM4);
		SendMessage(hButton_ITEM[3], BM_SETIMAGE, 0, (LPARAM)hBit_ITEM[3]);

		hBit_MONSTER[0] = LoadBitmap(g_hInst, MAKEINTRESOURCE(ID_MONSTER_1)); // 비트맵 로드
		hButton_MONSTER[0] = GetDlgItem(hDlg, ID_MONSTER1);
		SendMessage(hButton_MONSTER[0], BM_SETIMAGE, 0, (LPARAM)hBit_MONSTER[0]);

		hBit_MONSTER[1] = LoadBitmap(g_hInst, MAKEINTRESOURCE(ID_MONSTER_2)); // 비트맵 로드
		hButton_MONSTER[1] = GetDlgItem(hDlg, ID_MONSTER2);
		SendMessage(hButton_MONSTER[1], BM_SETIMAGE, 0, (LPARAM)hBit_MONSTER[1]);

		hBit_MONSTER[2] = LoadBitmap(g_hInst, MAKEINTRESOURCE(ID_MONSTER_3)); // 비트맵 로드
		hButton_MONSTER[2] = GetDlgItem(hDlg, ID_MONSTER3);
		SendMessage(hButton_MONSTER[2], BM_SETIMAGE, 0, (LPARAM)hBit_MONSTER[2]);

		hBit_MONSTER[3] = LoadBitmap(g_hInst, MAKEINTRESOURCE(ID_MONSTER_4)); // 비트맵 로드
		hButton_MONSTER[3] = GetDlgItem(hDlg, ID_MONSTER4);
		SendMessage(hButton_MONSTER[3], BM_SETIMAGE, 0, (LPARAM)hBit_MONSTER[3]);

		hBit_BackGround[0] = LoadBitmap(g_hInst, MAKEINTRESOURCE(ID_BACKGROUND_1));
		hBit_BackGround[1] = LoadBitmap(g_hInst, MAKEINTRESOURCE(ID_BACKGROUND_2));
		hBit_BackGround[2] = LoadBitmap(g_hInst, MAKEINTRESOURCE(ID_BACKGROUND_3));

		break;

	}
	case WM_COMMAND:
	{

		switch (LOWORD(wParam))
		{


		case ID_GRID_SIZE_X:
			break;
		case ID_GRID_SIZE_Y:

			break;
		case ID_MAP_SIZE_X:
			break;
		case ID_MAP_SIZE_Y:
			break;
		case ID_ITEM1:
			Current_kind = item_1;
			break;
		case ID_ITEM2:
			Current_kind = item_2;
			break;
		case ID_ITEM3:
			Current_kind = item_3;
			break;
		case ID_ITEM4:
			Current_kind = item_4;
			break;
		case ID_MONSTER1:
			Current_kind = mon_1;
			break;
		case ID_MONSTER2:
			Current_kind = mon_2;
			break;
		case ID_MONSTER3:
			Current_kind = mon_3;
			break;
		case ID_MONSTER4:
			Current_kind = mon_4;
			break;
		case ID_OBJECT1:
			Current_kind = ob_1;
			break;
		case ID_OBJECT2:
			Current_kind = ob_2;
			break;
		case ID_OBJECT3:
			Current_kind = ob_3;
			break;
		case ID_OBJECT4:
			Current_kind = ob_4;
			break;
		case ID_SAVE:
			memset(&SFN, 0, sizeof(OPENFILENAME)); // 초기화
			SFN.lStructSize = sizeof(OPENFILENAME);
			SFN.hwndOwner = hDlg;
			SFN.lpstrFilter = filter2;
			SFN.lpstrFile = lpstrFile3;
			SFN.nMaxFile = 256;
			SFN.lpstrInitialDir = ".";
			if (GetSaveFileName(&SFN) != 0)
			{
				wsprintf(str3, "%s 파일에 저장하시겠습니까 ?", SFN.lpstrFile);
				MessageBox(hDlg, str3, "저장하기 선택", MB_OK);
				fw = fopen(SFN.lpstrFile, "w");
				fprintf(fw, " %d", map_y);
				fprintf(fw, " %d", map_x);
				fprintf(fw, " %d", tile_x);
				fprintf(fw, " %d", tile_y);
				fprintf(fw, " %d", mapview);
				fprintf(fw, " %d", selection);
				for (int i = 0; i < tile_y; i++) // 그리드 (타일 그리기)
				{
					for (int j = 0; j < tile_x; j++)
					{
						if (map[i])
						{

							fprintf(fw, " %d %d %d %d %d\n", map[i][j].pos.x, map[i][j].pos.y, map[i][j].size.x, map[i][j].size.y, map[i][j].kind);

						}


					}

				}


				fclose(fw);

			}
			break;

		case ID_OPEN:
			memset(&OFN, 0, sizeof(OPENFILENAME)); // 초기화
			OFN.lStructSize = sizeof(OPENFILENAME);
			OFN.hwndOwner = hDlg;
			OFN.lpstrFilter = filter;
			OFN.lpstrFile = lpstrFile2;
			OFN.nMaxFile = 256;
			OFN.lpstrInitialDir = "."; // 초기 디렉토리
			if (GetOpenFileName(&OFN) != 0)
			{

				wsprintf(str2, "%s 파일을 여시겠습니까 ?", OFN.lpstrFile);
				MessageBox(hDlg, str2, "열기 선택", MB_OK);
				fr = fopen(OFN.lpstrFile, "r");
				fscanf(fr, " %d", &map_y);
				fscanf(fr, " %d", &map_x);
				fscanf(fr, " %d", &tile_x);
				fscanf(fr, " %d", &tile_y);
				fscanf(fr, " %d", &mapview);
				fscanf(fr, " %d", &selection);

				if (map)
				{
					for (int i = 0; i < tile_y; i++)
					{
						if (map[i] != nullptr)
						{
							free(map[i]);
							map[i] = nullptr;
						}
					}
					if (map != nullptr)
					{
						free(map);
						map = nullptr;
					}
				}



				if (map == nullptr)
				{
					map = (MAP**)malloc(sizeof(MAP*)*tile_y);

					for (int i = 0; i < tile_y; i++)
					{
						map[i] = (MAP*)malloc(sizeof(MAP)*tile_x);
					}
				}
				int x = (map_x / tile_x);
				int y = (map_y / tile_y);

				for (int i = 0; i < tile_y; i++) // 그리드 (타일 그리기)
				{
					for (int j = 0; j < tile_x; j++)
					{
						if (map[i])
						{

							fscanf(fr, " %d %d %d %d %d\n", &map[i][j].pos.x, &map[i][j].pos.y, &map[i][j].size.x, &map[i][j].size.y, &map[i][j].kind);

						}


					}

				}
				fclose(fr);
			}
			break;
		case IDC_LIST1:  // 리스트 박스 
			if (HIWORD(wParam) == CBN_SELCHANGE)
			{
				selection = SendMessage(hlist, LB_GETCURSEL, 0, 0);
			}
			break;

		case ID_DONE:
		{

			if (map)
			{
				for (int i = 0; i < tile_y; i++)
				{
					if (map[i] != nullptr)
					{
						free(map[i]);
						map[i] = nullptr;
					}
				}
				if (map != nullptr)
				{
					free(map);
					map = nullptr;
				}
			}

			map_x = GetDlgItemInt(hDlg, ID_MAP_SIZE_X, NULL, TRUE);
			map_y = GetDlgItemInt(hDlg, ID_MAP_SIZE_Y, NULL, TRUE);
			tile_x = GetDlgItemInt(hDlg, ID_GRID_SIZE_X, NULL, TRUE);
			tile_y = GetDlgItemInt(hDlg, ID_GRID_SIZE_Y, NULL, TRUE);


			if (map == nullptr)
			{
				map = (MAP**)malloc(sizeof(MAP*)*tile_y);

				for (int i = 0; i < tile_y; i++)
				{
					map[i] = (MAP*)malloc(sizeof(MAP)*tile_x);
				}
			}
			int x = (map_x / tile_x);
			int y = (map_y / tile_y);

			for (int i = 0; i < tile_y; i++) // 그리드 (타일 그리기)
			{
				for (int j = 0; j < tile_x; j++)
				{
					map[i][j].pos.x = i * x;
					map[i][j].pos.y = j * y;
					map[i][j].size.x = x;
					map[i][j].size.y = y;

				}
			}

			mapview = true;

			break;
		}
		case ID_GRID_ON:
			break;
		case ID_GRID_OFF:
			break;
		case ID_EXIT:
			EndDialog(hDlg, 0);
			break;
		case ID_TEST:


			CreateWindow("ChildClass", NULL, WS_POPUP | WS_VISIBLE,
				800, 0, map_x, map_y, hMainWnd, NULL, g_hInst, NULL);
			break;

		}
	}
	break;
	}

	return 0;
}


LRESULT CALLBACK ChildProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{

	PAINTSTRUCT ps;
	HBRUSH hBrush1, oldBrush;
	HDC hDC, memDC, bitDC;
	static HBITMAP hBitmap1, hBitmap2, oldbit1, oldbit2;
	HPEN hPen, oldPen;
	static HBITMAP hBit_OBJECT[4], hBit_ITEM[4], hBit_MONSTER[4], hBit_BackGround[3], hBit_Hero;
	HWND hDlg = NULL;
	POINT g_Pos;
	POINT mouse;
	static int move_count;
	static int Monsterindex = 0;
	static MAP hero;
	static int radian = 25;
	switch (iMessage)
	{
	case WM_CREATE:


		hBit_Hero = LoadBitmap(g_hInst, MAKEINTRESOURCE(ID_HERO));
		hero.pos.x = 50;
		hero.pos.y = 50;

		hBit_OBJECT[0] = LoadBitmap(g_hInst, MAKEINTRESOURCE(ID_OBJECT_1)); // 비트맵 로드

		hBit_OBJECT[1] = LoadBitmap(g_hInst, MAKEINTRESOURCE(ID_OBJECT_2)); // 비트맵 로드

		hBit_OBJECT[2] = LoadBitmap(g_hInst, MAKEINTRESOURCE(ID_OBJECT_3)); // 비트맵 로드

		hBit_OBJECT[3] = LoadBitmap(g_hInst, MAKEINTRESOURCE(ID_OBJECT_4)); // 비트맵 로드

		hBit_ITEM[0] = LoadBitmap(g_hInst, MAKEINTRESOURCE(ID_ITEM_1)); // 비트맵 로드

		hBit_ITEM[1] = LoadBitmap(g_hInst, MAKEINTRESOURCE(ID_ITEM_2)); // 비트맵 로드

		hBit_ITEM[2] = LoadBitmap(g_hInst, MAKEINTRESOURCE(ID_ITEM_3)); // 비트맵 로드

		hBit_ITEM[3] = LoadBitmap(g_hInst, MAKEINTRESOURCE(ID_ITEM_4)); // 비트맵 로드

		hBit_MONSTER[0] = LoadBitmap(g_hInst, MAKEINTRESOURCE(ID_MONSTER_1)); // 비트맵 로드

		hBit_MONSTER[1] = LoadBitmap(g_hInst, MAKEINTRESOURCE(ID_MONSTER_2)); // 비트맵 로드

		hBit_MONSTER[2] = LoadBitmap(g_hInst, MAKEINTRESOURCE(ID_MONSTER_3)); // 비트맵 로드

		hBit_MONSTER[3] = LoadBitmap(g_hInst, MAKEINTRESOURCE(ID_MONSTER_4)); // 비트맵 로드

		hBit_BackGround[0] = LoadBitmap(g_hInst, MAKEINTRESOURCE(ID_BACKGROUND_1));

		hBit_BackGround[1] = LoadBitmap(g_hInst, MAKEINTRESOURCE(ID_BACKGROUND_2));

		hBit_BackGround[2] = LoadBitmap(g_hInst, MAKEINTRESOURCE(ID_BACKGROUND_3));
		SetTimer(hWnd, 0, 1, NULL);

		break;
	case WM_CHAR:
	{
		InvalidateRect(hWnd, NULL, FALSE);
		break;
	}
	case WM_KEYDOWN:
	{



		InvalidateRect(hWnd, NULL, FALSE);
		break;
	}
	case WM_LBUTTONDOWN:
	{
		mouse.x = LOWORD(lParam);
		mouse.y = HIWORD(lParam);
		if (map)
		{
			for (int i = 0; i < tile_y; i++) // 그리드 (타일 그리기)
			{
				for (int j = 0; j < tile_x; j++)
				{
					if (map[i])
					{
						if (IsPointinRecTangle(mouse, map[i][j]))
						{
							map[i][j].kind = Current_kind;

						}


					}


				}
			}
		}


	}
	case WM_RBUTTONDOWN:
	{



		InvalidateRect(hWnd, NULL, FALSE);
		break;
	}

	case WM_TIMER:
	{ // 시간이 경과하면 메시지 자동 생성

		if (GetAsyncKeyState('W') & 0x8000 || GetAsyncKeyState('w') & 0x8000)
		{
			hero.pos.y -= 10;
		}
		else if (GetAsyncKeyState('S') & 0x8000 || GetAsyncKeyState('s') & 0x8000)
		{
			hero.pos.y += 10;

		}
		else if (GetAsyncKeyState('D') & 0x8000 || GetAsyncKeyState('d') & 0x8000)
		{
			hero.pos.x += 10;
		}
		else if (GetAsyncKeyState('A') & 0x8000 || GetAsyncKeyState('a') & 0x8000)
		{
			hero.pos.x -= 10;
		}


		for (int i = 0; i < tile_y; i++) // 그리드 (타일 그리기)
		{
			for (int j = 0; j < tile_x; j++)
			{
				if (Crush(map[i][j], hero))
				{

					if (map[i][j].viwe == true)
					{

						if (GetAsyncKeyState('W') & 0x8000 || GetAsyncKeyState('w') & 0x8000)
						{
							hero.pos.y += 10;
						}
						else if (GetAsyncKeyState('S') & 0x8000 || GetAsyncKeyState('s') & 0x8000)
						{
							hero.pos.y -= 10;

						}
						else if (GetAsyncKeyState('D') & 0x8000 || GetAsyncKeyState('d') & 0x8000)
						{
							hero.pos.x -= 10;
						}
						else if (GetAsyncKeyState('A') & 0x8000 || GetAsyncKeyState('a') & 0x8000)
						{
							hero.pos.x += 10;
						}
					}
				}
				if (map[i][j].monster_view == true && map[i][j].monster_type == 1)
				{
					if ((map[i][j].pos.x + map[i][j].size.x) < (map_x) && move_count == 1)
					{
						map[i][j].pos.x += 1;
						if ((map[i][j].pos.x + map[i][j].size.x) == (map_x))
						{
							move_count = 0;
						}

					}
					else
					{
						map[i][j].pos.x -= 1;
						if (map[i][j].pos.x == 1)
						{
							move_count = 1;
						}
					}

				}
				if (map[i][j].monster_view == true && map[i][j].monster_type == 2)
				{
					if (map[i][j].pos.x < hero.pos.x)
					{
						map[i][j].pos.x += 1;

					}
					else
					{
						map[i][j].pos.x -= 1;

					}

					if (map[i][j].pos.y < hero.pos.y)
					{
						map[i][j].pos.y += 1;

					}
					else
					{
						map[i][j].pos.y -= 1;

					}

				}



			}
		}
		InvalidateRgn(hWnd, NULL, FALSE);
		break;
	}

	case WM_PAINT:
	{

		hDC = BeginPaint(hWnd, &ps);
		memDC = CreateCompatibleDC(hDC); // 주어진 DC와 호환되는 DC를 생성


		hBitmap1 = CreateCompatibleBitmap(hDC, x, y);
		oldbit1 = (HBITMAP)SelectObject(memDC, hBitmap1);
		Rectangle(memDC, 0, 0, x, y);

		bitDC = CreateCompatibleDC(memDC);


		if (selection == 0)
		{

			if (mapview == true)
			{
				SelectObject(bitDC, hBit_BackGround[0]);

				StretchBlt(memDC, 0, 0, map_x, map_y, bitDC, 0, 0, 1024, 640, SRCCOPY); //1024 * 640

			}


		}
		else if (selection == 1)
		{

			if (mapview == true)
			{
				SelectObject(bitDC, hBit_BackGround[1]);

				StretchBlt(memDC, 0, 0, map_x, map_y, bitDC, 0, 0, 1024, 640, SRCCOPY); //1024 * 640

			}


		}
		else if (selection == 2)
		{


			if (mapview == true)
			{
				SelectObject(bitDC, hBit_BackGround[2]);
				StretchBlt(memDC, 0, 0, map_x, map_y, bitDC, 0, 0, 1024, 640, SRCCOPY); //1024 * 640

			}


		}


		for (int j = 0; j < tile_y; j++)
		{
			for (int i = 0; i < tile_x; i++)
			{
				hBrush1 = (HBRUSH)GetStockObject(NULL_BRUSH);
				oldBrush = (HBRUSH)SelectObject(memDC, hBrush1);

				int x = (map_x / tile_x);
				int y = (map_y / tile_y);

				Rectangle(memDC, i * x, j * y, (i + 1) * x, (j + 1) * y);

				SelectObject(memDC, oldBrush);
				DeleteObject(hBrush1);
			}
		}


		hero.size.x = (map_x / tile_x);
		hero.size.y = (map_y / tile_y);
		oldbit1 = (HBITMAP)SelectObject(bitDC, hBit_Hero);

		StretchBlt(memDC, hero.pos.x, hero.pos.y, hero.size.x, hero.size.y, bitDC, 0, 0, 130, 130, SRCCOPY);


		if (map)
		{
			for (int i = 0; i < tile_y; i++) // 그리드 (타일 그리기)
			{
				for (int j = 0; j < tile_x; j++)
				{




					switch (map[i][j].kind)
					{
					case ob_1:

						oldbit1 = (HBITMAP)SelectObject(bitDC, hBit_OBJECT[0]);

						StretchBlt(memDC, map[i][j].pos.x, map[i][j].pos.y, map[i][j].size.x, map[i][j].size.y, bitDC, 0, 0, 120, 120, SRCCOPY); //1024 * 640


						break;
					case ob_2:

						oldbit1 = (HBITMAP)SelectObject(bitDC, hBit_OBJECT[1]);

						StretchBlt(memDC, map[i][j].pos.x, map[i][j].pos.y, map[i][j].size.x, map[i][j].size.y, bitDC, 0, 0, 120, 120, SRCCOPY); //1024 * 640

						break;
					case ob_3:

						oldbit1 = (HBITMAP)SelectObject(bitDC, hBit_OBJECT[2]);

						StretchBlt(memDC, map[i][j].pos.x, map[i][j].pos.y, map[i][j].size.x, map[i][j].size.y, bitDC, 0, 0, 120, 120, SRCCOPY); //1024 * 640

						break;
					case ob_4:

						oldbit1 = (HBITMAP)SelectObject(bitDC, hBit_OBJECT[3]);

						StretchBlt(memDC, map[i][j].pos.x, map[i][j].pos.y, map[i][j].size.x, map[i][j].size.y, bitDC, 0, 0, 120, 120, SRCCOPY); //1024 * 640

						break;
					case mon_1:

						oldbit1 = (HBITMAP)SelectObject(bitDC, hBit_MONSTER[0]);

						StretchBlt(memDC, map[i][j].pos.x, map[i][j].pos.y, map[i][j].size.x, map[i][j].size.y, bitDC, 0, 0, 90, 90, SRCCOPY); //1024 * 640
						map[i][j].viwe = true;
						map[i][j].monster_view = true;
						map[i][j].monster_type = 1;
						break;
					case mon_2:

						oldbit1 = (HBITMAP)SelectObject(bitDC, hBit_MONSTER[1]);

						StretchBlt(memDC, map[i][j].pos.x, map[i][j].pos.y, map[i][j].size.x, map[i][j].size.y, bitDC, 0, 0, 90, 90, SRCCOPY); //1024 * 640

						break;
					case mon_3:

						oldbit1 = (HBITMAP)SelectObject(bitDC, hBit_MONSTER[2]);

						StretchBlt(memDC, map[i][j].pos.x, map[i][j].pos.y, map[i][j].size.x, map[i][j].size.y, bitDC, 0, 0, 90, 90, SRCCOPY); //1024 * 640

						break;
					case mon_4:

						oldbit1 = (HBITMAP)SelectObject(bitDC, hBit_MONSTER[3]);

						StretchBlt(memDC, map[i][j].pos.x, map[i][j].pos.y, map[i][j].size.x, map[i][j].size.y, bitDC, 0, 0, 90, 90, SRCCOPY); //1024 * 640

						break;
					case item_1:

						oldbit1 = (HBITMAP)SelectObject(bitDC, hBit_ITEM[0]);

						StretchBlt(memDC, map[i][j].pos.x, map[i][j].pos.y, map[i][j].size.x, map[i][j].size.y, bitDC, 0, 0, 90, 90, SRCCOPY); //1024 * 640

						break;
					case item_2:

						oldbit1 = (HBITMAP)SelectObject(bitDC, hBit_ITEM[1]);

						StretchBlt(memDC, map[i][j].pos.x, map[i][j].pos.y, map[i][j].size.x, map[i][j].size.y, bitDC, 0, 0, 90, 90, SRCCOPY); //1024 * 640

						break;
					case item_3:

						oldbit1 = (HBITMAP)SelectObject(bitDC, hBit_ITEM[2]);

						StretchBlt(memDC, map[i][j].pos.x, map[i][j].pos.y, map[i][j].size.x, map[i][j].size.y, bitDC, 0, 0, 90, 90, SRCCOPY); //1024 * 640

						break;
					case item_4:

						oldbit1 = (HBITMAP)SelectObject(bitDC, hBit_ITEM[3]);

						StretchBlt(memDC, map[i][j].pos.x, map[i][j].pos.y, map[i][j].size.x, map[i][j].size.y, bitDC, 0, 0, 90, 90, SRCCOPY); //1024 * 640

						break;


					}

				}
			}

		}

		SelectObject(bitDC, oldbit1);

		BitBlt(hDC, 0, 0, 1200, 800, memDC, 0, 0, SRCCOPY);

		SelectObject(memDC, hBitmap1);
		DeleteDC(bitDC);
		DeleteDC(memDC);
		DeleteObject(hBitmap1);

		EndPaint(hWnd, &ps);
		break;
	}

	case WM_DESTROY:
	{

		if (map)
		{
			for (int i = 0; i < tile_y; i++)
			{
				if (map[i] != nullptr)
				{
					free(map[i]);
					map[i] = nullptr;
				}
			}
			if (map != nullptr)
			{
				free(map);
				map = nullptr;
			}
		}


		return 0;
	}
	}

	return(DefWindowProc(hWnd, iMessage, wParam, lParam));

}

