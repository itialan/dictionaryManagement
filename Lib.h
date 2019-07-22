#pragma once
#include <windows.h>

void Gotoxy(int x, int y);
void ShowCur(bool CursorVisibility);
void resizeConsole(int width, int height);
void SetBGColor(WORD color);
