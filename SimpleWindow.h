#pragma once
#include<Windows.h>
#include<string>

#ifdef UNICODE
using autostring = std::wstring;
#else
using autostring = std::string;
#endif

namespace data
{
	static autostring title;
	static int width;
	static int height;
	static int x;
	static int y;
	static HWND window;
	static HINSTANCE instance;
	static HICON icon;
	static HCURSOR cursor;
	static HBRUSH backColor;
}

extern void SW_Init();
extern void SW_Title(const autostring& title);
extern void SW_Size(int width, int height);
extern void SW_Pos(int x, int y);
extern void SW_Icon(const autostring& iconPath);
extern void SW_Cursor(const autostring& cursorPath);
extern void SW_DarkMode();
extern void SW_BackColor(BYTE r, BYTE g, BYTE b);
extern bool SW_IsDarkMode();
extern void SW_CreateWindow();
extern bool SW_Update();
extern void SW_Show();
extern void SW_Close();

static LRESULT CALLBACK WndProcMultibyte(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp);
static LRESULT CALLBACK WndProcWide(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp);
