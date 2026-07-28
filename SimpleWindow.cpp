#include"SimpleWindow.h"

void SW_Init()
{
	data::title = autostring();
	data::width = 300;
	data::height = 300;
	data::x = 0;
	data::y = 0;
	data::icon = LoadIcon(NULL, IDC_ICON);
	data::cursor = LoadCursor(NULL, IDC_ARROW);
	data::window = nullptr;
	data::instance = GetModuleHandle(nullptr);
	data::backColor = (HBRUSH)DKGRAY_BRUSH;
	data::mouseLClick = false;
	data::mouseRClick = false;
	data::mouseMClick = false;
	//data::cursorPos;
}

void SW_Title(const autostring& title)
{
	data::title = title;
}

void SW_Size(int width, int height)
{
	data::width = width;
	data::height = height;
	data::x = (::GetSystemMetrics(SM_CXSCREEN) - width) >> 1;
	data::y = (::GetSystemMetrics(SM_CYSCREEN) - height) >> 1;
}

void SW_Pos(int x, int y)
{
	data::x = x;
	data::y = y;
}

void SW_Icon(const autostring& iconPath)
{
	data::icon = (HICON)LoadImage(data::instance, iconPath.c_str(), IMAGE_ICON, 0, 0, LR_LOADFROMFILE);
}

void SW_Cursor(const autostring& cursorPath)
{
	data::cursor = (HCURSOR)LoadImage(data::instance, cursorPath.c_str(), IMAGE_CURSOR, 0, 0, LR_LOADFROMFILE);
}

void SW_EnableDarkMode()
{
	if (!data::window)
	{
		throw SWInvalidHWndException("HWNDが無効です。SW_CreateWindowをした後実行してください");
	}
	BOOL value = TRUE;//ダークモードを有効化！
	HRESULT res = DwmSetWindowAttribute(data::window, DWMWA_USE_IMMERSIVE_DARK_MODE, &value, sizeof(value));

	if (FAILED(res))
	{
		throw SWFailureResultException("ダークモードの有効化に失敗しました");
	}
}

void SW_EnableForegroundWindow()
{
	data::foregroundWindow = SetWindowPos(data::window, HWND_TOPMOST, data::x, data::y, data::width, data::height, SWP_NOSIZE | SWP_NOMOVE);
}

void SW_DisableForegroundWindow()
{
	if (data::foregroundWindow)
	{
		data::foregroundWindow = !SetWindowPos(data::window, HWND_NOTOPMOST, data::x, data::y, data::width, data::height, SWP_NOSIZE | SWP_NOMOVE);
	}
}

bool SW_IsDarkMode()
{
	return false;
}

void SW_BackColor(BYTE r, BYTE g, BYTE b)
{
	COLORREF color = (0x00 << 24) | (r << 16) | (g << 8) | (b);
	data::backColor = CreateSolidBrush(color);
}

bool SW_Update()
{
	data::mouseLClickPrev = data::mouseLClick;
	data::mouseRClickPrev = data::mouseRClick;
	data::mouseMClickPrev = data::mouseMClick;

	MSG message{};
	while (PeekMessage(&message, NULL, 0, 0, PM_REMOVE))
	{
		if (message.message == WM_QUIT)
		{
			return false;
		}
		TranslateMessage(&message);
		DispatchMessage(&message);
	}

	return true;
}

void SW_UpdateTitle(const autostring& title)
{
	if (::SetWindowText(data::window, title.c_str()) == FALSE)
	{
		// 失敗したらログ出力をする
		// 致命的なエラーではないので例外は投げません
	}
}

void SW_UpdateWindowPos(int x, int y)
{
	if (data::x != x || data::y != y)
	{
		SetWindowPos(data::window, HWND_TOP, x, y, data::width, data::height, SWP_NOSIZE);
	}
}

void SW_Show()
{
	ShowWindow(data::window, SW_SHOW);
}

void SW_Close()
{
	DeleteObject(data::backColor);
	PostQuitMessage(0);
	PostMessage(data::window, WM_CLOSE, 0, 0);
}

bool SW_MouseLClick()
{
	return SW_Sys_MouseLUp();
}

bool SW_MouseRClick()
{
	return SW_Sys_MouseRUp();
}

bool SW_MouseWheelClick()
{
	return SW_Sys_MouseMUp();
}

Result SW_ShowMessageBox(const autostring& title, const autostring& message, long flag)
{
	return SW_Sys_MessageBox(data::window, data::instance, title, message, flag);
}

Result SW_ShowMessageBoxOk(const autostring& title, const autostring& message)
{
	return SW_Sys_MessageBox(data::window, data::instance, title, message, Button::Ok | Icon::Information);
}

Result SW_ShowMessageBoxYesNo(const autostring& title, const autostring& message)
{
	return SW_Sys_MessageBox(data::window, data::instance, title, message, Button::YesNo | Icon::Information);
}

