/********************************
* ゲームエネミー処理
* 編集者：
********************************/
#pragma once
#include "main.h"


class GameEnemy {
private:
	int frameCounter;
	int currentStateDuration;
	int nextStateChange;
	bool isChasingPlayer;

	Person enemy;
	Position inertia;

	GameStage stage;
	int blockIndex, stageIndex;

	int lagCounter;
	int lagTime;

	int TimeDuration = 60;
	int currenttime = 0;

	struct Vector {
		float x;
		float y;
	};

	enum class EnemyState {
		CHASE,
		CONTINUE_CHASE,
		ESCAPE,
		AVOID
	};

	EnemyState currentState = EnemyState::CHASE;
	int stateTimer;
	int stateDuration;

	float moveSpeedMax = 2.5f;
	//Vector moveSpeed = { 1.0f, 0.5f };
	float moveSpeed;
	float moveSpeedX;
	float moveSpeedY;
	float inertiaCoefficient;

	float XDistance;
	float YDistance;
	

	int anim;

	int enemyimg[3][18];
	int enemypattern;
	

	// プレイヤーの左上・右上座標
	Collide playerCollide;
	Collide collideData;
	Collide blockData;

	
	int enemyMax;

public:
	// コンストラクタ
	GameEnemy();

	// デストラクタ
	~GameEnemy();

	// 初期化
	void Init();

	// 更新
	void Update(int);

	// 描画
	void Draw() const;

	void SetEnemyState(int State) {
		enemy.state = State;
	}

	int GetEnemyState() {
		return enemy.state;
	}
	// 当たり判定用の左上・右上の座標を設定
	void SetCollide(Collide CollideData) {
		collideData.ul.x = CollideData.ul.x;
		collideData.ul.y = CollideData.ul.y;
		collideData.lr.x = CollideData.lr.x;
		collideData.lr.y = CollideData.lr.y;
	};

	// プレイヤー左上・右上の座標の取得
	Collide GetCollide() {
		Collide CollideData;
		CollideData.ul.x = (enemy.position.x - enemy.size.width);
		CollideData.ul.y = (enemy.position.y - enemy.size.height);
		CollideData.lr.x = (enemy.position.x + enemy.size.width);
		CollideData.lr.y = (enemy.position.y + enemy.size.height);
		return CollideData;
	};

	// 風船エリアの左上・右上の座標の取得
	Collide GetWeakCollide() {
		Collide CollideData;
		CollideData.ul.x = (enemy.position.x - enemy.size.width);
		CollideData.ul.y = (enemy.position.y - enemy.size.height);
		CollideData.lr.x = (enemy.position.x + enemy.size.width);
		CollideData.lr.y = (enemy.position.y - enemy.size.height) + 20;
		return CollideData;
	};

	// プレイヤーの衝突座標を設定
	void SetPlayerCollide(Collide collide) {
		playerCollide = collide;
	};
	void ChacePlayer();
	void RunAwayfromPlayer();
	void AvoidPlayer();

	// 引数で指定したブロックの左下、右下の座標を返す
	//Collide GetBlock(int StageIndex, int blockIndex) {
	//	Collide collide;
	//	collide.ul.x = collisionData[StageIndex].footingBlock[blockIndex][0];
	//	collide.ul.y = collisionData[StageIndex].footingBlock[blockIndex][1];
	//	collide.lr.x = collisionData[StageIndex].footingBlock[blockIndex][2];
	//	collide.lr.y = collisionData[StageIndex].footingBlock[blockIndex][3];
	//	return collide;
	//};

	// 引数で指定したステージの足場の最大数を返す
	int GetEnemyMax() {
		return enemyMax;
	};

	// 当たり判定 - 島袋
	static int CheckCollide(Collide collideA, Collide collideB) {
		if (collideA.lr.x <= collideB.ul.x || collideA.ul.x >= collideB.lr.x || collideA.lr.y <= collideB.ul.y || collideA.ul.y >= collideB.lr.y) return 0;
		if (fabsf(collideA.lr.y - collideB.ul.y) < 15) return 1;
		else if (fabsf(collideA.ul.y - collideB.lr.y) < 15) return 2;
		else if (fabsf(collideA.lr.x - collideB.ul.x) < 15) return 3;
		else if (fabsf(collideA.ul.x - collideB.lr.x) < 15) return 4;
		else return 0;
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
		if(flg) DrawRotaGraph(x, y, 1.0f, 0, img[anim], TRUE, FALSE);
	};

	void Spawn() {
		if (!flg) flg = 1;
		else if (flg && anim == 2) flg = 2;
	};
};
