/********************************
* ゲームステージ
* 編集者：
********************************/
#pragma once
#include "main.h"
#include "AbstractScene.h"

// プレイヤークラス
class GameStage {
private:
	int img_bg;
	int img_bg1;
	int cloudimg[2];//雲の画像用
	int StageFlg;
	int mx0, mx1, my0, my1, sx0, sx1, sy0, sy1;
	int StageX, StageY;
	int playerX,playerY;
	float PlayerAngle;

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
};
