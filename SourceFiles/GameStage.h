/********************************
* ゲームステージ処理
* 編集者：
********************************/
#pragma once
#include "main.h"

#define FOOTING_MAX 8 // 一番足場が多いステージの足場の最大数

// ステージ当たり判定データ 構造体
struct CollisionData {
	int footingMax = 0;
	int footingBlock[FOOTING_MAX][4];
};

// ステージクラス
class GameStage{
private:
	int img_sea;        // 海
	int img_footing[8]; // 足場 画像のStage01から始まり08まである　0から始まる
	int img_land[4];    // 海付き地面
	int img_cloud[2];   // 雲
	int img_ect[2];     // 雷

	// 仮 - ステージ当たり判定データ
	CollisionData collisionData[5];

	int nowStage; // 現在のステージ

public:
	// コンストラクタ
	GameStage();

	// デストラクタ
	~GameStage();

	// 更新
	void Update();

	// 描画
	void Draw() const;

	// 海の描画
	void DrawSea() const;

	void HitStage();

	void SetNowStage(int StaageIndex) {
		nowStage = StaageIndex;
	};

	// 引数で指定したブロックの左下、右下の座標を返す
	Collide GetBlock(int StageIndex, int blockIndex) {
		Collide collide;
		collide.ul.x = collisionData[StageIndex].footingBlock[blockIndex][0];
		collide.ul.y = collisionData[StageIndex].footingBlock[blockIndex][1];
		collide.lr.x = collisionData[StageIndex].footingBlock[blockIndex][2];
		collide.lr.y = collisionData[StageIndex].footingBlock[blockIndex][3];
		return collide;
	};

	// 引数で指定したステージの足場の最大数を返す
	int GetFootingMax(int StageIndex) {
		return collisionData[StageIndex].footingMax;
	};

};