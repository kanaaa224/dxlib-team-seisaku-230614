/********************************
* ゲームプレイヤー
* 担当：島袋
********************************/
#pragma once
#include "common.h"

//ブロック1つのサイズ(正方形)
#define BLOCK_SIZE SCREEN_WIDTH / 32

#define MOVE_SPEED 0
#define FALL_SPEED 1

// float型 2次元座標 構造体
struct Position {
	float x = 0.0f;
	float y = 0.0f;
};

// 大きさ 構造体
struct Size {
	float width = 0;
	float height = 0;
};

// 人 構造体
struct Person {
	Position position;
	Size size;
	int state = 0;
	int hp = 0;
};

class GamePlayer {
private:
	Person player;  // プレイヤーの位置、サイズ、状態、風船の状態

	float inputX;   // スティック横軸の入力
	int state;      // 当たり判定の状態
	int flapCount;  // ジャンプ数
	int flightMove; // 空中で羽ばたき中の移動
	int animState;  // アニメーションの状態
	bool turnState; // 左右反転状態
	float speed[2]; // 移動、落下速度

	float leftEndX, rightEndX; // ワープ、当たり判定用のプレイヤー左右端側のX位置

	int frameCounter;

	int img_player[30];


	int MapData[20][10];

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


	// プレイヤーのサイズを取得（大きさ 構造体）
	Size GetSize() {
		return player.size;
	};


	// デバッグ表示
	void Debug() {
		// 画面クリア
		clsDx();

		printfDx("\n\nプレイヤークラス情報\n");

		printfDx("X: %0.0f - Y: %0.0f\n", player.position.x, player.position.y);
		printfDx("State: %d\n", player.state);
		printfDx("animState: %d\n", animState);
		printfDx("flightMove: %d\n", flightMove);
		printfDx("Move Speed: %0.0f - Fall Speed: %0.0f\n", speed[0], speed[1]);
	};

	void SetStageData(int StageData[20][10]) {
		for (int i = 0; i < 20; i++) {
			for (int j = 0; j < 10; j++) {
				this->MapData[i][j] = StageData[i][j];
			};
		};
	};
};
