#include<Windows.h>
#include"resource.h"
#include<time.h>


HINSTANCE hInst;
HWND hwnd;

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK WndProcChild(HWND, UINT, WPARAM, LPARAM);


int APIENTRY wWinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPWSTR lpCmdStr,
	int nCmdShow)

{
	hInst = hInstance;

	WNDCLASS wndClass;
	wndClass.style = 0;
	wndClass.lpfnWndProc = WndProc;
	wndClass.cbClsExtra = 0;
	wndClass.cbWndExtra = 0;
	wndClass.hbrBackground = (HBRUSH)CreateSolidBrush(RGB(10, 40, 200));
	wndClass.hCursor = LoadCursor(NULL, IDC_CROSS);
	wndClass.hIcon = LoadIcon(NULL, IDI_WINLOGO);
	wndClass.hInstance = hInstance;
	wndClass.lpszClassName = L"MainWndClass";
	wndClass.lpszMenuName = NULL;

	WNDCLASS childWndClass;
	childWndClass.style = 0;
	childWndClass.lpfnWndProc = WndProcChild;
	childWndClass.cbClsExtra = 0;
	childWndClass.cbWndExtra = 0;
	childWndClass.hbrBackground = (HBRUSH)CreateSolidBrush(RGB(10, 40, 20));
	childWndClass.hCursor = LoadCursor(NULL, IDC_CROSS);
	childWndClass.hIcon = LoadIcon(NULL, IDI_QUESTION);
	childWndClass.hInstance = hInstance;
	childWndClass.lpszClassName = L"ChildWndClass";
	childWndClass.lpszMenuName = NULL;

	RegisterClass(&wndClass);
	RegisterClass(&childWndClass);

	hwnd = CreateWindow(
		L"MainWndClass",
		L"Main Window Caption App",
		WS_OVERLAPPEDWINDOW,
		50,
		50,
		500,
		500,
		NULL,
		NULL,
		hInstance,
		0);

	if (!hwnd)
	{
		return FALSE;
	}

	ShowWindow(hwnd, SW_NORMAL);

	UpdateWindow(hwnd);

	MSG msg;

	while (GetMessage(&msg, hwnd, 0, 0) == TRUE)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static WCHAR buf[100];

	switch (message)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_LBUTTONDOWN: {
		hwnd = CreateWindow(
			L"ChildWndClass",
			L"Child Window Caption App",
			WS_OVERLAPPEDWINDOW,
			100,
			100,
			200,
			200,
			NULL,
			NULL,
			hInst,
			0);

		ShowWindow(hwnd, SW_NORMAL);

	}  break;

	default:
		return DefWindowProc(hwnd, message, wParam, lParam);
	}

	return 0;
}

LRESULT CALLBACK WndProcChild(HWND hwndChild, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_RETURN:
		{
			int x, y;
			x = y = 0;
			MoveWindow(hwnd, x, y, 300, 300, TRUE);
			break;
		}
		case VK_LEFT:
		{
			int x, y;
			RECT rect;
			GetWindowRect(hwnd, &rect);
			x = rect.left;
			y = rect.top;
			if (x > 0) --x;
			MoveWindow(hwnd, x, y, 300, 300, TRUE);
			break;
		}
		case VK_RIGHT:
		{
			int x, y;
			RECT rect;
			GetWindowRect(hwnd, &rect);
			x = rect.left;
			y = rect.top;
			if (x < 1366) ++x;
			MoveWindow(hwnd, x, y, 300, 300, TRUE);
			break;
		}
		case VK_DOWN:
		{
			int x, y;
			RECT rect;
			GetWindowRect(hwnd, &rect);
			x = rect.left;
			y = rect.top;
			if (y < 768) ++y;
			MoveWindow(hwnd, x, y, 300, 300, TRUE);
			break;
		}
		case VK_UP:
		{
			int x, y;
			RECT rect;
			GetWindowRect(hwnd, &rect);
			x = rect.left;
			y = rect.top;
			if (y > 0) --y;
			MoveWindow(hwnd, x, y, 300, 300, TRUE);
			break;
		}
		}
		break;
	

	default:
		return DefWindowProc(hwndChild, message, wParam, lParam);
	}
	return 0;
}