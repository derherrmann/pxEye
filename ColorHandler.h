#pragma once
#include <Windows.h>

COLORREF gPC(HDC hdc, int x, int y);
bool IsColorInRange(COLORREF color, COLORREF targetColor, int tolerance);
bool IsColorHit(HDC hdc, int x, int y, COLORREF targetColor, int tolerance);