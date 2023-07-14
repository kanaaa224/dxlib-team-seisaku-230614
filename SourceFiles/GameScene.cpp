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
	ui.SetState(1);
	blockIndex = 0;
	stageIndex = 0;
	debug = false;
};

Game::~Game() {
	// 終了処理
};

AbstractScene* Game::Update() {

	// 仮 - ステージ上のブロックとプレイヤーの当たり判定
	if (player.GetState() == 0) {
		blockData = stage.GetBlock(blockIndex);
		if (blockIndex >= (FOOTING_MAX - 1)) blockIndex = 0;
		else blockIndex++;
	};
	player.SetCollideData(blockData);
	player.SetState(
		CheckCollideBox(
			player.GetPosition().x - player.GetSize().width, player.GetPosition().y - player.GetSize().height, 
			player.GetPosition().x + player.GetSize().width, player.GetPosition().y + player.GetSize().height,
			blockData.ul.x, blockData.ul.y, blockData.lr.x, blockData.lr.y
		)
	);
	if (state != 1) player.Update();

	// 仮 - Pキーでポーズ
	if (!CheckHitKey(KEY_INPUT_P) && !CheckHitKey(KEY_INPUT_O) && !CheckHitKey(KEY_INPUT_1)) btn_flg = 0;
	if (CheckHitKey(KEY_INPUT_P) && btn_flg == 0) {
		if (state == 1) state = 0;
		else state = 1;
		btn_flg = 1;
	}
	// 仮 - OキーでUIテスト
	else if (CheckHitKey(KEY_INPUT_O) && btn_flg == 0) {
		if (stageIndex >= 5) stageIndex = -1;
		else stageIndex++;
		ui.SetState(stageIndex);
		ui.SetStock(stageIndex + 1);
		btn_flg = 1;
	}
	// 仮 - 1キーでデバッグモード
	else if (CheckHitKey(KEY_INPUT_1) && btn_flg == 0) {
		if (debug) debug = false;
		else debug = true;
		btn_flg = 1;
	};

	// 仮 - Rキーでリセット
	if (CheckHitKey(KEY_INPUT_R)) return new Game();

	stage.Update();
	ui.Update();

	return this;
};

void Game::Draw() const {

	stage.Draw();
	player.Draw();
	ui.Draw();

	if (debug) player.Debug();
};

