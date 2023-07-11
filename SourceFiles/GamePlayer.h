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

// 大きさ 構造体
struct Size {
	int width = 0;
	int height = 0;
};

// 人 構造体
struct Person {
	int state = 0;
	int hp = 0;
	Position position;
	Size size;
};

// プレイヤークラス
class GamePlayer {
private:
	Person player;

	int fly_state = 0;
	int frameCounter = 0;
	int playerImg_state = 0;
	int img_player[32];

	// 仮
	int img_bg;

	int debug[5];


public:
	// コンストラクタ
	GamePlayer();

	// デストラクタ
	~GamePlayer();


	// 初期化
	void Init();

	// 更新
	void Update();

	// 描画
	void Draw() const;

	// プレイヤー移動
	void Control();

	// 重力を作用させる
	void Gravity();

	// プレイヤー画像のアニメーションを行う
	void Animation();

	// 跳ね返りさせる
	void Bounce();


	// プレイヤーの状態を設定
	void SetState(int State) {
		player.state = State;
	};

	// プレイヤーの状態を取得
	int GetState() {
		return player.state;
	};


	// プレイヤーのX位置を設定
	void SetPositionX(float X) {
		player.position.x = X;
	};

	// プレイヤーのY位置を設定
	void SetPositionY(float Y) {
		player.position.y = Y;
	};

	// プレイヤーの位置を取得（float型 座標 構造体）
	Position GetPosition() {
		return player.position;
	};
};
