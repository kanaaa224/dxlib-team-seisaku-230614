/********************************
* ゲームプレイヤー
* 担当：島袋
********************************/
#pragma once
#include "main.h"

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

// ブロック 構造体
struct Collide {
	Position ul, lr; // UpperLeft LowerRight
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

	Collide collideData;

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


	void SetCollideData(Collide CollideData) {
		collideData.ul.x = CollideData.ul.x;
		collideData.ul.y = CollideData.ul.y;
		collideData.lr.x = CollideData.lr.x;
		collideData.lr.y = CollideData.lr.y;
	};


	// デバッグ表示
	void Debug() {
		// 画面クリア
		clsDx();

		printfDx("\n\nプレイヤークラス情報\n");

		printfDx("x: %0.0f - y: %0.0f\n", player.position.x, player.position.y);
		printfDx("playerState: %d\n", player.state);

		printfDx("\ninputX: %0.0f\n", inputX);
		printfDx("state: %d\n", state);
		printfDx("flapCount: %d\n", flapCount);
		printfDx("flightMove: %d\n", flightMove);
		printfDx("animState: %d\n", animState);
		printfDx("turnState: %d\n", turnState);
	
		printfDx("\nmoveSpeed: %0.0f - fallSpeed: %0.0f\n", speed[0], speed[1]);

		printfDx("\nleftEndX: %0.0f - rightEndX: %0.0f\n", leftEndX, rightEndX);

		printfDx("\nframeCounter: %d\n", frameCounter);
	};
};
