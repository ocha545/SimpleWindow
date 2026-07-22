#pragma once
#include<string>
#include<Windows.h>
#include<exception>
#include<dwmapi.h>
#pragma comment(lib, "dwmapi.lib")

//#include"SimpleVector2D/SimpleVector.h"

#ifdef UNICODE
using autostring = std::wstring;
#else
using autostring = std::string;
#endif

#ifndef DWMWA_USE_IMMERSIVE_DARK_MODE
#define DWMWA_USE_IMMERSIVE_DARK_MODE (20)
#endif

#ifndef NODISCARD
#define NODISCARD [[nodiscard]]
#endif

/// @brief SimpleWindowからスローされる例外の親クラスです
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

/// @brief ウィンドウハンドルが無効の時スローされる例外です
class SWInvalidHWndException : SWException
{
public:
	SWInvalidHWndException(std::string msg)
		: SWException(msg)
	{
	}
};

/// @brief HRESULTの値がS_OK以外の時にスローされる例外です
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

	//未使用！
	//static POINT cursorPos;
	//Vector2D ConvPointToVector2D(const POINT& pos);
}

/// @brief ウィンドウの作成に必要な変数を初期化します
extern void SW_Init();

/// @brief ウィンドウのタイトルを設定します
/// @param title 
extern void SW_Title(const autostring& title);

/// @brief ウィンドウの大きさを設定します
/// @param width 
/// @param height 
extern void SW_Size(int width, int height);

/// @brief ウィンドウの座標を設定します
/// @param x 
/// @param y 
extern void SW_Pos(int x, int y);

/// @brief ウィンドウのアイコンを設定します
/// @param iconPath 
extern void SW_Icon(const autostring& iconPath);

/// @brief ウィンドウ内で使うカーソル画像を設定します
/// @param cursorPath 
extern void SW_Cursor(const autostring& cursorPath);

/// @brief ウィンドウをダークモードに設定します
/// @brief SW_CreateWindow関数を実行した後にこの関数を実行してください
extern void SW_DarkMode();

/// @brief ウィンドウの背景の色を設定します
/// @param r 
/// @param g 
/// @param b 
extern void SW_BackColor(BYTE r, BYTE g, BYTE b);

/// @brief ユーザー設定でダークモードが有効かチェックします
/// @return 
extern bool SW_IsDarkMode();

/// @brief ウィンドウを作成します
extern void SW_CreateWindow();

/// @brief ウィンドウの内容を更新します
/// @return 
extern NODISCARD bool SW_Update();

/// @brief ウィンドウを表示します
extern void SW_Show();

/// @brief ウィンドウを閉じます
extern void SW_Close();

extern HWND SW_Sys_GetHWnd();
extern HINSTANCE SW_Sys_GetHInstance();

static LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp);
