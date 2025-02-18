#include <iostream>
#include "WindowHandler.h"
using namespace std;

HWND fWindow(LPCWSTR name) {
    // Handle des Fensters der Anwendung erhalten
    HWND hwnd = FindWindow(NULL, name);
    if (hwnd == NULL) {
		cerr << "Fenster nicht gefunden!" << endl;
        return NULL;
    }
    //cout << "Fenster gefunden!" << endl;
    return hwnd;
}

HDC fDC(HWND hwnd) {
    // Gerätekontext des Fensters erhalten
    HDC hdc = GetDC(hwnd);
    if (hdc == NULL) {
		cerr << "Gerätekontext konnte nicht erstellt werden!" << endl;
        return NULL;
    }
    //cout << "Gerätekontext erstellt!" << endl;
    return hdc;
}

RECT gWR(HWND hwnd) {
	// Größe des Fensters erhalten
	RECT rect;
	BOOL result = GetWindowRect(hwnd, &rect);
	if (!result) {
		cerr << "Größe des Fensters konnte nicht erhalten werden!" << endl;
		return rect;
	}
	//cout << "Größe des Fensters erhalten!" << endl;
	return rect;
}

BOOL isWinForeground(HWND hwnd) {
	// Prüfen, ob Fenster im Vordergrund ist
	HWND foreground = GetForegroundWindow();
	if (foreground == hwnd) {
		//cout << "Fenster ist im Vordergrund!" << endl;
		return TRUE;
	}
	cout << "Fenster ist nicht im Vordergrund!" << endl;
	return FALSE;
}