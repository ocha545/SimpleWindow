/// @file SampleWindow.h
/// @brief 楽に使えるウィンドウ周りのライブラリです


#pragma once
#include<string>
#include<Windows.h>
#include<exception>
#include<dwmapi.h>
#include<unordered_set>	
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

#ifndef SW_RAWINPUT_INDEX_MOUSE
#define SW_RAWINPUT_INDEX_MOUSE (0)
#endif

#ifndef SW_RAWINPUT_INDEX_KEYBOARD
#define SW_RAWINPUT_INDEX_KEYBOARD (1)
#endif

/// @brief SimpleWindowからスローされる例外の親クラスです
class SWException : public std::exception
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
class SWInvalidHWndException : public SWException
{
public:
	SWInvalidHWndException(std::string msg)
		: SWException(msg)
	{
	}
};

/// @brief HRESULTの値がS_OK以外の時にスローされる例外です
class SWFailureResultException : public SWException
{
public:
	SWFailureResultException(std::string msg)
		: SWException(msg)
	{
	}
};

enum class SWResult : long
{
	Ok = IDOK,
	Cancel = IDCANCEL,
	Abort = IDABORT,
	Retry = IDRETRY,
	Ignore = IDIGNORE,
	Yes = IDYES,
	No = IDNO,
	TryAgain = IDTRYAGAIN,
	Continue = IDCONTINUE,
	Null = NULL,
};
enum class SWButton : long
{
	Ok = MB_OK,
	OkCancel = MB_OKCANCEL,
	AbortRetryIgnore = MB_ABORTRETRYIGNORE,
	YesNoCancel = MB_YESNOCANCEL,
	YesNo = MB_YESNO,
	RetryCancel = MB_RETRYCANCEL,
	CancelTryContinue = MB_CANCELTRYCONTINUE,
};
enum class SWIcon : long
{
	Hand = MB_ICONERROR,
	Stop = MB_ICONERROR,
	Error = MB_ICONERROR,
	Question = MB_ICONQUESTION,
	Exclamation = MB_ICONWARNING,
	Warning = MB_ICONWARNING,
	Asterisk = MB_ICONINFORMATION,
	Information = MB_ICONINFORMATION,
};
long operator|(SWButton b, SWIcon i);

