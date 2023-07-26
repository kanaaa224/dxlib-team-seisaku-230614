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

	if ((LoadDivGraph("Resources/Images/Stage/Stage_ThunderEffectAnimation.png",3, 3, 1, 32, 32, Thunder)) == -1) throw;

	// 仮
	ctrlFlg = false;
	blockIndex = 0;
	ThunderAnim = 0;
	ThunderAnimFlg = 0;
	AnimChangefps = 3;
	stageIndex = GameMain::GetNowStageIndex();
	debug = false;
	gameover = false;
	ui.SetScore(12345);
	ui.SetHighScore(67890);
	ui.SetState(stageIndex + 1);
	player.SetStock(2);

	// 仮 - ダメージブロック
	damageBlock[0] = 150;
	damageBlock[1] = 100;
	damageBlock[2] = damageBlock[0] + 20;
	damageBlock[3] = damageBlock[1] + 20;
	damageBlock[4] = 250;
	damageBlock[5] = 100;
	damageBlock[6] = damageBlock[4] + 20;
	damageBlock[7] = damageBlock[5] + 20;
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
	player.SetCollide(blockData);
	player.SetState(
		CheckCollideBox(
			player.GetPosition().x - player.GetSize().width, player.GetPosition().y - player.GetSize().height, 
			player.GetPosition().x + player.GetSize().width, player.GetPosition().y + player.GetSize().height,
			blockData.ul.x, blockData.ul.y, blockData.lr.x, blockData.lr.y
		)
	);

	// 仮 - 海に落ちた時の残機処理
	if (SCREEN_HEIGHT + 50 < (player.GetPosition().y - player.GetSize().height)) {
		player.Miss(MISS_FALLSEA);
	};

	// 仮 - ダメージブロックとの判定、ダメージ処理
	Collide balloonCollide = player.GetWeakCollide();
	if ((CheckCollideBox(balloonCollide.ul.x, balloonCollide.ul.y, balloonCollide.lr.x, balloonCollide.lr.y, damageBlock[0], damageBlock[1], damageBlock[2], damageBlock[3]) == 0) && (CheckCollideBox(balloonCollide.ul.x, balloonCollide.ul.y, balloonCollide.lr.x, balloonCollide.lr.y, damageBlock[4], damageBlock[5], damageBlock[6], damageBlock[7]) == 0)) damageFlg = true;
	if (CheckCollideBox(balloonCollide.ul.x, balloonCollide.ul.y, balloonCollide.lr.x, balloonCollide.lr.y, damageBlock[0], damageBlock[1], damageBlock[2], damageBlock[3]) >= 1 && damageFlg) {
		player.Damage();
		damageFlg = false;
	}
	else if (CheckCollideBox(balloonCollide.ul.x, balloonCollide.ul.y, balloonCollide.lr.x, balloonCollide.lr.y, damageBlock[4], damageBlock[5], damageBlock[6], damageBlock[7]) >= 1 && damageFlg) {
		player.Miss(MISS_LIGHTNING);
		damageFlg = false;
	};

	// 仮 - 水しぶき
	if (SCREEN_HEIGHT + 10 < (player.GetPosition().y - player.GetSize().height)) effect.Splash((player.GetPosition().x - player.GetSize().width), (SCREEN_HEIGHT - 50));
	ThunderAnim++;
	if (ThunderAnim > 0 && ThunderAnim <= AnimChangefps)
	{
		ThunderAnimFlg = 0;
	}
	else if (ThunderAnim > AnimChangefps && ThunderAnim <= AnimChangefps * 2)
	{
		ThunderAnimFlg = 1;
	}
	else if (ThunderAnim > AnimChangefps * 2 && ThunderAnim <= AnimChangefps * 3)
	{
		ThunderAnimFlg = 2;
	}
	else if (ThunderAnim > AnimChangefps * 3) {
		ThunderAnim = 0;
	}

	// 仮 - Pキーでポーズ
	if (!CheckHitKey(KEY_INPUT_P) && !CheckHitKey(KEY_INPUT_O) && !CheckHitKey(KEY_INPUT_1)) ctrlFlg = true;
	if (CheckHitKey(KEY_INPUT_P) && ctrlFlg) {
		if (state == 1) state = 0;
		else state = 1;
		ctrlFlg = false;
	}
	// 仮 - 1キーでデバッグモード
	else if (CheckHitKey(KEY_INPUT_1) && ctrlFlg) {
		if (debug) debug = false;
		else debug = true;
		ctrlFlg = false;
	}
	// 仮 - Oキーでステージ遷移
	else if ((CheckHitKey(KEY_INPUT_O) && ctrlFlg) || PadInput::OnPress(XINPUT_BUTTON_START)) {
		int si = GameMain::GetNowStageIndex();
		if (si < 4) GameMain::SetStageIndex(GameMain::GetNowStageIndex() + 1);
		else GameMain::SetStageIndex(0);
		return new Game();
	};

	// 仮 - Rキーでリセット
	if (CheckHitKey(KEY_INPUT_R)) return new Game();

	// 仮 - ESCキーでタイトル
	if (CheckHitKey(KEY_INPUT_ESCAPE) || PadInput::OnPress(XINPUT_BUTTON_BACK)) return new Title();

	stage.SetNowStage(stageIndex);
	stage.Update();
	gimmick.Update();
	gimmick.SetPlayerCollide(player.GetCollide());

	if (state != 1) player.Update();
	if ((player.GetStock() == -1) && !gameover) {
		state = 1;
		PlaySoundMem(snd_gameOver, DX_PLAYTYPE_BACK, TRUE);
		gameover = true;
	};
	effect.Update();
	ui.SetStock(player.GetStock());
	ui.Update();

	enemy.Update();
	
	return this;
};

void Game::Draw() const {

	stage.Draw();
	gimmick.Draw();

	player.Draw();
	effect.Draw();
	ui.Draw();

	enemy.Draw();

	if (debug) player.Debug();
	//if (gameover) DrawFormatString(10, 50, 0xffffff, "Rキーでリセット（メモリ占有に注意）");
	//if (gameover) DrawFormatString(10, 65, 0xffffff, "Pキーでそのまま続行");

	DrawBox(damageBlock[0], damageBlock[1], damageBlock[2], damageBlock[3], 0xff0000, FALSE);
	DrawBox(damageBlock[4], damageBlock[5], damageBlock[6], damageBlock[7], 0xffff00, FALSE);

	DrawExtendGraph(damageBlock[4], damageBlock[5], damageBlock[6], damageBlock[7], Thunder[ThunderAnimFlg], TRUE);
};

int GameMain::stageIndex = 0;