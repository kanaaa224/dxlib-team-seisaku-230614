/********************************
* ゲームメインシーン
* 編集者：島袋
********************************/
#include "main.h"

Game::Game() {
	// 初期化処理
	btn_flg = 0;
	state = 0;

	// 仮
	block[0] = 0;
	block[1] = 428;
	block[2] = 160;
	block[3] = SCREEN_HEIGHT;
};

Game::~Game() {
	// 終了処理
};

AbstractScene* Game::Update() {

	player.Update();

	if (!CheckCollideSquares(player.GetPosition().x, player.GetPosition().y, player.GetPosition().x + player.GetSize().width, player.GetPosition().y + player.GetSize().height, block[0], block[1], block[0] + block[2], block[1] + block[3])) {
		player.Gravity();
		player.SetState(2);
	}
	else {
		player.SetState(0);
	};



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

	//stage.Draw();

	player.Draw();

	//ui.Draw();

	//DrawFormatString(20, 50, 0xffffff, "ゲームメイン");

	if (state == 0) {
		//DrawFormatString(20, 100, 0xffffff, "ボタンが押されました");
	} else if (state == 1) {
		//DrawFormatString(20,150, 0xffffff, "ボタンが押されました");
	};

	// 仮
	DrawBox(block[0], block[1], block[2], block[3], 0xffffff, FALSE);
};

