/********************************************************************/
/*                            lek_graph1.cpp                        */
/*                            ============                          */
/*    ������  ��  ��������  �������.                                */
/*    �������������� �  ��������  ������  ���������                 */
/********************************************************************/
#define STRICT

#include <stdio.h>
#include <malloc.h>


#include <windows.h>
#include <windowsx.h>

 // ���� ���������� � ����������� ����� ��������� ���������� (common controls)
#include <commctrl.h>

 // ���� ���������������� ��������������� �������� � ��������� ����������
 #include "resource.h"
#include "tdef.h"

 // �������� ����������
HINSTANCE hiApp;                           // ����� ������
char aczAppName[] = "���������� ��������"; // ���
HICON hiconAppSmall, hiconAppBig;          // ����������� ����������

// --- ������� ���� ---
HWND hwndMain;                                                    // ����������
LPCSTR pczMainWndClassName = "MainWndClass";                      // ��� ������
LPCSTR pczMainWndTitle = "������� '������' ������/���������";  // ����� ���������
HMENU  hmenuMain;                                                 // ���������� ����

// --- ���������� ���� ---
HWND hwndDlg;

// --- ������� ������� � ����������� ��������� �������� ���� ---
LRESULT CALLBACK MainWndProc(HWND, UINT, WPARAM, LPARAM);
BOOL MainOnCreate(HWND, LPCREATESTRUCT);
BOOL MainOnPaint(HWND);
BOOL polet_snar(HWND);
BOOL MainOnDestroy(HWND);

// --- ������� ������������� � ���������� ---
BOOL RegisterWndClasses(void);
void UnregisterWndClasses(void);
BOOL CreateWindows(void);
void InitializeApp(void);
void UninitializeApp(void);

// ������� - ����� �����
int APIENTRY WinMain(HINSTANCE, HINSTANCE, LPSTR, int);

int* Scale_coor_w(HWND, RECT, double*, int);
double* make_mas_coor(int*);
BOOL   anim_main(HWND hwnd);

/*----------------------------------*/
/*  ������, ���������� ���������    */
/*----------------------------------*/
 // --- ������ ---
 // �������� ������� (����)
#define TIMER_INTERVAL 10
 // �������������
#define TIMER_ID 1000


 // --- ������ ---
 // �������
int timer = -1;

#define  K_GAB 0.05  // ����������  ����������� �������
//  ���������� ����������� �� ���� ������� ������


/********************************************************************/
/*                            MainWndProc                           */
/*                            ============                          */
/*                      ������� ������� �������� ����               */
/********************************************************************/

LRESULT CALLBACK MainWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg) {

	case WM_KEYDOWN:
		if (LOWORD(wParam) == VK_SPACE)
		{
			InvalidateRect(hwnd, NULL, TRUE);
			if (-1 == timer)
				SetTimer(hwnd, TIMER_ID, TIMER_INTERVAL, NULL);
			else
			{
				KillTimer(hwnd, TIMER_ID);
				timer = -1;
			}
		}

		break;

	case WM_PAINT:
		return anim_main(hwnd);

	case WM_TIMER:
		timer++;
		InvalidateRect(hwnd, NULL, TRUE);
		break;

	case WM_DESTROY:
		return MainOnDestroy(hwnd);
	default:
		return DefWindowProc(hwnd, msg, wParam, lParam);
	}
	return 0L;
}  //func MainWndProc


/***********************************************/
/*               MainOnDestroy                 */
/*               =============                 */
/*          ���������� WM_DESTROY              */
/***********************************************/

BOOL MainOnDestroy(HWND hwnd)
{
	PostQuitMessage(0);
	return TRUE;
}  //func MainOnDestroy


/***********************************************/
/*               RegisterWndClasses            */
/*               ==================            */
/*     ����������� ������� ���� � �� Windows   */
/***********************************************/

BOOL RegisterWndClasses()
{
	// ������������� ��������� �������� ������ ����
	WNDCLASSEX wce_main;
	memset(&wce_main, 0, sizeof(WNDCLASSEX));
	wce_main.cbSize = sizeof(WNDCLASSEX);
	wce_main.hInstance = hiApp;
	wce_main.style = CS_VREDRAW | CS_HREDRAW;
	// wce_main.hIcon = LoadIcon(hiApp, MAKEINTRESOURCE(IDI_ICON));
	wce_main.lpfnWndProc = (WNDPROC)MainWndProc;
	wce_main.hCursor = LoadCursor(NULL, IDC_ARROW);
	wce_main.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	// wce_main.lpszMenuName = MAKEINTRESOURCE(IDR_MENU);
	wce_main.lpszClassName = pczMainWndClassName;
	return RegisterClassEx(&wce_main);
}  //func RegisterWndClasses


/***************************************************/
/*               UnregisterWndClasses              */
/*               ====================              */
/*   �������� �������� ������� ���� �� �� Windows  */
/***************************************************/

void UnregisterWndClasses()
{
	UnregisterClass(pczMainWndClassName, hiApp);
}  //func UnregisterWndClasses


/***************************************************/
/*               CreateWindows                     */
/*               =============                     */
/*     ������� �������� �������� ����              */
/***************************************************/
BOOL CreateWindows()
{
	// ����������� �������� ������ � ��������
	int scrw2 = GetSystemMetrics(SM_CXSCREEN) / 2,
		scrh2 = GetSystemMetrics(SM_CYSCREEN) / 2;
	// �������� �������� ����
	hwndMain = CreateWindow(pczMainWndClassName, pczMainWndTitle,
		WS_OVERLAPPED | WS_SYSMENU | WS_MINIMIZEBOX |
		WS_MAXIMIZEBOX | WS_THICKFRAME | WS_CLIPCHILDREN | WS_CLIPSIBLINGS,
		scrw2 - 400, scrh2 - 300, 800, 600, NULL, NULL, hiApp, NULL);
	if (!hwndMain)
		return FALSE;
	return TRUE;
}  //func CreateWindows

/***************************************************/
/*               InitializeApp                     */
/*               =============                     */
/*     ��������������� ��������                    */
/***************************************************/
void InitializeApp()
{
	RegisterWndClasses();
	CreateWindows();
	ShowWindow(hwndMain, SW_SHOW);
	UpdateWindow(hwndMain);
}  //func InitializeApp


/***************************************************/
/*               UninitializeApp                   */
/*               ===============                   */
/*     ��������������  ��������                    */
/***************************************************/
void UninitializeApp()
{

	extern HBRUSH hbr[];

	extern int all_br;

	for (int i = 0; i < all_br; i++)
		DeleteObject(hbr[i]);

	UnregisterWndClasses();
}  //func UninitializeApp

/***************************************************/
/*                 WinMain                         */
/*                 =======                         */
/*        �������  �������                         */
/***************************************************/

int APIENTRY WinMain(HINSTANCE hiApp__, HINSTANCE, LPSTR, int)
{
	MSG msg;
	hiApp = hiApp__;

	InitializeApp();
	while (GetMessage(&msg, NULL, 0, 0))
		DispatchMessage(&msg);
	UninitializeApp();

	return msg.wParam;
}  //func WINMAIN



