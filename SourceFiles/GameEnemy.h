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
	int frameCounter;


	int img[10];

	int flg, anim;
	int x;
	int y;

public:
	EnemyFish() {
		frameCounter = 0;

		flg = 0;
		anim = 0;
		x = 0;
		y = 0;

		LoadDivGraph("Resources/Images/Enemy/Enemy_FishAnimation.png", 10, 5, 2, 64, 64, img);
	};

	~EnemyFish() {
		for (int i = 0; i < 10; i++) {
			DeleteGraph(img[i]);
		}
	};

	void Update() {
		x = 300;
		y = SCREEN_HEIGHT - 50;

		if (flg) {
			if (frameCounter++ % 7 == 0) {
				if (flg == 1) {
					if (anim < 2) {
						anim++;
					}
				}
				else if (flg == 2) {
					if (anim > 0) {
						anim--;
					}
					else flg = 0;
				};
			}
		}
	};

	void Draw() const {
		if(flg) DrawRotaGraph(x, y, 1.0f, 0, img[anim], TRUE);
	};

	void Spawn() {
		if (!flg) flg = 1;
		else if (flg && anim == 2) flg = 2;
	};
};