void SW_CreateWindow()
{
	//DPI対応
	::SetProcessDpiAwarenessContext(DPI_AWARENESS_CONTEXT_PER_MONITOR_AWARE_V2);

	WNDCLASSEX windowClass{};
	windowClass.cbSize = sizeof(windowClass);
	windowClass.style = CS_HREDRAW | CS_VREDRAW;
	windowClass.hInstance = data::instance;
	windowClass.hIcon = data::icon;
	windowClass.hCursor = data::cursor;
	windowClass.hbrBackground = data::backColor;
	windowClass.lpfnWndProc = WndProc;
#ifdef UNICODE
	windowClass.lpszClassName = L"Simple Window ^_^;";
#else
	windowClass.lpszClassName = "Simple Window ^_^;";
#endif
	RegisterClassEx(&windowClass);

	RECT windowRect{};
	windowRect.left = 0;
	windowRect.top = 0;
	windowRect.right = data::width;
	windowRect.bottom = data::height;
	AdjustWindowRect(&windowRect, WS_OVERLAPPEDWINDOW, FALSE);
	int windowWidth = windowRect.right - windowRect.left;
	int windowHeight = windowRect.bottom - windowRect.top;

	data::window = CreateWindowEx(
		NULL, windowClass.lpszClassName, data::title.c_str(), WS_OVERLAPPEDWINDOW,
		data::x, data::y, windowWidth, windowHeight,
		NULL, FALSE, data::instance, NULL
	);
}

HWND SW_Sys_GetHWnd()
{
	return data::window;
}

HINSTANCE SW_Sys_GetHInstance()
{
	return data::instance;
}

Result SW_Sys_MessageBox(HWND handle, HINSTANCE instance, const autostring& title, const autostring& message, long flag)
{
	MSGBOXPARAMS params{};
	params.cbSize = sizeof(params);
	params.hwndOwner = handle;
	params.hInstance = instance;
	params.lpszCaption = title.c_str();
	params.lpszText = message.c_str();
	params.dwStyle = flag;

	switch (MessageBoxIndirect(&params))
	{
	case IDOK:			return Result::Ok;
	case IDCANCEL:		return Result::Cancel;
	case IDABORT:		return Result::Abort;
	case IDRETRY:		return Result::Retry;
	case IDIGNORE:		return Result::Ignore;
	case IDYES:			return Result::Yes;
	case IDNO:			return Result::No;
	case IDTRYAGAIN:	return Result::TryAgain;
	case IDCONTINUE:	return Result::Continue;
	default:			return Result::Null;
	}
	return Result::Null;
}

bool SW_Sys_MouseLDown()
{
	return data::mouseLClick && !data::mouseLClickPrev;
}
bool SW_Sys_MouseLUp()
{
	return !data::mouseLClick && data::mouseLClickPrev;
}
bool SW_Sys_MouseLPress()
{
	return data::mouseLClick;
}
bool SW_Sys_MouseRDown()
{
	return data::mouseRClick && !data::mouseRClickPrev;
}
bool SW_Sys_MouseRUp()
{
	return !data::mouseRClick && data::mouseRClickPrev;
}
bool SW_Sys_MouseRPress()
{
	return data::mouseLClick;
}

bool SW_Sys_MouseMDown()
{
	return data::mouseMClick && !data::mouseMClickPrev;
}
bool SW_Sys_MouseMUp()
{
	return !data::mouseMClick && data::mouseMClickPrev;
}
bool SW_Sys_MouseMPress()
{
	return data::mouseMClick;
}



long operator|(Button b, Icon i)
{
	return (long)b | (long)i;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp)
{
	switch (msg)
	{
	case WM_CREATE:
	{
		RAWINPUTDEVICE rawInputDevice[1]{};
		rawInputDevice[SW_RAWINPUT_INDEX_MOUSE].usUsagePage = 0x01;
		rawInputDevice[SW_RAWINPUT_INDEX_MOUSE].usUsage = 0x02;
		rawInputDevice[SW_RAWINPUT_INDEX_MOUSE].dwFlags = RIDEV_INPUTSINK;
		rawInputDevice[SW_RAWINPUT_INDEX_MOUSE].hwndTarget = hWnd;
		RegisterRawInputDevices(rawInputDevice, _countof(rawInputDevice), sizeof(RAWINPUTDEVICE));
	}
	return DefWindowProc(hWnd, msg, wp, lp);

	case WM_CLOSE:
		DestroyWindow(hWnd);
		return 0;

	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;

	case WM_INPUT:
	{
		RAWINPUT rawInput{};
		UINT dwSize = sizeof(rawInput);
		GetRawInputData((HRAWINPUT)lp, RID_INPUT, &rawInput, &dwSize, sizeof(RAWINPUTHEADER));

		if (rawInput.header.dwType == RIM_TYPEMOUSE)
		{
			if ((rawInput.data.mouse.usButtonFlags & RI_MOUSE_LEFT_BUTTON_DOWN) != 0)
			{
				data::mouseLClick = true;
			}
			if ((rawInput.data.mouse.usButtonFlags & RI_MOUSE_LEFT_BUTTON_UP) != 0)
			{
				data::mouseLClick = false;
			}
			if ((rawInput.data.mouse.usButtonFlags & RI_MOUSE_RIGHT_BUTTON_DOWN) != 0)
			{
				data::mouseRClick = true;
			}
			if ((rawInput.data.mouse.usButtonFlags & RI_MOUSE_RIGHT_BUTTON_UP) != 0)
			{
				data::mouseRClick = false;
			}
			if ((rawInput.data.mouse.usButtonFlags & RI_MOUSE_MIDDLE_BUTTON_DOWN) != 0)
			{
				data::mouseMClick = true;
			}
			if ((rawInput.data.mouse.usButtonFlags & RI_MOUSE_MIDDLE_BUTTON_UP) != 0)
			{
				data::mouseMClick = false;
			}
		}
	}
	return DefWindowProc(hWnd, msg, wp, lp);


	default:
		return DefWindowProc(hWnd, msg, wp, lp);
	}
}
