#include<Windows.h>
#include<stdio.h>
#include<stdlib.h>
#include <time.h>
#include <string.h>
#include "resource.h"
HINSTANCE g_hInst;
LPCTSTR lpszClass = "WinDow Class Name";
LPCTSTR lpszWindowName = "windows program 1-2";
void Insert(TCHAR *NumLine, TCHAR Input, HWND *hwnd);

BOOLEAN isCurrent(TCHAR *NumLine);
LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM IParam);
BOOL CALLBACK Dlg6_1Proc(HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hlnsatance, HINSTANCE hPrevlstance,
	LPSTR lpzsCmdParam, int nCmdShow)

{
	HWND hWnd;
	HACCEL hAccel;
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

	hAccel = LoadAccelerators(hlnsatance, MAKEINTRESOURCE(IDR_ACCELERATOR1));
	while (GetMessage(&Message, NULL, 0, 0)) {
		if (!TranslateAccelerator(hWnd, hAccel, &Message)) {
			TranslateMessage(&Message);
			DispatchMessage(&Message);
		}
	}
	return Message.wParam;
}


LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM IParam)
{
	PAINTSTRUCT ps;
	HDC hDC;
	HPEN hpen, oldpen;
	HBRUSH hBrush, oldBrush;
	static RECT str = { 0,0,400,590 };
	TCHAR ptr[30] = "계산기";
	static int a =NULL;
	static int result =0;
	static int b = NULL;
	 char ch;
	 static int count = NULL;
	static TCHAR NumLine[128] = { NULL, };
	static int num,num2;
	switch (iMessage)
	{
	case WM_CREATE:
		CreateWindow(TEXT("static"), NumLine, WS_CHILD |
			WS_VISIBLE | SS_RIGHT, 15, 25, 335, 95, hWnd, (HMENU)ID_STATIC, g_hInst, NULL);
		CreateWindow(TEXT("Button"), TEXT("CE"), WS_CHILD |
			WS_VISIBLE | BS_PUSHBUTTON, 29, 162, 70, 70, hWnd, (HMENU)0, g_hInst, NULL);
		CreateWindow(TEXT("Button"), TEXT("C"), WS_CHILD |
			WS_VISIBLE | BS_PUSHBUTTON, 107, 162, 70, 70, hWnd, (HMENU)ID_C, g_hInst, NULL);
		CreateWindow(TEXT("Button"), TEXT("←"), WS_CHILD |
			WS_VISIBLE | BS_PUSHBUTTON, 185, 162, 70, 70, hWnd, (HMENU)IDC_BACKSPACE, g_hInst, NULL);
		CreateWindow(TEXT("Button"), TEXT("/"), WS_CHILD |
			WS_VISIBLE | BS_PUSHBUTTON, 263, 162, 70, 70, hWnd, (HMENU)ID_DIV, g_hInst, NULL);


		CreateWindow(TEXT("Button"), TEXT("7"), WS_CHILD |
			WS_VISIBLE | BS_PUSHBUTTON, 29, 239, 70, 70, hWnd, (HMENU)ID_NUM_7, g_hInst, NULL);
		CreateWindow(TEXT("Button"), TEXT("8"), WS_CHILD |
			WS_VISIBLE | BS_PUSHBUTTON, 107, 239, 70, 70, hWnd, (HMENU)ID_NUM_8, g_hInst, NULL);
		CreateWindow(TEXT("Button"), TEXT("9"), WS_CHILD |
			WS_VISIBLE | BS_PUSHBUTTON, 185, 239, 70, 70, hWnd, (HMENU)ID_NUM_9, g_hInst, NULL);
		CreateWindow(TEXT("Button"), TEXT("X"), WS_CHILD |
			WS_VISIBLE | BS_PUSHBUTTON, 263, 239, 70, 70, hWnd, (HMENU)ID_MUF, g_hInst, NULL);


		CreateWindow(TEXT("Button"), TEXT("4"), WS_CHILD |
			WS_VISIBLE | BS_PUSHBUTTON, 29, 316, 70, 70, hWnd, (HMENU)ID_NUM_4, g_hInst, NULL);
		CreateWindow(TEXT("Button"), TEXT("5"), WS_CHILD |
			WS_VISIBLE | BS_PUSHBUTTON, 107, 316, 70, 70, hWnd, (HMENU)ID_NUM_5, g_hInst, NULL);
		CreateWindow(TEXT("Button"), TEXT("6"), WS_CHILD |
			WS_VISIBLE | BS_PUSHBUTTON, 185, 316, 70, 70, hWnd, (HMENU)ID_NUM_6, g_hInst, NULL);
		CreateWindow(TEXT("Button"), TEXT("-"), WS_CHILD |
			WS_VISIBLE | BS_PUSHBUTTON, 263, 316, 70, 70, hWnd, (HMENU)ID_MINUS, g_hInst, NULL);


		CreateWindow(TEXT("Button"), TEXT("1"), WS_CHILD |
			WS_VISIBLE | BS_PUSHBUTTON, 29, 393, 70, 70, hWnd, (HMENU)ID_NUM_1, g_hInst, NULL);
		CreateWindow(TEXT("Button"), TEXT("2"), WS_CHILD |
			WS_VISIBLE | BS_PUSHBUTTON, 107, 393, 70, 70, hWnd, (HMENU)ID_NUM_2, g_hInst, NULL);
		CreateWindow(TEXT("Button"), TEXT("3"), WS_CHILD |
			WS_VISIBLE | BS_PUSHBUTTON, 185, 393, 70, 70, hWnd, (HMENU)ID_NUM_3, g_hInst, NULL);
		CreateWindow(TEXT("Button"), TEXT("+"), WS_CHILD |
			WS_VISIBLE | BS_PUSHBUTTON, 263, 393, 70, 70, hWnd, (HMENU)ID_PLUS, g_hInst, NULL);


		CreateWindow(TEXT("Button"), TEXT("0"), WS_CHILD |
			WS_VISIBLE | BS_PUSHBUTTON, 107, 470, 70, 70, hWnd, (HMENU)ID_NUM_0, g_hInst, NULL);
		CreateWindow(TEXT("Button"), TEXT("."), WS_CHILD |
			WS_VISIBLE | BS_PUSHBUTTON, 185, 470, 70, 70, hWnd, (HMENU)1, g_hInst, NULL);
		CreateWindow(TEXT("Button"), TEXT("="), WS_CHILD |
			WS_VISIBLE | BS_PUSHBUTTON, 263, 470, 70, 70, hWnd, (HMENU)ID_RESULT, g_hInst, NULL);

		CreateWindow(TEXT("Button"), TEXT("Reverse"), WS_CHILD |
			WS_VISIBLE | BS_PUSHBUTTON, 107, 547, 70, 70, hWnd, (HMENU)IDC_REVERSE, g_hInst, NULL);
		CreateWindow(TEXT("Button"), TEXT("종료"), WS_CHILD |
			WS_VISIBLE | BS_PUSHBUTTON, 185, 547, 70, 70, hWnd, (HMENU)IDC_EXIT, g_hInst, NULL);
		CreateWindow(TEXT("Button"), TEXT("^10"), WS_CHILD |
			WS_VISIBLE | BS_PUSHBUTTON, 263, 547, 70, 70, hWnd, (HMENU)IDC_MUF10, g_hInst, NULL);

		CreateWindow(TEXT("Button"), TEXT("8진수"), WS_CHILD |
			WS_VISIBLE | BS_PUSHBUTTON, 185, 624, 70, 70, hWnd, (HMENU)IDC_8JINSU, g_hInst, NULL);
		CreateWindow(TEXT("Button"), TEXT("10의 지수"), WS_CHILD |
			WS_VISIBLE | BS_PUSHBUTTON, 263, 624, 70, 70, hWnd, (HMENU)IDC_10JISU, g_hInst, NULL);
		return 0;
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

	case WM_INITDIALOG:
		break;
	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case ID_C:
			memset(NumLine, NULL, sizeof(NumLine));
			SetDlgItemText(hWnd, ID_STATIC, NumLine);
			break;
		case ID_NUM_0:
			Insert(NumLine, '0', &hWnd);
			if (count == NULL)

			{

				if (a != NULL)

				{

					a *= 10;

				}

				else

					a = 0;



				_itoa_s(a, NumLine, 10);

			}

			else

			{

				if (b != NULL)

				{

					b *= 10;

				}

				else

					b = 0;



				_itoa_s(b, NumLine, 10);

			}



			break;
		case ID_NUM_1:
			Insert(NumLine, '1', &hWnd);
			num = atoi(NumLine);
			if (count == NULL)

			{

				if (a != NULL)

				{

					a *= 10;

					a += 1;

				}

				else

					a = 1;



				//sprintf_s(str, "%d", a);

				_itoa_s(a, NumLine, 10);

			
			}

			else

			{

				if (b != NULL)

				{

					b *= 10;

					b += 1;

				}

				else

					b = 1;



				_itoa_s(b, NumLine, 10);

			}



			break;
		case ID_NUM_2:
			Insert(NumLine, '2', &hWnd);
			num = atoi(NumLine);
			if (count == NULL)

			{

				if (a != NULL)

				{

					a *= 10;

					a += 2;

				}

				else

					a = 2;



				_itoa_s(a, NumLine, 10);
				
			}

			else

			{

				if (b != NULL)

				{

					b *= 10;

					b += 2;

				}

				else

					b = 2;



				_itoa_s(b, NumLine, 10);

			}


			break;
		case ID_NUM_3:
			Insert(NumLine, '3', &hWnd);
			num = atoi(NumLine);
			if (count == NULL)

			{

				if (a != NULL)

				{

					a *= 10;

					a += 3;

				}

				else

					a = 3;



				_itoa_s(a, NumLine, 10);


			}

			else

			{

				if (b != NULL)

				{

					b *= 10;

					b += 3;

				}

				else

					b = 3;



				_itoa_s(b, NumLine, 10);

			}

			break;

			break;
		case ID_NUM_4:
			Insert(NumLine, '4', &hWnd);
			num = atoi(NumLine);
			if (count == NULL)

			{

				if (a != NULL)

				{

					a *= 10;

					a += 4;

				}

				else

					a = 4;



				_itoa_s(a, NumLine, 10);

			}

			else

			{

				if (b != NULL)

				{

					b *= 10;

					b += 4;

				}

				else

					b = 4;



				_itoa_s(b, NumLine, 10);


			}

			break;


			break;
		case ID_NUM_5:
			Insert(NumLine, '5', &hWnd);
			num = atoi(NumLine);

			break;
		case ID_NUM_6:
			Insert(NumLine, '6', &hWnd);
			num = atoi(NumLine);

			break;
		case ID_NUM_7:
			Insert(NumLine, '7', &hWnd);
			num = atoi(NumLine);

			break;
		case ID_NUM_8:
			Insert(NumLine, '8', &hWnd);
			num = atoi(NumLine);

			break;
		case ID_NUM_9:
			Insert(NumLine, '9', &hWnd);
			num = atoi(NumLine);

				break;
		case ID_PLUS:
			Insert(NumLine, '+', &hWnd);
			ch = '+';

			count = 1;
			break;
		case ID_MINUS:
			Insert(NumLine, '-', &hWnd);
			ch = '-';

			count = 1;
			break;
		case ID_DIV:
			Insert(NumLine, '/', &hWnd);
			ch = 'X';

			count = 1;
			break;
		case ID_MUF:
			Insert(NumLine, '*', &hWnd);
			ch = '/';

			count = 1;
			break;
		case IDC_BACKSPACE:
			if (lstrlen(NumLine)) {
				NumLine[lstrlen(NumLine) - 1] = NULL;
				SetDlgItemText(hWnd, ID_STATIC, NumLine);
			}
			break;
		case ID_RESULT:
			if (lstrlen(NumLine)) {
				NumLine[lstrlen(NumLine) - 1] = NULL;
				SetDlgItemText(hWnd, ID_STATIC, NumLine);
				if (ch == '+')

					result = a + b;

				else if (ch == '-')

					result = a - b;

				else if (ch == 'X')

					result = a * b;

				else if (ch == '/')

				{

					if (b = NULL)

						b = 1;



					result = a / b;

				}

				else

					break;



				sprintf_s(NumLine, "%d", result);



				count = 0;

				a = 0;

				b = 0;



			}
			//	Result(NumLine);
			break;
		case IDC_10JISU:
			break;
		case IDC_8JINSU:
			break;
		case IDC_EXIT:
			PostQuitMessage(0);
			break;
		case IDC_MUF10:
			break;
		case IDC_REVERSE :
			break;

		}
		return 0;
		break;
	case WM_PAINT:
		hDC = BeginPaint(hWnd, &ps);
		EndPaint(hWnd, &ps);
		break;
	case WM_KEYDOWN:
		// 아무 키나 누르면 대화상자를 띄운다.
		
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
		switch (LOWORD(wParam)) {

		case IDC_EXIT:
			EndDialog(hDlg, 0);
			break;

		}
		break;
	}
	return 0;
}

void Insert(TCHAR *NumLine, TCHAR Input, HWND *hwnd)
{
	TCHAR CopyTemp[2] = { NULL, };
	if (!isdigit(Input)) {
		if (isCurrent(NumLine))
		{
			CopyTemp[0] = Input;
			lstrcat(NumLine, CopyTemp);
			SetDlgItemText(*hwnd, ID_STATIC, NumLine);


		}
	}
	else
	{
		CopyTemp[0] = Input;
		lstrcat(NumLine, CopyTemp);
		SetDlgItemText(*hwnd, ID_STATIC, NumLine);

	}
}
BOOLEAN isCurrent(TCHAR *NumLine)
{
	int Length = lstrlen(NumLine);
	if (isdigit(NumLine[Length - 1])) {
		return true;
	}
	else 
	{
		return false;
	}
}
