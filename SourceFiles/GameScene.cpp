/********************************
* ゲームメインシーン
* 編集者：島袋
********************************/
#include "common.h"

Game::Game() {
	// 初期化処理
	btn_flg = 0;
	state = 0;
};

Game::~Game() {
	// 終了処理
};

AbstractScene* Game::Update() {

	if (!CheckHitKey(KEY_INPUT_SPACE)) {
		btn_flg = 0;
	};
	if (CheckHitKey(KEY_INPUT_SPACE) && btn_flg == 0) {
		
		if (state == 0) {
			state = 1;
		}
		else {
			state = 0;
		};

		btn_flg = 1;
	};

	return this;
};

void Game::Draw() const {
	SetFontSize(16);

	player.Draw();
	stage.Draw();

	DrawFormatString(20, 50, 0xffffff, "ゲームメイン");

	if (state == 0) {
		DrawFormatString(20, 100, 0xffffff, "ボタンが押されました");
	} else if (state == 1) {
		DrawFormatString(20,150, 0xffffff, "ボタンが押されました");
	};
};

