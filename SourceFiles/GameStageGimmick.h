/********************************
* ゲームステージギミック処理
* 編集者：
********************************/
#pragma once
#include "main.h"

#define BUBBLE_MAX 100

struct Bubble {
	int frameCounter = 0;
	int anim = 0;
	int flg = 0;
	float x = 0.0f;
	float y = 0.0f;
	float drawX = 0.0f;
};

// ギミッククラス
class GameStageGimmick {
private:
	Bubble bubble[BUBBLE_MAX];

	int img_bubble[4];

	// プレイヤーの左上・右上座標
	//Collide playerCollide;

public:
	// コンストラクタ
	GameStageGimmick();

	// デストラクタ
	~GameStageGimmick();

	// 更新
	void Update() {
		UpdateBubble();
	};

	// 描画
	void Draw() const {
		DrawBubble();
	};

	/////////////////////////////////////////////////////////

	// シャボン玉 リセット
	void BubbleReset() {
		for (int i = 0; i < BUBBLE_MAX; i++) {
			bubble[i].flg = 0;
		};
	};

	// シャボン玉 更新
	void UpdateBubble();

	// シャボン玉 描画
	void DrawBubble() const;

	// シャボン玉 出現
	void SpawnBubble(float x) {
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

	Collide GetBubbleCollide(int index) {
		Collide collide;
		int padding = 20;
		collide.ul.x = bubble[index].drawX - 20;
		collide.ul.y = bubble[index].y - 20;
		collide.lr.x = bubble[index].drawX + 20;
		collide.lr.y = bubble[index].y + 20;
		return collide;
	};

	void SetBubbleFlg(int index, int flg) {
		bubble[index].flg = flg;
	};

	int GetBubbleFlg(int index) {
		return bubble[index].flg;
	};



	void UpdateThunder();

	void DrawThunder() const;

	void ChangeAngle(void);//雷

	// 雷
	int Thunder[3];
	int ThunderAnim;
	int ThunderAnimFlg;
	int AnimChangefps;

	//ボールの変数
	int ThunderX = 320;
	int ThunderY = 400;
	int MoveX = 0;
	int MoveY = 0; //雷の移動量
	int Speed = 4; // 雷のスピード
	float ThunderAngle = 0.625f; // 雷の角度

	int thunderx, thundery;
	//雷用の座標を設定
		int SetThunderX(int ThunderX) {
			thunderx = ThunderX;
	};

		int GetThunderX() {
			return thunderx;
		}

		//雷用の座標を設定
		int SetThunderY(int ThunderY) {
			thundery = ThunderY;
		};

		int GetThunderY() {
			return thundery;
		}
};