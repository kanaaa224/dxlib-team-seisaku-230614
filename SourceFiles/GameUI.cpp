/********************************
* ゲームUI処理
* 担当：島袋
********************************/
#include "main.h"

GameUI::GameUI() {
	// 画像読み込み
	img_playerScore = LoadGraph("Resources/Images/UI/UI_Score.png");
	img_highScore = LoadGraph("Resources/Images/UI/UI_HiScore.png");
	img_stock = LoadGraph("Resources/Images/UI/UI_Stock.png");
	img_gameOver = LoadGraph("Resources/Images/UI/UI_GameOver.png");
	img_phase = LoadGraph("Resources/Images/UI/UI_Phase.png");
	LoadDivGraph("Resources/Images/UI/UI_NumAnimation.png", 10, 10, 1, 32, 32, img_number);
};

GameUI::~GameUI() {
	DeleteGraph(img_playerScore);
	DeleteGraph(img_highScore);
	DeleteGraph(img_stock);
	DeleteGraph(img_gameOver);
	DeleteGraph(img_phase);
	//DeleteGraph(img_number);
};

void GameUI::Update() {
	
};

void GameUI::Draw() const {
	// スコア（6桁）
	DrawGraph(40, 15, img_playerScore, TRUE);
	for (int i = 0; i < 6; i++) {
		int digit = (score / static_cast<int>(pow(10, i))) % 10;
		DrawRotaGraph(170 - (20 * i), 23, 1.0, 0.0, img_number[digit], TRUE);
	};

	// ハイスコア
	DrawGraph(240, 15, img_highScore, TRUE);
	for (int i = 0; i < 6; i++) {
		int digit = (highScore / static_cast<int>(pow(10, i))) % 10;
		DrawRotaGraph(390 - (20 * i), 23, 1.0, 0.0, img_number[digit], TRUE);
	};

	// 残機
	if (stock == 2) {
		DrawGraph(125, 35, img_stock, TRUE);
		DrawGraph(145, 35, img_stock, TRUE);
	}
	else if (stock == 1) {
		DrawGraph(145, 35, img_stock, true);
	};

	// PHASE
	if (state == 1) {
		DrawGraph(260, 30, img_phase, TRUE);
	}

	// ゲームオーバー
	if (state == 9) {
		//DrawString(280, 230, "GameOver", 0xffffff);
		DrawGraph(220, 220, img_gameOver, TRUE);
	};
};
