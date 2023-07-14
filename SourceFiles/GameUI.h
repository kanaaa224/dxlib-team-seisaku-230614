/********************************
* ゲームUI
* 担当：島袋
********************************/
#pragma once
#include "main.h"

// プレイヤークラス
class GameUI {
private:

public:
	// コンストラクタ
	GameUI();

	// デストラクタ
	~GameUI();

	// 更新
	void Update();

	// 描画
	void Draw() const;
};