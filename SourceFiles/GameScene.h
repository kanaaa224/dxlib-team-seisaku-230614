/********************************
* ゲームメインシーン
* 担当：島袋、
********************************/
#pragma once
#include "AbstractScene.h"
#include "main.h"

class Game : public AbstractScene {
private:
	int state;
	int btn_flg;

	GamePlayer player;
	GameStage stage;
	GameUI ui;

	// 仮
	Collide blockData;
	int blockIndex, stageIndex;
	bool debug;

public:
	// コンストラクタ
	Game();

	// デストラクタ
	~Game();

	// 描画以外の更新を実装
	virtual AbstractScene* Update() override;

	// 描画に関することを実装
	virtual void Draw() const override;


	// 当たり判定 - 島袋
	static int CheckCollideBox(float s1X1, float s1Y1, float s1X2, float s1Y2, float s2X1, float s2Y1, float s2X2, float s2Y2) {
		if (s1X2 <= s2X1 || s1X1 >= s2X2 || s1Y2 <= s2Y1 || s1Y1 >= s2Y2) return 0;
		if (fabsf(s1Y2 - s2Y1) < 10) return 1;
		else if (fabsf(s1Y1 - s2Y2) < 10) return 2;
		else if (fabsf(s1X2 - s2X1) < 10) return 3;
		else if (fabsf(s1X1 - s2X2) < 10) return 4;
		else return 0;
	};
};
