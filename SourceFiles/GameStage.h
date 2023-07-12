/********************************
* ゲームステージ
* 編集者：
********************************/
#pragma once
#include "common.h"
#include "AbstractScene.h"

// プレイヤークラス
class GameStage {
private:
	int img_bg;
	int img_bg1;

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
