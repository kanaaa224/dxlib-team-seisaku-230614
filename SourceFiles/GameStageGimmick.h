/********************************
* ゲームステージギミック処理
* 編集者：
********************************/
#pragma once
#include "main.h"


// ステージクラス
class GameStageGimmick {
private:
	int img_bubble[4]; // シャボン

	int bubble_height;
	int bubble_width;
	int frequency; // シャボン玉のの周波数
	int  bubble_count;
	float amplitude;
	float bubble_x;

	// シャボン玉のアニメーション用
	int frameCounter;
	int bubble_anim;

	int bubble_flg;
	int position;
	int position_flg;
	int new_position;

	//int GetScore_500;//仮りで画像表示するための変数

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

	// シャボン玉 更新
	void BubbleUpdate();

	// シャボン玉 描画
	void BubbleDraw() const;

	// プレイヤーの衝突座標を設定
	void SetPlayerCollide(Collide collide) {
		playerCollide = collide;
	};
};
