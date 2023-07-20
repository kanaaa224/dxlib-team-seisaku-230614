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
	// 仮
	float block[FOOTING_MAX][4];
	int GetScore_500;//仮りで画像表示するための変数
public:
	// コンストラクタ
	GameStageGimmick();

	// デストラクタ
	~GameStageGimmick();

	// 更新
	void bubble_Update();

	// 描画
	void bubble_Draw() const;


	// 引数で指定したブロックの左下、右下の座標を返す
	Collide GetBlock(int Index) {
		Collide collide;
		collide.ul.x = block[Index][0];
		collide.ul.y = block[Index][1];
		collide.lr.x = block[Index][2];
		collide.lr.y = block[Index][3];
		return collide;
	};
};