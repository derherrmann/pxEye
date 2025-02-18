#include <iostream>
#include <fstream>
#include <thread>
#include <atomic>
#include <Windows.h>
#include <unordered_map>
#include "WindowHandler.h"
#include "ColorHandler.h"
#include "KeyHandler.h"
using namespace std;

struct skill {
    int sx;
    int sy;
    COLORREF scolor;
	int isbar;
	int bx;
	int by;
	COLORREF bcolor;
};
static unordered_map<int, skill> dict;
atomic<bool> run(false);

static void checkK() {
	while (true) {
		if (GetAsyncKeyState(0x70) & 1) { // KEY F1
			run = !run;
			cout << (run ? "Programm läuft" : "Programm pasiert") << endl;
		}
		Sleep(0x64); // 100ms
	}
}

static void lSkillsfFile(const string& path) {
    // Skills aus Datei laden
    ifstream file(path);
    if (!file) {
        cerr << "Datei konnte nicht geladen werden!" << endl;
        return;
    }

	int id, sx, sy, sred, sgreen, sblue;
	int isbar, bx, by, bred, bgreen, bblue;

	while (file >> id >> sx >> sy >> sred >> sgreen >> sblue >> isbar >> bx >> by >> bred >> bgreen >> bblue) {
		dict.emplace(id, skill{ sx, sy, RGB(sred, sgreen, sblue), isbar, bx, by, RGB(bred, bgreen, bblue) });
        //dict[id] = { x, y, RGB(r, g, b) };
    }
    file.close();
}


static int process() {
	LPCWSTR name = L"Diablo IV";
	int stolerance = 0x14; // 20
	int btolerance = 0x14; // 20
	int key = 0x31; // KEY 1

	HWND hwnd = fWindow(name);
	if (hwnd == NULL) {
		return 1;
	}

	if (!isWinForeground(hwnd)) {
		return 1;
	}

	HDC hdc = fDC(NULL);
	if (hdc == NULL) {
		return 1;
	}

	RECT rect = gWR(hwnd);
	if (rect.right == 0 || rect.bottom == 0) {
		cerr << "Fenstergröße konnte nicht erhalten werden!" << endl;
		return 1;
	}

	for (const auto& [id, s] : dict) {
		// Skill prüfen

		int barPosX = rect.left + s.bx;
		int barPosY = rect.top + s.by;
		int skillPosX = rect.left + s.sx;
		int skillPosY = rect.top + s.sy;

		if (s.isbar) {
			if (IsColorHit(hdc, barPosX, barPosY, s.bcolor, btolerance) && 
				IsColorHit(hdc, skillPosX, skillPosX, s.scolor, stolerance)) {
				cout << "Skill " << id + 1 << " wird ausgeführt!" << endl;
				sendK(key + id);
				continue;
			} 
		}

		COLORREF color = gPC(hdc, rect.left + s.sx, rect.top + s.sy);
		if (!IsColorInRange(color, s.scolor, stolerance)) {
			cout << "Skill " << id + 1 << " wird ausgeführt!" << endl;
			sendK(key + id);
		}
	}
	ReleaseDC(hwnd, hdc);

    return 0;
}

int main() {
	lSkillsfFile("skills.txt");

	if (dict.empty()) {
		cerr << "Leere Datei du Eimer!" << endl;
		return 1;
	}

	thread runThread(checkK);
	runThread.detach();
	cout << "Drücke F1 zum Starten/Pausieren" << endl;
	while (true) {
		if (run) {
			process();
		}
		Sleep(0x64); // 100ms
	}
}
