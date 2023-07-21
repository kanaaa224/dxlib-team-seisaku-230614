/********************************
* ゲームステージ処理
* 編集者：
********************************/
#pragma once
#include "main.h"

#define COLLIDE 0
#define TURN    1
#define ANIM    2
#define BLINK 3
#define MOVE 0
#define FALL 1

#define MISS_FALLSEA -1
#define MISS_BALLOONZERO -1
#define MISS_LIGHTNING -3

#define FIRST_POSITION_X 50
#define FIRST_POSITION_Y 405

// float型 2次元座標 構造体
/*struct Position {
	float x = 0.0f;
	float y = 0.0f;
};

// 大きさ 構造体
struct Size {
	float width = 0.0f;
	float height = 0.0f;
};

// ブロック 構造体
struct Collide {
	Position ul, lr; // UpperLeft LowerRight
};*/

// 敵 構造体
struct Enemy {
	Position position;
	Size size;
	int state = 0;
	int hp = 0;
};
class GameEnemy {
private:
	int frameCounter;

	Enemy enemy;

	int flapCount;  // ジャンプ数
	int flightMove; // 空中で羽ばたき中の移動
	int state[4];   // 当たり判定の状態、左右反転状態、アニメーションのフレームカウンター、最初の点滅フラグ
	float speed[1];

	float leftEndX, rightEndX; // ワープ、当たり判定用のプレイヤー左右端側のX位置

	int r_enemy[17];
	int g_enemy[18];
	int p_enemy[18];
	int fish[10];

	Collide collideData;

public:
	// コンストラクタ
	GameEnemy();

	// デストラクタ
	~GameEnemy();

	// 初期化
	void Init();

	// 更新
	void Update();

	// 描画
	void Draw() const;

	void SetEnemyState(int State) {
		enemy.state = State;
	}

	int GetEnemyState() {
		return enemy.state;
	}

	// 当たり判定用の左上・右上の座標を設定
	void SetCollideData(Collide CollideData) {
		collideData.ul.x = CollideData.ul.x;
		collideData.ul.y = CollideData.ul.y;
		collideData.lr.x = CollideData.lr.x;
		collideData.lr.y = CollideData.lr.y;
	};
};
