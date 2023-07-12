/********************************
* ゲームプレイヤー
* 編集者：島袋
********************************/
#pragma once
#include "main.h"

#define PLAYER_STOP 0
#define PLAYER_WALK 1
#define PLAYER_FLIGHT 2

#define PLAYER_L_STOP 0
#define PLAYER_R_STOP 1
#define PLAYER_L_WALK 2
#define PLAYER_R_WALK 3
#define PLAYER_L_SLIP 4
#define PLAYER_R_SLIP 5
#define PLAYER_L_FLIGHT 6
#define PLAYER_R_FLIGHT 7

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

	int state = 0;
	int fly_state = 0;
	int frameCounter = 0;
	int playerImg_state = 0; // 0-2: 風船２個の待機 | 4-6: 風船２個の待機 | 8-11: 風船２個の歩行 | 12-15: 風船１個の歩行 | 15-20: 風船２個の飛行 | 21-23: 死亡 | 24-28: 風船１個の飛行
	int img_player[32];

	int keyInput_state[3];
	int speed[4];
	int move[4];

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
	bool Control();

	// 重力を作用させる
	void Gravity();

	// プレイヤー画像のアニメーションを行う
	void Animation();

	// 跳ね返りさせる
	void Bounce();


	// プレイヤーの状態を設定
	void SetState(int State) {
		state = State;
	};

	// プレイヤーの状態を取得
	int GetState() {
		return state;
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


	// プレイヤーのサイズを取得（大きさ 構造体）
	Size GetSize() {
		return player.size;
	};
};
