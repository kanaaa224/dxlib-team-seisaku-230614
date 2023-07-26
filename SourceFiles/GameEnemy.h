/********************************
* ゲームエネミー処理
* 編集者：
********************************/
#pragma once
#include "main.h"

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

	int anim;

	int r_enemy[18];
	int g_enemy[18];
	int p_enemy[18];
	int fish[10];

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
};
