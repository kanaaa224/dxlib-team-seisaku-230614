/********************************
* ゲームメインシーン
* 編集：島袋
********************************/
#pragma once
#include "AbstractScene.h"
#include "main.h"

class Game : public AbstractScene {
private:
	int btn_flg;
	int state;

	GamePlayer player;
	GameStage stage;

	// 仮
	int block[4];
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
	static bool CheckCollideSquares(int s1X1, int s1Y1, int s1X2, int s1Y2, int s2X1, int s2Y1, int s2X2, int s2Y2) {
		// s1がs2の左側にある場合
		if (s1X2 < s2X1) {
			return false;
		};
		// s1がs2の右側にある場合
		if (s1X1 > s2X2) {
			return false;
		};
		// s1がs2の上側にある場合
		if (s1Y2 < s2Y1) {
			return false;
		};
		// s1がs2の下側にある場合
		if (s1Y1 > s2Y2) {
			return false;
		};
		// 上記の条件に当てはまらない場合、二つの四角形は重なっている
		return true;
	};
};
