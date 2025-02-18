#pragma once
#include <Windows.h>

HWND fWindow(LPCWSTR name);
HDC fDC(HWND hwnd);
RECT gWR(HWND hwnd);
BOOL isWinForeground(HWND hwnd);