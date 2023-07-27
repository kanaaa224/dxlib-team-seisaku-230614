/********************************
* ゲームエネミー処理
* 編集者：
********************************/
#pragma once
#include "main.h"


class GameEnemy {
private:
	int frameCounter;

	Person enemy;
	

	int anim;

	int r_enemy[18];
	int g_enemy[18];
	int p_enemy[18];
	

	// プレイヤーの左上・右上座標
	Collide playerCollide;

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
	// プレイヤーの衝突座標を設定
	void SetPlayerCollide(Collide collide) {
		playerCollide = collide;
	};
};
class EnemyFish {
private:
	int fish[10];
	int Flg;
	int x;
	int y;
	int anim;
	int frameCounter;

public:

	EnemyFish() {
		Flg = 0;
		anim = 0;
		LoadDivGraph("Resources/Images/Enemy/Enemy_FishAnimation.png", 10, 5, 2, 64, 64, fish);
	};
	~EnemyFish() {
		for (int i = 0; i < 10; i++) {
			DeleteGraph(fish[i]);
		}
	};

	void Update() {
		x = 300;
		y = SCREEN_HEIGHT - 50;
		if (Flg) {
			if (frameCounter % 5 == 0) {
				if (anim < 3) {
					anim++;
				}
			}
		}
	};

	void Draw() const {
		DrawRotaGraph(x, y, 1.0f, 0, fish[anim], TRUE);
	};
	void Spawn() {
		Flg = 1;

	}
};
