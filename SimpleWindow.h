#pragma once
#include<string>
#include<Windows.h>
#include<exception>
#include<dwmapi.h>
#pragma comment(lib, "dwmapi.lib")


#ifdef UNICODE
using autostring = std::wstring;
#else
using autostring = std::string;
#endif

#ifndef DWMWA_USE_IMMERSIVE_DARK_MODE
#define DWMWA_USE_IMMERSIVE_DARK_MODE (20)
#endif

class SWException : std::exception
{
private:
	std::string message;

public:
	SWException(const std::string& msg)
		: message(msg)
	{
	}

	char const* what() const noexcept
	{
		return message.c_str();
	}
};

class SWInvalidHWndException : SWException
{
public:
	SWInvalidHWndException(std::string msg)
		: SWException(msg)
	{
	}
};

class SWFailureResultException : SWException
{
public:
	SWFailureResultException(std::string msg)
		: SWException(msg)
	{
	}
};

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

/// <summary>
/// ウィンドウを作成するのに必要な変数を初期化します
/// </summary>
extern void SW_Init();

/// <summary>
/// ウィンドウのタイトルを設定します
/// </summary>
/// <param name="title"></param>
extern void SW_Title(const autostring& title);

/// <summary>
/// ウィンドウの大きさを設定します
/// </summary>
/// <param name="width"></param>
/// <param name="height"></param>
extern void SW_Size(int width, int height);

/// <summary>
/// ウィンドウの座標を設定します
/// </summary>
/// <param name="x"></param>
/// <param name="y"></param>
extern void SW_Pos(int x, int y);

/// <summary>
/// ウィンドウのアイコンを設定します
/// </summary>
/// <param name="iconPath"></param>
extern void SW_Icon(const autostring& iconPath);

/// <summary>
/// ウィンドウ内で使うカーソル画像を設定します
/// </summary>
/// <param name="cursorPath"></param>
extern void SW_Cursor(const autostring& cursorPath);

/// <summary>
/// ウィンドウをダークモードに設定します
/// </summary>
extern void SW_DarkMode();

/// <summary>
/// ウィンドウの背景の色を設定します
/// </summary>
/// <param name="r"></param>
/// <param name="g"></param>
/// <param name="b"></param>
extern void SW_BackColor(BYTE r, BYTE g, BYTE b);

/// <summary>
/// ユーザー設定でダークモードが有効かチェックします
/// </summary>
/// <returns></returns>
extern bool SW_IsDarkMode();

/// <summary>
/// ウィンドウを作成します
/// </summary>
extern void SW_CreateWindow();

/// <summary>
/// ウィンドウの内容を更新します
/// </summary>
/// <returns></returns>
extern bool SW_Update();

/// <summary>
/// ウィンドウを表示します
/// </summary>
extern void SW_Show();

/// <summary>
/// ウィンドウを閉じます
/// </summary>
extern void SW_Close();


static LRESULT CALLBACK WndProcMultibyte(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp);
static LRESULT CALLBACK WndProcWide(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp);
