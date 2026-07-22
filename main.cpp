#include<iostream>
#include"SimpleWindow.h"

int main()
{
	SW_Init();
	SW_Size(960, 720);
	SW_Title(L"たいとる");
	SW_BackColor(0, 255, 0);
	SW_CreateWindow();
	SW_DarkMode();
	SW_Show();

	while (SW_Update())
	{
	}

	SW_Close();
}