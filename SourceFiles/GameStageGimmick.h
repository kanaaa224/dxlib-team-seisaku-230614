/********************************
* ゲームステージ処理
* 編集者：
********************************/
#pragma once
#include "main.h"

// ステージクラス
class GameStageGimmick {
private:
	//int img_sea;      // 海
	//int img_footing;  // 足場
	//int img_cloud[2]; // 雲

	int img_bubble[3];//シャボン
	int bubble_height;
	int bubble_width;
	int frequency;//シャボン玉のの周波数
	int  bubble_count;
	float amplitude;
	float bubble_x;
	//シャボン玉のアニメーション用
	int frameCounter;
	int bubble_anm;

public:
	// コンストラクタ
	GameStageGimmick(int *bubble_images);

	// デストラクタ
	~GameStageGimmick();

	// 更新
	void bubble_Update();

	// 描画
	void bubble_Draw() const;



};