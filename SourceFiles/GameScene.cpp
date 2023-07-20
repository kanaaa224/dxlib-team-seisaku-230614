/********************************
* ゲームメインシーン
* 担当：島袋、
********************************/
#include "main.h"

Game::Game() {
	state = 0;

	if ((snd_start = LoadSoundMem("Resources/Sounds/SE_Start.wav")) == -1) throw;
	if (CheckSoundMem(snd_start) == 0) PlaySoundMem(snd_start, DX_PLAYTYPE_BACK, TRUE);

	if ((snd_gameOver = LoadSoundMem("Resources/Sounds/SE_GameOver.wav")) == -1) throw;

	// 仮
	ctrlFlg = false;
	ui.SetScore(12345);
	ui.SetHighScore(67890);
	ui.SetState(1);
	stock = 2;
	blockIndex = 0;
	stageIndex = 0;
	debug = false;
};

Game::~Game() {
	DeleteSoundMem(snd_start);
	DeleteSoundMem(snd_gameOver);
};

AbstractScene* Game::Update() {

	// 仮 - ステージ上のブロックとプレイヤーの当たり判定
	if (player.GetState() == 0) {
		blockData = stage.GetBlock(blockIndex);
		if (blockIndex >= (7 - 1)) blockIndex = 0;
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

	// 仮 - 海に落ちた時の残機処理
	if (SCREEN_HEIGHT + 100 < (player.GetPosition().y - player.GetSize().height)) {
		if (stock == 0) {
			state = 1;
			ui.SetState(-1);
			PlaySoundMem(snd_gameOver, DX_PLAYTYPE_BACK, TRUE);
			stock = -1;
		}
		else if (stock > 0) {
			stock--;
			player.Restart();
		};
	};

	// 仮 - Pキーでポーズ
	if (!CheckHitKey(KEY_INPUT_P) && !CheckHitKey(KEY_INPUT_O) && !CheckHitKey(KEY_INPUT_1)) ctrlFlg = true;
	if (CheckHitKey(KEY_INPUT_P) && ctrlFlg) {
		if (state == 1) state = 0;
		else state = 1;
		ctrlFlg = false;
	}
	// 仮 - OキーでUIテスト
	else if (CheckHitKey(KEY_INPUT_O) && ctrlFlg) {
		if (stageIndex >= 5) stageIndex = -1;
		else stageIndex++;
		ui.SetState(stageIndex);
		//ui.SetStock(stageIndex + 1);
		ctrlFlg = false;
	}
	// 仮 - 1キーでデバッグモード
	else if (CheckHitKey(KEY_INPUT_1) && ctrlFlg) {
		if (debug) debug = false;
		else debug = true;
		ctrlFlg = false;
	};

	// 仮 - Rキーでリセット
	if (CheckHitKey(KEY_INPUT_R)) return new Game();

	// 仮 - ESCキーでタイトル
	if (PadInput::OnPress(XINPUT_BUTTON_BACK) || CheckHitKey(KEY_INPUT_ESCAPE)) return new Title();

	stage.Update();
	ui.SetStock(stock);
	ui.Update();

	return this;
};

void Game::Draw() const {

	stage.Draw();
	player.Draw();
	ui.Draw();

	if (debug) player.Debug();
};

