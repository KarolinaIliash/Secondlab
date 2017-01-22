#include<windows.h>
#include <stdio.h>
#include "draw.h"


LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
char szClassName[] = "PROJ";

enum
{
	WAIT_CENTER = 0, WAIT_RADIUS, COMPLETED
}
states;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	HWND hWnd;
	MSG lpMsg;
	WNDCLASS wc;

	// Заполняем структуру класса окна
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = NULL;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = szClassName;

	// Регистрируем класс окна
	if (!RegisterClass(&wc))
	{
		MessageBox(NULL, "Cannot register class", "Error", MB_OK);
		return 0;
	}

	// Создаем основное окно приложения
	hWnd = CreateWindow(
		szClassName,					// Имя класса                   
		"Wu Xiaolin Alghorithm Cicrle Paint",	// Текст заголовка
		WS_OVERLAPPEDWINDOW,			// Стиль окна                                             
		50, 50,						// Позиция левого верхнего угла  
		600, 600,						// Ширина и высота окна    
		(HWND)NULL,					// Указатель на родительское окно NULL    
		(HMENU)NULL,					// Используется меню класса окна              
		(HINSTANCE)hInstance,			// Указатель на текущее приложение
		NULL);						// Передается в качестве lParam в событие WM_CREATE

	if (!hWnd)
	{
		MessageBox(NULL, "Не удается создать главное окно!", "Ошибка", MB_OK);
		return 0;
	}

	// Показываем наше окно
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	// Выполняем цикл обработки сообщений до закрытия приложения
	while (GetMessage(&lpMsg, NULL, 0, 0)) {
		TranslateMessage(&lpMsg);
		DispatchMessage(&lpMsg);
	}

	return (lpMsg.wParam);
}


LRESULT CALLBACK WndProc(HWND hWnd, UINT messg, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	RECT Rect;
	HDC hdc, hCmpDC;
	HBITMAP hBmp;
	static int x_r, y_r, x_c, y_c, radius;
	static int state = 0;
	static bool win_paint = false;

	switch (messg)
	{
	case WM_PAINT:
		GetClientRect(hWnd, &Rect);
		hdc = BeginPaint(hWnd, &ps);
		// Создание нового контекста для двойной буфферизации
		hCmpDC = CreateCompatibleDC(hdc);
		hBmp = CreateCompatibleBitmap(hdc, Rect.right - Rect.left,
			Rect.bottom - Rect.top);
		SelectObject(hCmpDC, hBmp);
		// Закраска фоновым цветом
		LOGBRUSH br;
		br.lbStyle = BS_SOLID;
		br.lbColor = 0xEECCCC;
		HBRUSH brush;
		brush = CreateBrushIndirect(&br);
		FillRect(hCmpDC, &Rect, brush);
		DeleteObject(brush);
		// Рисование
		SetBkColor(hCmpDC, 0xEECCCC);
		switch (state)
		{
		case WAIT_CENTER:
			TextOut(hCmpDC, 10, 10, "Click Center Point", 18);
			break;
		case WAIT_RADIUS:
			TextOut(hCmpDC, 10, 10, "Click Border Point", 18);
			break;
		case COMPLETED:
			TextOut(hCmpDC, 10, 10, "Click for clear draw", 23);
			char _tmp[60];
			sprintf_s(_tmp, "Radius Circle = %3u, Coords = x:%4u, y:%4u", radius, x_r, y_r);
			TextOut(hCmpDC, 10, 25, _tmp, 45);
			break;
		}
		if ((state == COMPLETED) || (state == WAIT_RADIUS))
		{
			//draw_parts(hCmpDC, radius, x_c, y_c);
			draw_complex(hCmpDC, radius, x_c, y_c);
		}
		// Вывод на экран
		SetStretchBltMode(hdc, COLORONCOLOR);
		BitBlt(hdc, 0, 0, Rect.right - Rect.left, Rect.bottom - Rect.top,
			hCmpDC, 0, 0, SRCCOPY);
		DeleteDC(hCmpDC);
		DeleteObject(hBmp);
		hCmpDC = NULL;
		EndPaint(hWnd, &ps);
		break;

	case WM_LBUTTONDOWN:
		int x, y;
		x = LOWORD(lParam);
		y = HIWORD(lParam);

		switch (state)
		{
		case WAIT_CENTER:
		{
			x_c = x;
			y_c = y;
			x_r = x;
			y_r = y;
			state = WAIT_RADIUS;
		}
		break;
		case WAIT_RADIUS:
		{
			//calculating radius
			int t1 = (x_r - x_c);
			int t2 = t1*t1;
			int t3 = (y_r - y_c);
			int t4 = t3*t3;
			radius = sqrt(t2 + t4);
			state = COMPLETED;
		}
		break;
		case COMPLETED:
		{
			state = WAIT_CENTER;
			InvalidateRect(hWnd, NULL, FALSE);
		}
		break;
		}
		break;

	case WM_MOUSEMOVE:
		x = LOWORD(lParam);
		y = HIWORD(lParam);
		if (state == WAIT_RADIUS) {
			x_r = x;
			y_r = y;
			int t1 = (x_r - x_c);
			int t2 = t1*t1;
			int t3 = (y_r - y_c);
			int t4 = t3*t3;
			radius = sqrt(t2 + t4);
		}
		InvalidateRect(hWnd, NULL, FALSE);
		break;

	case WM_LBUTTONUP:
		break;

	case WM_KEYDOWN:
		win_paint = !win_paint;
		InvalidateRect(hWnd, NULL, FALSE);
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	default:
		return (DefWindowProc(hWnd, messg, wParam, lParam));
	}

	return (0);
}