enum class SWKey : UINT
{
	Backspace = VK_BACK,
	Tab = VK_TAB,
	Clear = VK_CLEAR,
	Enter = VK_RETURN,
	Shift = VK_SHIFT,
	Ctrl = VK_CONTROL,
	Alt,
	Pause,
	CapsLock,
	KANA,
	IME_HANGUL = KANA,
	IME_ON,
	IME_JUNJA,
	IME_Final,
	IME_HANJA,
	IME_KANJI = IME_HANJA,
	IME_OFF = VK_IME_OFF,
	Escape,
	IME_CONVERT,
	IME_NONCONVERT,
	IME_ACCEPT,
	IME_MODE_CHANGE,
	Space,
	PageUp,
	PageDown,
	End,
	Home,
	Left,
	Up,
	Right,
	Down,
	Select,
	Print,
	Execute,
	Snapshot,
	Insert,
	Delete,
	Help,
	NUM_0 = 0x30,
	NUM_1,
	NUM_2,
	NUM_3,
	NUM_4,
	NUM_5,
	NUM_6,
	NUM_7,
	NUM_8,
	NUM_9,
	A = 0x41,
	B,
	C,
	D,
	E,
	F,
	G,
	H,
	I,
	J,
	K,
	L,
	M,
	N,
	O,
	P,
	Q,
	R,
	S,
	T,
	U,
	V,
	W,
	X,
	Y,
	Z,
	Win,
	RWin,
	Apps,
	Sleep = VK_SLEEP,
	NUMPAD_0,
	NUMPAD_1,
	NUMPAD_2,
	NUMPAD_3,
	NUMPAD_4,
	NUMPAD_5,
	NUMPAD_6,
	NUMPAD_7,
	NUMPAD_8,
	NUMPAD_9,
	Multiply,
	Add,
	Separator,
	Subtract,
	Decimal,
	Divide,
	F1,
	F2,
	F3,
	F4,
	F5,
	F6,
	F7,
	F8,
	F9,
	F10,
	F11,
	F12,
	F13,
	F14,
	F15,
	F16,
	F17,
	F18,
	F19,
	F20,
	F21,
	F22,
	F23,
	F24,
	NumLock = VK_NUMLOCK,
	Scroll,
	LShift = VK_LSHIFT,
	RShift,
	LCtrl,
	RCtrl,
	LAlt,
	RAlt,
	BROWSER_BACK,
	BROWSER_FORWARD,
	BROWSER_REFRESH,
	BROWSER_STOP,
	BROWSER_SEARCH,
	BROWSER_FAVORITES,
	BROWSER_HOME,
	VOLUMME_Mute,
	VOLUMME_Down,
	VOLUMME_Up,
	MEDIA_NextTrack,
	MEDIA_PrevTrack,
	MEDIA_STOP,
	MEDIA_PLAY_PAUSE,
	LAUNCH_MAIL,
	LAUNCH_MEDIA_SELECT,
	LAUNCH_APP1,
	LAUNCH_APP2,
	//ここから先は不要っぽいので書きません
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
	static bool foregroundWindow;
	static bool mouseLClickPrev;
	static bool mouseRClickPrev;
	static bool mouseMClickPrev;
	static bool mouseLClick;
	static bool mouseRClick;
	static bool mouseMClick;
	static std::unordered_set<short> keyboardDowns;
	static std::unordered_set<short> keyboardDownsPrev;
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
extern void SW_EnableDarkMode();

/// @brief ウィンドウを最前面に固定します
extern void SW_EnableForegroundWindow();

/// @brief ウィンドウの固定を解除します
extern void SW_DisableForegroundWindow();

/// @brief ウィンドウの背景の色を設定します
/// @brief 0 から 255までの値を使用してください
/// @param r 
/// @param g 
/// @param b 
extern void SW_BackColor(BYTE r, BYTE g, BYTE b);

/// @brief ユーザー設定でダークモードが有効かチェックします(未実装)
/// @return true(未実装の為)
extern bool SW_IsDarkMode();

/// @brief ウィンドウを作成します
extern void SW_CreateWindow();

/// @brief ウィンドウの内容を更新します
/// @return 
extern bool SW_Update();

/// @brief ウィンドウタイトルを更新します
/// @brief 処理が重たいのでループ内で使用するのはご遠慮下さい
/// @param title 
extern void SW_UpdateTitle(const autostring& title);

/// @brief ウィンドウの座標を変更します
/// @param x 
/// @param y 
extern void SW_UpdateWindowPos(int x, int y);

/// @brief ウィンドウを表示します
extern void SW_Show();

/// @brief ウィンドウを閉じます
extern void SW_Close();

/// @brief マウスの左クリックを判定します
/// @return 
extern bool SW_MouseLClick();

/// @brief マウスの右クリックを判定します
/// @return 
extern bool SW_MouseRClick();

/// @brief マウスのホイールクリックを判定します
/// @return 
extern bool SW_MouseWheelClick();

extern bool SW_KeyDown(SWKey key);

extern bool SW_KeyUp(SWKey key);

extern bool SW_KeyPress(SWKey key);

/// @brief メッセージボックスを表示します
/// @param title 
/// @param message 
/// @param flag Button列挙体とIcon列挙体を使ってカスタムします
/// @return 
extern SWResult SW_ShowMessageBox(const autostring& title, const autostring& message, long flag);

/// @brief メッセージボックスをOKボタンで表示します
/// @param title 
/// @param message 
/// @return Result::Ok が返されます
extern SWResult SW_ShowMessageBoxOk(const autostring& title, const autostring& message);

/// @brief メッセージボックスをYesNoボタンで表示します
/// @param title 
/// @param message 
/// @return Result::Yes か Result::No が返されます
extern SWResult SW_ShowMessageBoxYesNo(const autostring& title, const autostring& message);

extern HWND SW_Sys_GetHWnd();
extern HINSTANCE SW_Sys_GetHInstance();
extern SWResult SW_Sys_MessageBox(HWND handle, HINSTANCE instance, const autostring& title, const autostring& message, long flag);
extern bool SW_Sys_MouseLDown();
extern bool SW_Sys_MouseLUp();
extern bool SW_Sys_MouseLPress();
extern bool SW_Sys_MouseRDown();
extern bool SW_Sys_MouseRUp();
extern bool SW_Sys_MouseRPress();
extern bool SW_Sys_MouseMDown();
extern bool SW_Sys_MouseMUp();
extern bool SW_Sys_MouseMPress();

extern LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp);
