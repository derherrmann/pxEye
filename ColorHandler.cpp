#include <iostream>
#include "ColorHandler.h"
using namespace std;

COLORREF gPC(HDC hdc, int x, int y) {
    // Farbe des Pixels erhalten
    COLORREF color = GetPixel(hdc, x, y);
    if (color == CLR_INVALID) {
        cerr << "Farbe des Pixels konnte nicht erhalten werden!" << endl;
        return NULL;
    }
    int r = GetRValue(color);
    int g = GetGValue(color);
    int b = GetBValue(color);
	//cout << "Farbe des Pixels erhalten R: " << r << " G: " << g << " B: " << b << endl;
    return color;
}

bool IsColorInRange(COLORREF color, COLORREF targetColor, int tolerance) {
	// Prüfen, ob zwei Farben innerhalb einer bestimmten Toleranz liegen
    int r = GetRValue(color);
    int g = GetGValue(color);
    int b = GetBValue(color);

    int targetR = GetRValue(targetColor);
    int targetG = GetGValue(targetColor);
    int targetB = GetBValue(targetColor);

    return (abs(r - targetR) <= tolerance) &&
        (abs(g - targetG) <= tolerance) &&
        (abs(b - targetB) <= tolerance);
}

bool IsColorHit(HDC hdc, int x, int y, COLORREF targetColor, int tolerance) {
	// Prüfen, ob die Farbe des Pixels innerhalb einer bestimmten Toleranz liegt
    COLORREF color = gPC(hdc, x, y);
    if (IsColorInRange(color, targetColor, tolerance)) {
        return TRUE;
    }
    return FALSE;
}