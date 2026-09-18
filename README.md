# SimpleWindow v0.0.1
- C++で作成したWindows専用ライブラリです
- シンプルか？と言われるとそうでもない気もしますが、ご了承ください
- (AIを使用して修正したコードが含まれています)

# Requirement
- VC++14

# 使い方
- 基本的に SimpleWindow.h をインクルードすれば直ぐ使えます
- 静的ライブラリを生成して使うこともできます

# ちょっとしたサンプル集
## ギリギリ動く最小限のコード
```C++
#include"SimpleWindow.h"

int main()
{
	SW_Init();					// 座標や色などのデータを初期化
	SW_CreateWindow();			// ウィンドウの作成
	SW_Show();					// ウィンドウの表示

	while (SW_Update())			// ウィンドウを更新
	{
	}

	SW_Close();					// ウィンドウを閉じる
}
```

## キーボードの矢印キーでウィンドウが移動するサンプル
```C++
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
	float windowPosX = 0.0f;
	float windowPosY = 0.0f;
	float speed = 0.1f;

	while (SW_Update())			// ウィンドウを更新
	{
		if (SW_KeyPress(SWKey::Left))
		{
			windowPosX -= speed;
		}
		if (SW_KeyPress(SWKey::Right))
		{
			windowPosX += speed;
		}
		if (SW_KeyPress(SWKey::Up))
		{
			windowPosY -= speed;
		}
		if (SW_KeyPress(SWKey::Down))
		{
			windowPosY += speed;
		}
		SW_UpdateWindowPos((int)windowPosX, (int)windowPosY);
	}

	SW_Close();					// ウィンドウを閉じる
}
```

# 今後
- [x] メッセージボックスの表示
- [x] キーボード入力の対応
- [ ] トースト通知の表示
- [ ] タスクトレイへの収納
  などなど... 出来たらいいな
