#include "KeyHandler.h"
using namespace std;

void sendK(WORD key) {
	// Menschlichen Tastendruck simulieren

	// Zufallsgenerator initialisieren
	static random_device rd;
	static mt19937 gen(rd());
	static uniform_int_distribution<> dist(0x32, 0xFA); // 50 - 250ms

	INPUT input = { 0 };

	// Definiere Taste drücken
	input.type = INPUT_KEYBOARD;
	input.ki.wVk = key;
	SendInput(1, &input, sizeof(INPUT)); // Drücken

	int rndmPressDur = dist(gen);
	Sleep(rndmPressDur);

	// Definiere Taste loslassen
	input.ki.dwFlags = KEYEVENTF_KEYUP;
	SendInput(1, &input, sizeof(INPUT)); // Loslassen
}
