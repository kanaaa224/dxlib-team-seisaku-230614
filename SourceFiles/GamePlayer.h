/********************************
* ゲームプレイヤー
* 担当：島袋
********************************/
#pragma once
#include "main.h"

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


// プレイヤークラス
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


	// プレイヤーの状態を設定
	void SetState(int State) {
		player.state = State;
	};

	// プレイヤーの状態を取得
	int GetState() {
		return player.state;
	};

	// プレイヤーの位置を取得（float型 座標 構造体）
	Position GetPosition() {
		return player.position;
	};

	// プレイヤーのサイズを取得（大きさ 構造体）
	Size GetSize() {
		return player.size;
	};

	// 当たり判定用の左上・右上の座標を設定
	void SetCollideData(Collide CollideData) {
		collideData.ul.x = CollideData.ul.x;
		collideData.ul.y = CollideData.ul.y;
		collideData.lr.x = CollideData.lr.x;
		collideData.lr.y = CollideData.lr.y;
	};


	// デバッグ表示
	void Debug() const {
		int x = 10;  // x座標の初期値
		int y = 50;  // y座標の初期値

		DrawFormatString(x, y, GetColor(255, 255, 255), "プレイヤークラス データ");
		y += 30;
		DrawFormatString(x, y, GetColor(255, 255, 255), "x: %0.0f y: %0.0f", player.position.x, player.position.y);
		y += 30;
		DrawFormatString(x, y, GetColor(255, 255, 255), "playerState: %d", player.state);
		y += 15;
		DrawFormatString(x, y, GetColor(255, 255, 255), "inputX: %0.1f", inputX);
		y += 15;
		DrawFormatString(x, y, GetColor(255, 255, 255), "state: %d", state);
		y += 15;
		DrawFormatString(x, y, GetColor(255, 255, 255), "flapCount: %d", flapCount);
		y += 15;
		DrawFormatString(x, y, GetColor(255, 255, 255), "flightMove: %d", flightMove);
		y += 15;
		DrawFormatString(x, y, GetColor(255, 255, 255), "animState: %d", animState);
		y += 15;
		DrawFormatString(x, y, GetColor(255, 255, 255), "turnState: %d", turnState);
		y += 15;
		DrawFormatString(x, y, GetColor(255, 255, 255), "moveSpeed: %0.1f fallSpeed: %0.1f", speed[0], speed[1]);
		y += 15;
		DrawFormatString(x, y, GetColor(255, 255, 255), "leftEndX: %0.0f rightEndX: %0.0f", leftEndX, rightEndX);
		y += 15;
		DrawFormatString(x, y, GetColor(255, 255, 255), "frameCounter: %d", frameCounter);
	};


	//// プレイヤー移動
	//bool Control();

	//// 重力を作用させる
	//void Gravity();

	//// プレイヤー画像のアニメーションを行う
	//void Animation();

	//// 跳ね返りさせる
	//void Bounce();
};
