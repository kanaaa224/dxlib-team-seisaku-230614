/********************************
* ゲームステージギミック処理
* 編集者：
********************************/
#pragma once
#include "main.h"

#define BUBBLE_MAX 100

struct Bubble {
	int frameCounter = 0;;
	int anim = 0;
	int flg = 0;
	float x = 0.0f;
	float y = 0.0f;
	float drawX = 0.0f;
};

// ステージクラス
class GameStageGimmick {
private:
	Bubble bubble[BUBBLE_MAX];

	int img_bubble[4];

	// プレイヤーの左上・右上座標
	Collide playerCollide;
	
public:
	// コンストラクタ
	GameStageGimmick();

	// デストラクタ
	~GameStageGimmick();

	// 更新
	void Update() {
		BubbleUpdate();
	};

	// 描画
	void Draw() const {
		BubbleDraw();
	};

	/////////////////////////////////////////////////////////

	// シャボン玉リセット
	void BubbleReset() {
		for (int i = 0; i < BUBBLE_MAX; i++) {
			bubble[i].flg = 0;
		};
	};

	// シャボン玉 更新
	void BubbleUpdate();

	// シャボン玉 描画
	void BubbleDraw() const;

	// シャボン玉を出現させる
	void BubbleSpawn(float x) {
		for (int i = 0; i < BUBBLE_MAX; i++) {
			if (!bubble[i].flg) {
				bubble[i].flg = GetRand(1) + 1;
				bubble[i].frameCounter = 0;
				bubble[i].anim = 0;
				bubble[i].x = x;
				bubble[i].y = SCREEN_HEIGHT + 70;
				bubble[i].drawX = x;
				i = BUBBLE_MAX;
			};
		};
	};

	// プレイヤーの衝突座標を設定
	void SetPlayerCollide(Collide collide) {
		playerCollide = collide;
	};
};
