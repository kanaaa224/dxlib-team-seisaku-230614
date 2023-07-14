/********************************
* ゲームメインシーン
* 担当：島袋、
********************************/
#include "main.h"

Game::Game() {
	// 初期化処理
	btn_flg = 0;
	state = 0;

	// 仮
	ui.SetScore(12345);
	ui.SetHighScore(67890);
	ui.SetStock(2);
	blockIndex = 0;
};

Game::~Game() {
	// 終了処理
};

AbstractScene* Game::Update() {

	// 仮 - ステージ上のブロックとプレイヤーの当たり判定
	if (player.GetState() == 0) {
		blockData = stage.GetBlock(blockIndex);
		if (blockIndex >= (BLOCK_MAX - 1)) blockIndex = 0;
		else blockIndex++;
	};
	player.SetCollideData(blockData);
	player.SetState(CheckCollideBox(player.GetPosition().x - player.GetSize().width, player.GetPosition().y - player.GetSize().height, player.GetPosition().x + player.GetSize().width, player.GetPosition().y + player.GetSize().height, blockData.ul.x, blockData.ul.y, blockData.lr.x, blockData.lr.y));
	if (state != 1) player.Update();
	//player.Debug();

	// 仮 - Pキーでポーズ
	if (!CheckHitKey(KEY_INPUT_P)) btn_flg = 0;
	if (CheckHitKey(KEY_INPUT_P) && btn_flg == 0) {
		if (state == 1) {
			state = 0;
		}
		else {
			state = 1;
		};
		btn_flg = 1;
	};

	/*if (!CheckHitKey(KEY_INPUT_0) && !CheckHitKey(KEY_INPUT_1) && !CheckHitKey(KEY_INPUT_2) && !CheckHitKey(KEY_INPUT_3) && !CheckHitKey(KEY_INPUT_4)) {
		btn_flg = 0;
	};
	if (CheckHitKey(KEY_INPUT_0) && btn_flg == 0) {

		state = 0;
		player.SetState(0);

		btn_flg = 1;
	}
	else if (CheckHitKey(KEY_INPUT_1) && btn_flg == 0) {
		
		state = 1;
		player.SetState(1);

		btn_flg = 1;
	}
	else if (CheckHitKey(KEY_INPUT_2) && btn_flg == 0) {

		state = 2;
		player.SetState(2);

		btn_flg = 1;
	}
	else if (CheckHitKey(KEY_INPUT_3) && btn_flg == 0) {

		state = 3;
		player.SetState(3);

		btn_flg = 1;
	}
	else if (CheckHitKey(KEY_INPUT_4) && btn_flg == 0) {

		state = 4;
		player.SetState(4);

		btn_flg = 1;
	};*/

	stage.Update();
	ui.Update();

	return this;
};

void Game::Draw() const {

	stage.Draw();
	player.Draw();
	ui.Draw();

	//SetFontSize(16);
	//DrawFormatString(20, 50, 0xffffff, "ゲームメイン");
	//if (state == 0) {
	//	DrawFormatString(20, 100, 0xffffff, "ボタンが押されました");
	//} else if (state == 1) {
	//	DrawFormatString(20,150, 0xffffff, "ボタンが押されました");
	//};
};

