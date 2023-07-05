/********************************
* ゲームプレイヤー
* 編集者：島袋
********************************/
#pragma once
#include "main.h"

// float型 2次元座標 構造体
struct Position {
	float x = 0.0f;
	float y = 0.0f;
};

// 人構造体
struct Person {
	int state = 0;
	Position position;
	int width, height;
};

// プレイヤークラス
class GamePlayer {
private:
	Person player;

	int fly_state = 0;

	int frameCounter = 0;

	int state;

	int img_player[32];

	int img_bg;


public:
	// コンストラクタ
	GamePlayer();

	// デストラクタ
	~GamePlayer();

	// 更新
	void Update();

	// 描画
	void Draw() const;

	// プレイヤー移動
	void Control();

	// 重力を作用させる
	void Gravity();
};
