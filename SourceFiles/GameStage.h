/********************************
* ゲームステージ処理
* 編集者：
********************************/
#pragma once
#include "main.h"

#define FOOTING_MAX 3 // 足場の最大数（ステージごとで変わるので後で変数にするといいかも）

// ステージクラス
class GameStage{
private:
	int img_sea;      // 海
	int img_footing[8];  // 足場 画像のStage01から始まり08まである　0から始まる
	int img_Stage[2];
	int img_cloud[2]; // 雲
	int img_ect[2]; //雷

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
	GameStage();

	// デストラクタ
	~GameStage();

	// 更新
	void Update();

	// 描画
	void Draw() const;

	void HitStage();

	// 引数で指定したブロックの左下、右下の座標を返す
	Collide GetBlock(int Index) {
		Collide collide;
		collide.ul.x = block[Index][0];
		collide.ul.y = block[Index][1];
		collide.lr.x = block[Index][2];
		collide.lr.y = block[Index][3];
		return collide;
	};
	static int Stage;
};