/********************************
* ゲームステージ
* 編集者：
********************************/
#pragma once
#include "main.h"

// プレイヤークラス
class GameStage{
private:
	int img_bg;
	int img_bg1;
	int cloudimg[2];//雲の画像用

public:
	// コンストラクタ
	GameStage();

	// デストラクタ
	~GameStage();

	// 更新
	void Update();

	// 描画
	void Draw() const;

	void HitStage();
};