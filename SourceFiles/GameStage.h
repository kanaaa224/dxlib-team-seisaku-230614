/********************************
* ゲームステージ
* 編集者：
********************************/
#pragma once
#include "main.h"

// プレイヤークラス
class GameStage {
private:
	int img_bg;

public:
	// コンストラクタ
	GameStage();

	// デストラクタ
	~GameStage();

	// 更新
	void Update();

	// 描画
	void Draw() const;
};
