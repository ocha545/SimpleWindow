#include<iostream>
#include"SimpleWindow.h"

int main()
{
	SW_Init();
	SW_Size(960, 720);
	SW_Title(L"たいとる");
	SW_BackColor(255, 0, 0);
	SW_DarkMode();
	SW_CreateWindow();
	SW_Show();

	while (SW_Update())
	{

	}

	SW_Close();

	system("pause");
}