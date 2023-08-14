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

	if ((snd_bubble = LoadSoundMem("Resources/Sounds/SE_Bubble.wav")) == -1) throw;

	if ((LoadDivGraph("Resources/Images/Stage/Stage_ThunderEffectAnimation.png",3, 3, 1, 32, 32, Thunder)) == -1) throw;
	ThunderAnim = 0;
	ThunderAnimFlg = 0;
	AnimChangefps = 3;

	// 仮 - プレイヤー関連
	ctrlFlg = false;
	blockIndex = 0;
	stageIndex = GameMain::GetNowStageIndex();
	debug = false;
	gameover = false;
	ui.SetState(stageIndex + 1);
	player.SetStock(2);
	Position p;
	p.x = 50;
	p.y = 405;
	player.SetPosition(p); // ステージによって変わるかもしれないので念のため
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
	DeleteSoundMem(snd_bubble);
};

AbstractScene* Game::Update() {

	ui.SetScore(gimmick.GetOnBubbleCrackChanged());
	ui.SetHighScore(player.GetPosition().y);

	// 仮 - ステージ上のブロックとプレイヤーの当たり判定
	for (int i = 0; i < stage.GetFootingMax(stageIndex); i++) {
		if (player.GetState() == 0) {
			blockData = stage.GetBlock(stageIndex, blockIndex);
			if (blockIndex >= (stage.GetFootingMax(stageIndex) - 1)) blockIndex = 0;
			else blockIndex++;
		};
		player.SetCollide(blockData);
		player.SetState(CheckCollide(player.GetCollide(), blockData));
	};

	// 仮 - 海に落ちた時の残機処理
	if (SCREEN_HEIGHT + 50 < (player.GetPosition().y - player.GetSize().height)) {
		player.Miss(MISS_FALLSEA);
	};

	// 仮 - ダメージブロックとの判定、ダメージ処理
	Collide collideA, collideB, collideC;
	collideA = player.GetWeakCollide();
	collideB.ul.x = damageBlock[0];
	collideB.ul.y = damageBlock[1];
	collideB.lr.x = damageBlock[2];
	collideB.lr.y = damageBlock[3];
	collideC.ul.x = damageBlock[4];
	collideC.ul.y = damageBlock[5];
	collideC.lr.x = damageBlock[6];
	collideC.lr.y = damageBlock[7];
	if ((CheckCollide(collideA, collideB) == 0) && (CheckCollide(collideA, collideC) == 0)) damageFlg = true;
	if (CheckCollide(collideA, collideB) >= 1 && damageFlg) {
		player.Damage();
		damageFlg = false;
	}
	else if (CheckCollide(collideA, collideC) >= 1 && damageFlg) {
		player.Miss(MISS_LIGHTNING);
		damageFlg = false;
	};

	// 仮 - バブルとの当たり判定
	collideA = player.GetCollide();
	for (int i = 0; i < BUBBLE_MAX; i++) {
		if (gimmick.GetBubbleFlg(i)) {
			collideB = gimmick.GetBubbleCollide(i);
			int isCollide = CheckCollide(collideA, collideB);
			if (isCollide && (gimmick.GetBubbleFlg(i) <= 10)) {
				gimmick.SetBubbleFlg(i, 10);
				effect.Point(player.GetPosition().x, (player.GetPosition().y - player.GetSize().height), 1);
				if (CheckSoundMem(snd_bubble) == 0) PlaySoundMem(snd_bubble, DX_PLAYTYPE_BACK, TRUE);
			}; // スコア表示されない・バブルが消えない時あり
		};
	};

	// 仮 - 水しぶき
	if (SCREEN_HEIGHT + 10 < (player.GetPosition().y - player.GetSize().height)) effect.Splash(player.GetPosition().x, (SCREEN_HEIGHT - 50));

	// 仮 - 2キーかL/Rボタンを押すとプレイヤーの上にゲットポイント表示
	if(PadInput::OnPressed(XINPUT_BUTTON_LEFT_SHOULDER) || PadInput::OnPressed(XINPUT_BUTTON_RIGHT_SHOULDER) || CheckHitKey(KEY_INPUT_2)) effect.Point(player.GetPosition().x, (player.GetPosition().y - player.GetSize().height), 1);

	// 仮 - Pキーでポーズ
	if (!CheckHitKey(KEY_INPUT_P) && !CheckHitKey(KEY_INPUT_O) && !CheckHitKey(KEY_INPUT_1) && !CheckHitKey(KEY_INPUT_B)) ctrlFlg = true;
	if ((CheckHitKey(KEY_INPUT_P) && ctrlFlg) || PadInput::OnPress(XINPUT_BUTTON_START)) {
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
	else if ((CheckHitKey(KEY_INPUT_O) && ctrlFlg) || PadInput::OnPress(XINPUT_BUTTON_X)) {
		int si = GameMain::GetNowStageIndex();
		if (si < 4) GameMain::SetStageIndex(GameMain::GetNowStageIndex() + 1);
		else GameMain::SetStageIndex(0);
		return new Game();
	}
	// 仮 - Bキーでシャボン玉
	else if (CheckHitKey(KEY_INPUT_B) && ctrlFlg) {
		gimmick.SpawnBubble(player.GetPosition().x);
		ctrlFlg = false;
	};

	// 仮 - Rキーでリセット
	if (CheckHitKey(KEY_INPUT_R) || PadInput::OnPress(XINPUT_BUTTON_Y)) return new Game();

	// 仮 - ESCキーでタイトル
	if (CheckHitKey(KEY_INPUT_ESCAPE) || PadInput::OnPress(XINPUT_BUTTON_BACK)) return new Title();

	if (state != 1) player.Update();

	// ゲームオーバー時の処理
	if ((player.GetStock() == -1) && !gameover) {
		state = 1;
		PlaySoundMem(snd_gameOver, DX_PLAYTYPE_BACK, TRUE);
		gameover = true;
	};
	if (gameover && (CheckSoundMem(snd_gameOver) == 0)) {
		GameMain::SetStageIndex(0);
		return new Title();
	};

	ui.SetStock(player.GetStock());
	
	stage.SetNowStage(stageIndex);
	//gimmick.SetPlayerCollide(player.GetCollide());
	enemy.SetPlayerCollide(player.GetCollide());

	if (state != 1) { // ポーズか否か
		effect.Update();

		ui.Update();

		stage.Update();
		gimmick.Update();

		// 雷
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
		};

		if (CheckHitKey(KEY_INPUT_E)) fish.Spawn();
		enemy.Update();
		fish.Update();
	};
	
	return this;
};

void Game::Draw() const {

	stage.Draw();

	ui.Draw();

	if (state != 1) {
		gimmick.Draw();

		player.Draw();
		effect.Draw();

		enemy.Draw();
		fish.Draw();

		if (debug) player.Debug();
		//if (gameover) DrawFormatString(10, 50, 0xffffff, "Rキーでリセット（メモリ占有に注意）");
		//if (gameover) DrawFormatString(10, 65, 0xffffff, "Pキーでそのまま続行");

		DrawBox(damageBlock[0], damageBlock[1], damageBlock[2], damageBlock[3], 0xff0000, FALSE);
		DrawBox(damageBlock[4], damageBlock[5], damageBlock[6], damageBlock[7], 0xffff00, FALSE);

		DrawExtendGraph(damageBlock[4], damageBlock[5], damageBlock[6], damageBlock[7], Thunder[ThunderAnimFlg], TRUE);
	};

	stage.DrawSea();
};

int GameMain::stageIndex = 0;