/********************************
* ゲームステージ
* 編集者：
********************************/
#pragma once
#include "main.h"

// プレイヤークラス
class GameStage{
private:
	int img_sea;      // 海
	int img_footing;  // 足場
	int img_cloud[2]; // 雲の画像用

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