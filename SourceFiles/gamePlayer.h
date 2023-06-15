/********************************
* ゲームプレイヤー
* 編集者：島袋
********************************/
#pragma once
#include "main.h"

// プレイヤークラス
class GamePlayer {
private:
	int state;
public:
	// コンストラクタ
	GamePlayer();

	// デストラクタ
	~GamePlayer();

	// 更新
	//void Update();

	// 描画
	void Draw() const {
		DrawFormatString(20, 100, 0xffffff, "プレイヤークラス実行中！");
	};
};
