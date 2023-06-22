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

	int img_bg;

	int x, y; // プレイヤー座標
	int w, h; // プレイヤーの幅と高さ

public:
	// コンストラクタ
	GamePlayer();

	// デストラクタ
	~GamePlayer();

	// 更新
	void Update();

	// 描画
	void Draw() const;
};
