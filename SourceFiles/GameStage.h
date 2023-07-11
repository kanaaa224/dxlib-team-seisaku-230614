/********************************
* ゲームステージ
* 編集者：
********************************/
#pragma once
#include "common.h"
#include "AbstractScene.h"

// プレイヤークラス
class GameStage :public AbstractScene{
private:
	int img_bg;
	int img_bg1;

public:
	// コンストラクタ
	GameStage();

	// デストラクタ
	~GameStage();

	// 更新
	virtual AbstractScene* Update() override;

	// 描画
	virtual void Draw() const override;
};
