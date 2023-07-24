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
	hp = 2;
	blockIndex = 0;
	stageIndex = 0;
	debug = false;

	// 仮 - ダメージブロック
	damageBlock[0] = 150;
	damageBlock[1] = 100;
	damageBlock[2] = damageBlock[0] + 20;
	damageBlock[3] = damageBlock[1] + 20;
	damageFlg = false;
};

Game::~Game() {
	DeleteSoundMem(snd_start);
	DeleteSoundMem(snd_gameOver);
};

AbstractScene* Game::Update() {

	// 仮 - ステージ上のブロックとプレイヤーの当たり判定
	if (player.GetState() == 0) {
		blockData = stage.GetBlock(stageIndex, blockIndex);
		if (blockIndex >= (stage.GetFootingMax(stageIndex) - 1)) blockIndex = 0;
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
	if (SCREEN_HEIGHT + 50 < (player.GetPosition().y - player.GetSize().height)) {
		if (stock == 0) {
			state = 1;
			ui.SetState(-1);
			PlaySoundMem(snd_gameOver, DX_PLAYTYPE_BACK, TRUE);
			stock = -1;
		}
		else if (stock > 0) {
			stock--;
			player.Miss(2);
		};
	};

	// 仮 - ダメージブロックとの判定、ダメージ処理
	Collide balloonCollide = player.GetCollideData();
	if (CheckCollideBox(balloonCollide.ul.x, balloonCollide.ul.y, balloonCollide.lr.x, balloonCollide.lr.y, damageBlock[0], damageBlock[1], damageBlock[2], damageBlock[3]) == 0) damageFlg = true;
	if (CheckCollideBox(balloonCollide.ul.x, balloonCollide.ul.y, balloonCollide.lr.x, balloonCollide.lr.y, damageBlock[0], damageBlock[1], damageBlock[2], damageBlock[3]) >= 1 && damageFlg) {
		//if (stock == 0) {
		//	if (player.GetHP() == -10) {
		//		state = 1;
		//		ui.SetState(-1);
		//		PlaySoundMem(snd_gameOver, DX_PLAYTYPE_BACK, TRUE);
		//		stock = -1;
		//	};
		//}
		//else if (stock > 0) {
		//	stock--;
		//};
		player.Damage();
		//if (hp == 1) {
		//	if (player.GetHP() == -10) {
		//		state = 1;
		//		ui.SetState(-1);
		//		PlaySoundMem(snd_gameOver, DX_PLAYTYPE_BACK, TRUE);
		//		stock = -1;
		//	};
		//}
		//else if (hp > 1) {
		//	hp--;
		//	player.Miss(2);
		//};
		damageFlg = false;
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

	stage.SetNowStage(stageIndex);
	stage.Update();
	gimmick.Update();

	ui.SetStock(stock);
	ui.Update();
	
	return this;
};

void Game::Draw() const {

	stage.Draw();
	gimmick.Draw();

	player.Draw();
	ui.Draw();

	if (debug) player.Debug();

	DrawBox(damageBlock[0], damageBlock[1], damageBlock[2], damageBlock[3], 0xffffff, FALSE);
};

