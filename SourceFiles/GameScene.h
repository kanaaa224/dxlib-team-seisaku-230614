/********************************
* ゲームメインシーン
* 編集者：島袋
********************************/
#pragma once
#include "AbstractScene.h"

class Game : public AbstractScene {
private:
	int state;
public:
	// コンストラクタ
	Game();

	// デストラクタ
	~Game();

	// 描画以外の更新を実装
	virtual AbstractScene* Update() override;

	// 描画に関することを実装
	virtual void Draw() const override;
};

// じゃんけんの手
#define ROCK 0     // グー
#define SCISSORS 1 // チョキ
#define PAPER 2    // パー

#define ME 0       // 自分
#define AITE 1     // 相手

class GameMain {
private:
	static int score[];
	static int clearFlg;
public:
	// スコア設定
	static void SetScore(int f, int s) { 
		score[f] = s;
	};

	// スコア取得
	static int GetScore(int f) {
		return score[f];
	};

	// クリアフラグ設定
	static void SetClearFlg(int f) {
		clearFlg = f;
	};

	// クリアフラグ取得
	static int GetClearFlg() {
		return clearFlg;
	};

	// 初期化処理
	static void Init() {
		score[0] = 0;
		score[1] = 1;
		clearFlg = 0;
	};
};