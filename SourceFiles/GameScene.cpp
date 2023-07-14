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
	blockIndex = 0;

	block[0][0] = 180;
	block[0][1] = 250;
	block[0][2] = 460;
	block[0][3] = 270;

	block[1][0] = 0;
	block[1][1] = 430;
	block[1][2] = 230;
	block[1][3] = 480;
};

Game::~Game() {
	// 終了処理
};

AbstractScene* Game::Update() {

	if (blockIndex > 0) {
		blockIndex = 0;
	}
	else {
		blockIndex++;
	};

	if (player.GetState() == 0) {
		Collide collide;
		collide.ul.x = block[blockIndex][0];
		collide.ul.y = block[blockIndex][1];
		collide.lr.x = block[blockIndex][2];
		collide.lr.y = block[blockIndex][3];
		blockData = collide;
	};
	player.SetCollideData(blockData);
	player.SetState(CheckCollideBox(player.GetPosition().x - player.GetSize().width, player.GetPosition().y - player.GetSize().height, player.GetPosition().x + player.GetSize().width, player.GetPosition().y + player.GetSize().height, blockData.ul.x, blockData.ul.y, blockData.lr.x, blockData.lr.y));



	if (!CheckHitKey(KEY_INPUT_0) && !CheckHitKey(KEY_INPUT_1) && !CheckHitKey(KEY_INPUT_2) && !CheckHitKey(KEY_INPUT_3) && !CheckHitKey(KEY_INPUT_4)) {
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
	};

	player.Update();
	player.Debug();


	return this;
};

void Game::Draw() const {
	SetFontSize(16);

	stage.Draw();

	player.Draw();

	//ui.Draw();

	//DrawFormatString(20, 50, 0xffffff, "ゲームメイン");

	if (state == 0) {
		//DrawFormatString(20, 100, 0xffffff, "ボタンが押されました");
	} else if (state == 1) {
		//DrawFormatString(20,150, 0xffffff, "ボタンが押されました");
	};

	// 仮
	DrawBox(block[0][0], block[0][1], block[0][2], block[0][3], 0xffffff, FALSE); // 真ん中
	DrawBox(block[1][0], block[1][1], block[1][2], block[1][3], 0xffffff, FALSE); // 左下
};

