/********************************
* ゲームステージ
* 編集者：
********************************/
#pragma once
#include "main.h"

// プレイヤークラス
class GameStage {
private:
	int state;

	int img_bg;

	int x, y; // プレイヤー座標
	int w, h; // プレイヤーの幅と高さ

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
