#include<Windows.h>
#include <stdio.h>
#include "resource.h"

LPCTSTR lpszClass = "WinDow Class Name";
LPCTSTR lpszWindowName = "windows program 1-2";

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage,
	WPARAM wParam, LPARAM IParam);
int WINAPI WinMain(HINSTANCE hlnsatance, HINSTANCE hPrevlstance,
	LPSTR lpzsCmdParam, int nCmdShow)

{
	HWND hWnd;
	MSG Message;
	WNDCLASSEX WndClass;


	WndClass.cbSize = sizeof(WndClass);
	WndClass.style = CS_HREDRAW | CS_VREDRAW;
	WndClass.lpfnWndProc = (WNDPROC)WndProc;
	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hInstance = hlnsatance;
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	WndClass.lpszMenuName = MAKEINTRESOURCE(IDR_MENU1);
	
	WndClass.lpszClassName = lpszClass;
	WndClass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	RegisterClassEx(&WndClass);

	hWnd = CreateWindow
	(lpszClass, lpszWindowName, WS_SYSMENU | WS_THICKFRAME | WS_MAXIMIZEBOX | WS_MINIMIZEBOX | WS_HSCROLL | WS_VSCROLL, 100, 50, 800, 600, NULL, (HMENU)NULL, hlnsatance, NULL);

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	while (GetMessage(&Message, 0, 0, 0))
	{
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}
	return 0;
}


LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM IParam)
{
	PAINTSTRUCT ps;
	HDC hDC;
	static char str[10][100];
	static int count, line;
	FILE *fr;
	FILE *fw;
	OPENFILENAME OFN;
	TCHAR str2[100], lpstrFile2[100] = "";
	TCHAR filter[100] =  "텍스트 파일(*.txt)\0 * .txt; \0 문서 File \0 * .txt; *.doc \0";
	OPENFILENAME SFN;
	HANDLE hFile;
	TCHAR InBuff[1000];
	TCHAR str3[100], lpstrFile3[100] = "";
	static SIZE  size;
	TCHAR filter2[100] = "텍스트 파일(*.txt)\0 * .txt; \0 문서 File \0 * .txt; *.doc \0";


	static POINT cursor;

	switch (iMessage) {
	case  WM_CREATE:
		CreateCaret(hWnd, NULL, 3, 15);
		ShowCaret(hWnd);
		count = 0;
		line = 0;
		break;
	case WM_PAINT:
		hDC = BeginPaint(hWnd, &ps);
		GetTextExtentPoint(hDC, str[line], count, &size);
		SetCaretPos(size.cx + cursor.x, line * 20);

		for (int i = 0; i < 10; i++)
		{
			TextOut(hDC, cursor.x, i * 20, str[i], strlen(str[i]));
	
		}
		EndPaint(hWnd, &ps);
		break;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case ID_OPEN:
			memset(&OFN, 0, sizeof(OPENFILENAME)); // 초기화
			OFN.lStructSize = sizeof(OPENFILENAME);
			OFN.hwndOwner = hWnd;
			OFN.lpstrFilter = filter;
			OFN.lpstrFile = lpstrFile2;
			OFN.nMaxFile = 256;
			OFN.lpstrInitialDir = "."; // 초기 디렉토리
			if (GetOpenFileName(&OFN) != 0) {

					wsprintf(str2, "%s 파일을 여시겠습니까 ?", OFN.lpstrFile);
					MessageBox(hWnd, str2, "열기 선택", MB_OK);
					fr = fopen(OFN.lpstrFile, "rt");
					for (int i = 0; i < 10; i++)
					{
						for (int j = 0; j < 100; j++)
						{
							fscanf(fr, "%c", &str[i][j]);
						}

						fscanf(fr, "\n");
					}
					fclose(fr);
			}
			break;
		case ID_STORE:
			memset(&SFN, 0, sizeof(OPENFILENAME)); // 초기화
			SFN.lStructSize = sizeof(OPENFILENAME);
			SFN.hwndOwner = hWnd;
			SFN.lpstrFilter = filter2;
			SFN.lpstrFile = lpstrFile3;
			SFN.nMaxFile = 256;
			SFN.lpstrInitialDir = ".";
			if (GetSaveFileName(&SFN) != 0) {
				wsprintf(str3, "%s 파일에 저장하시겠습니까 ?", SFN.lpstrFile);
				MessageBox(hWnd, str3, "저장하기 선택", MB_OK);
				fw = fopen(SFN.lpstrFile, "wt");
				for (int i = 0; i < 10; i++) 
				{
					for (int j = 0; j < 100; j++)
					{
						fprintf(fw, "%c", str[i][j]);
					}

					fprintf(fw, "\n");
				}
				fclose(fw);

			}
			break;
		}
		break;

	case WM_CHAR:

		if (wParam == VK_TAB)
		{
			for (int i = 0; i < 4; i++)
			{

				str[line][count++] = ' ';
			}
		}

		else if (wParam == VK_BACK)
		{
			if (count == 0)
			{

				line--;
				count = strlen(str[line]);
			}
			else if (count > 0)
			{
				count--;
				str[line][count] = NULL;
			}
		}
		else if (wParam == VK_RETURN)
		{
			if (line < 9)
			{
				count = 0;
				line++;
			}
		}
		else if (wParam == VK_ESCAPE)
		{
			for (int i = 0; i < 10; i++)
			{
				for (int j = 0; j < 100; j++)
				{
					str[i][j] = NULL;

				}
			}
			count = 0;
			line = 0;
		}


		else
		{
			if (count < 100)
			{
				str[line][count++] = wParam;
				str[line][count] = '\0';
			}
		}

		InvalidateRgn(hWnd, NULL, TRUE);
		break;
	case WM_KEYDOWN:

		if (wParam == VK_UP)
		{

			line--;
			count = strlen(str[line]);
		}
		if (wParam == VK_RIGHT)
		{
			if (count < 100)
			{
				count++;
			}
		}
		if (wParam == VK_DOWN)
		{
			line++;
			count = strlen(str[line]);
		}

		if (wParam == VK_LEFT)
		{
			if (size.cx + cursor.x > 0)
				count--;
		}
		if (wParam == VK_DELETE)
		{
			if (line > 0)
			{
				for (int i = 0; i < 100; i++)
				{
					str[line][i] = NULL;
				}
				line--;
				count = 0;
			}

			// 현재 캐럿이 놓인 한 줄이 삭제되고 한 줄씩 위로 쉬프트
			//된다 캐럿은 현재 줄 맨 앞으로
		}

		if (wParam == VK_HOME)
		{
			if (line >= 0)
			{

				count = 0;
			}
		}
		InvalidateRgn(hWnd, NULL, TRUE);
		break;
	case WM_DESTROY:
		HideCaret(hWnd);
		DestroyCaret();

		PostQuitMessage(0);
		return 0;

	}
	return(DefWindowProc(hWnd, iMessage, wParam, IParam));
}
