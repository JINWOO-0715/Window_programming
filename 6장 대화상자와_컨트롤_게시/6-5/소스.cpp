#include<Windows.h>
#include<stdio.h>
#include<stdlib.h>
#include <time.h>
#include <string.h>
#include"resource.h"

HINSTANCE g_hInst;
LPCTSTR lpszClass = "WinDow Class Name";
LPCTSTR lpszWindowName = "windows program 1-2";

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM IParam);
BOOL CALLBACK Dlg6_1Proc(HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam);

int convert_string(const void *a, const void *b);

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
		break;
	case WM_PAINT:
		hDC = BeginPaint(hWnd, &ps);
		EndPaint(hWnd, &ps);
		break;
	case WM_KEYDOWN:
		// 아무 키나 누르면 대화상자를 띄운다.
		DialogBox(g_hInst, MAKEINTRESOURCE(IDD_DIALOG1), hWnd, Dlg6_1Proc);
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

	static char list[100];
	static char list2[10][100];
	static char phone[20];
	static char name[30];
	static char str[] = { "여성" };
	static char str2[] = { "남성" };
	 int ra;
	static char birth[256];
	static char birth_str[256];
	static char n = sizeof(list2) / sizeof(char[100]);


	static char tmp[100];
	static int a = 0, b = 0;
	static int gender;
	static HWND hlist;
	switch (iMsg) {
	case WM_INITDIALOG:
		hlist = GetDlgItem(hDlg, IDC_LIST1);
		hCombo = GetDlgItem(hDlg, IDC_COMBO1);
		
		for (int i = 1994; i < 2018; i++)
		{
			sprintf_s(birth_str, sizeof(birth_str), "%d", i);
			SendMessage(hCombo, CB_ADDSTRING, 0, (LPARAM)birth_str);
		}


		break;

	case WM_COMMAND:
		switch (LOWORD(wParam)) {

		case IDC_EXIT:
			EndDialog(hDlg, 0);
			break;
		case IDC_ENJOY:
			GetDlgItemText(hDlg, ID_NAME, name, 100);
			if (gender == 0)
			{
				GetDlgItemText(hDlg, ID_NUMBER, phone, 30);
				GetDlgItemText(hDlg, IDC_FEMALE, str2, 30);

				SendMessage(hCombo, CB_GETLBTEXT, selection, (LPARAM)birth);
				sprintf(list, "이름:%s  성별:%s  전화번호:%s 생년월일:%s", name, str, phone, birth);
				sprintf(list, "이름:%s  성별:%s  전화번호:%s 생년월일:%s", name, str, phone, birth);
				strcpy(list2[a], list);
				a++;
			}
			else
			{
				GetDlgItemText(hDlg, ID_NUMBER, phone, 30);
				GetDlgItemText(hDlg, IDC_MALE, str2, 30);
				SendMessage(hCombo, CB_GETLBTEXT, selection, (LPARAM)birth);
				sprintf(list, "이름:%s  성별:%s  전화번호:%s 생년월일:%s", name, str, phone, birth);
				sprintf(list2[a], "%s", list);
				a++;
			}
			if (strcmp(name, ""))
			{
				SendMessage(hlist, LB_INSERTSTRING, 0, (LPARAM)list);
			}
			break;
		case IDC_NEWMEM:
			SetDlgItemText(hDlg, ID_NAME, ""); // 널 스트링 복사
			SetDlgItemText(hDlg, ID_NUMBER, "");

			break;
		case IDC_GOOUT:

			SendMessage(hlist, LB_DELETESTRING, selection, 0);
			a--;
			break;
		case IDC_FEMALE:
			gender = 0;
			break;
		case IDC_MALE:
			gender = 1;
			break;
		case IDC_COMBO1:

			if (HIWORD(wParam) == CBN_SELCHANGE)
				selection = SendMessage(hCombo, CB_GETCURSEL, 0, 0);

			break;
		case IDC_LIST1:
			if (HIWORD(wParam) == CBN_SELCHANGE)
			{
				selection = SendMessage(hlist, LB_GETCURSEL, 0, 0);
			}
			break;
		case IDC_SORT:

		
			for (int i = 0; i < a; i++)
			{
				SendMessage(hlist, LB_DELETESTRING, 0, 0);
				
			}
			for (int i = 0; i < a - 1; i++)

			{
				ra = i;
				for (int j = i+1; j <a; j++)

				{

					if (strcmp(list2[ra], list2[j]) > 0)

					{
						ra = j;
				

					}

				}
				strcpy(tmp, list2[i]);

				strcpy(list2[i], list2[ra]);

				strcpy(list2[ra], tmp);

			}
			for (int i = 0; i < a; i++)

			{
				SendMessage(hlist, LB_INSERTSTRING, i, (LPARAM)list2[i]); 
			}
		
			

			break;

		}
		break;
	}
	return 0;
}
int convert_string(const void *a, const void *b)
{
	return strcmp((char *)a, (char *)b);
}