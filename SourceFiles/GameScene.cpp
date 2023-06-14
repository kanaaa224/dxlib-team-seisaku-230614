/********************************
* ゲームメインシーン
* 編集者：島袋
********************************/
#include "main.h"

Game::Game() {
	// 初期化処理
	state = 0;
};

Game::~Game() {
	// 終了処理
};

AbstractScene* Game::Update() {



	return this;
};

void Game::Draw() const {
	SetFontSize(16);

	DrawFormatString(20, 50, 0xffffff, "ゲームメイン");
};

