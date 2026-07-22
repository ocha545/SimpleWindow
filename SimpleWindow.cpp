#include"SimpleWindow.h"

void SW_Init()
{
	data::title = autostring();
	data::width = 100;
	data::height = 100;
	data::x = 0;
	data::y = 0;
	data::icon = LoadIcon(NULL, IDC_ICON);
	data::cursor = LoadCursor(NULL, IDC_ARROW);
	data::window = nullptr;
	data::instance = GetModuleHandle(nullptr);
	data::backColor = (HBRUSH)DKGRAY_BRUSH;
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
	data::cursor = (HCURSOR)LoadImage(data::instance, cursorPath.c_str(), IMAGE_ICON, 0, 0, LR_LOADFROMFILE);
}

void SW_DarkMode()
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

bool SW_IsDarkMode()
{
	return false;
}

void SW_BackColor(BYTE r, BYTE g, BYTE b)
{
	COLORREF color = (0x00 << 24) | (r << 16) | (g << 8) | (b);
	data::backColor = CreateSolidBrush(color);
}

NODISCARD bool SW_Update()
{
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

void SW_CreateWindow()
{
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

extern HWND SW_Sys_GetHWnd()
{
	return data::window;
}

extern HINSTANCE SW_Sys_GetHInstance()
{
	return data::instance;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp)
{
	switch (msg)
	{
	case WM_CREATE:
	{
		//RAWINPUTDEVICE rawInputDevice{};
		//rawInputDevice.usUsagePage = 0x01;
		//rawInputDevice.usUsage = 0x02;
		//rawInputDevice.dwFlags = RIDEV_INPUTSINK;
		//rawInputDevice.hwndTarget = data::window;
		//RegisterRawInputDevices(&rawInputDevice, 1, sizeof(RAWINPUTDEVICE));
		//GetCursorPos(&data::cursorPos);
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
		//RAWINPUT rawInput{};
		//UINT rawInputSize = (UINT)sizeof(rawInput);
		//GetRawInputData((HRAWINPUT)lp, RID_INPUT, &rawInput, &rawInputSize, sizeof(RAWINPUTHEADER));
		//if (rawInput.header.dwType == RIM_TYPEMOUSE)
		//{
		//	GetCursorPos(&data::cursorPos);
		//}
	}
	return DefWindowProc(hWnd, msg, wp, lp);


	default:
		return DefWindowProc(hWnd, msg, wp, lp);
	}
}


//Vector2D data::ConvPointToVector2D(const POINT& pos)
//{
//	return Vector2D{
//		(double)pos.x,
//		(double)pos.y
//	};
//}
