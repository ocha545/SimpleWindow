#include<iostream>
#include"SimpleWindow.h"

int main()
{
	SW_Init();					// (必須!)座標や色などのデータを初期化
	SW_Size(960, 720);			// ウィンドウサイズの設定
	SW_Title(L"たいとる");		// ウィンドウタイトルの設定
	SW_BackColor(0, 255, 0);	// 背景色の設定(R, G, B)
	SW_CreateWindow();			// (必須!)ウィンドウの作成
	SW_EnableDarkMode();		// ダークモードの有効化
	SW_Show();					// (必須!)ウィンドウの表示
		
	while (SW_Update())			// ウィンドウを更新
	{
		if (SW_MouseRClick())
		{
		}
	}

	SW_Close();					// ウィンドウを閉じる
}