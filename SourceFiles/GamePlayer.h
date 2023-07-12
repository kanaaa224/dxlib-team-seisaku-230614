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
	int flapCount;  // ジャンプ入力数
	int flightMove; // 空中で羽ばたき中の移動受付
	int animState;  // アニメーション状態
	bool turnState; // 左右反転状態
	float speed[2]; // 移動、落下速度

	float leftEndX, rightEndX; // ワープ用のプレイヤー左右端側のX位置

	int frameCounter;

	int img_player[30];


	int MapData[20][10];	//マップデータ

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

	void SetStageData(int StageData[20][10]);

	// デバッグ表示
	void Debug() {
		// 画面クリア
		clsDx();

		printfDx("\n\nプレイヤークラス情報\n");

		printfDx("X: %0.0f - Y: %0.0f\n", player.position.x, player.position.y);
		printfDx("State: %d\n", player.state);
		printfDx("animState: %d\n", animState);
		printfDx("Move Speed: %0.0f - Fall Speed: %0.0f\n", speed[0], speed[1]);
	};
};
