/********************************
* ゲームUI処理
* 担当：島袋
********************************/
#include "main.h"

GameUI::GameUI() {
	state = 0;
	frameCounter = 0;

	stock = 0;
	score = 0;
	highScore = 0;

	if ((img_playerScore = LoadGraph("Resources/Images/UI/UI_Score.png")) == -1) throw;
	if ((img_highScore = LoadGraph("Resources/Images/UI/UI_HiScore.png")) == -1) throw;
	if ((img_stock = LoadGraph("Resources/Images/UI/UI_Stock.png")) == -1)       throw;
	if ((img_gameOver = LoadGraph("Resources/Images/UI/UI_GameOver.png")) == -1) throw;
	if ((img_phase = LoadGraph("Resources/Images/UI/UI_Phase.png")) == -1)       throw;
	if (LoadDivGraph("Resources/Images/UI/UI_NumAnimation.png", 10, 10, 1, 32, 32, img_number) == -1) throw;
};

GameUI::~GameUI() {
	DeleteGraph(img_playerScore);
	DeleteGraph(img_highScore);
	DeleteGraph(img_stock);
	DeleteGraph(img_gameOver);
	DeleteGraph(img_phase);
	for (int i = 0; i < 10; i++) {
		DeleteGraph(img_number[i]);
	};
};

void GameUI::Update() {
	if (state >= 1) {
		frameCounter++;
		if (frameCounter % 20 == 0) {
			if (state >= 10) state -= 10;
			else state += 10;
		};
		if (frameCounter % (60 * 5) == 0) {
			frameCounter = 0;
			state = 0;
		};
	};
};

void GameUI::Draw() const {
	// スコア（6桁）
	DrawGraph(40, 15, img_playerScore, TRUE);
	for (int i = 0; i < 6; i++) {
		int digit = (score / static_cast<int>(pow(10, i))) % 10;
		DrawRotaGraph(170 - (20 * i), 23, 1.0f, 0, img_number[digit], TRUE);
	};

	// ハイスコア（6桁）
	DrawGraph(225, 15, img_highScore, TRUE);
	for (int i = 0; i < 6; i++) {
		int digit = (highScore / static_cast<int>(pow(10, i))) % 10;
		DrawRotaGraph(375 - (20 * i), 23, 1.0f, 0, img_number[digit], TRUE);
	};

	// 残機
	if (stock == 2) {
		DrawGraph(125, 35, img_stock, TRUE);
		DrawGraph(145, 35, img_stock, TRUE);
	}
	else if (stock == 1) {
		DrawGraph(145, 35, img_stock, TRUE);
	};

	// PHASE
	if (state >= 1 && state < 10) {
		DrawGraph(240, 40, img_phase, TRUE);
		DrawRotaGraph(370, 47, 1.0f, 0, img_number[state], TRUE);
	};

	// ゲームオーバー
	if (stock == -1) DrawGraph(220, 220, img_gameOver, TRUE);
};