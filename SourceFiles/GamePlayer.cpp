/********************************
* ゲームプレイヤー処理
* 担当：島袋
********************************/
#include "main.h"

GamePlayer::GamePlayer() {
	stock = 2; // 残機

	Init();

	if (LoadDivGraph("Resources/Images/Player/Player_animation.png", 30, 8, 4, 64, 64, img_player) == -1) throw;

	if ((snd_se_flight = LoadSoundMem("Resources/Sounds/SE_PlayerJump.wav")) == -1) throw;
	ChangeVolumeSoundMem((255 / 100) * 50, snd_se_flight);

	if ((snd_se_walk = LoadSoundMem("Resources/Sounds/SE_PlayerWalk.wav")) == -1) throw;
	ChangeVolumeSoundMem((255 / 100) * 100, snd_se_walk);

	//if ((snd_se_bound = LoadSoundMem("Resources/Sounds/SE_PlayerBound.wav")) == -1) throw;
	//ChangeVolumeSoundMem((255 / 100) * 100, snd_se_bound);

	if ((snd_se_restart = LoadSoundMem("Resources/Sounds/SE_Restart.wav")) == -1) throw;
	ChangeVolumeSoundMem((255 / 100) * 100, snd_se_restart);

	if ((snd_se_crack = LoadSoundMem("Resources/Sounds/SE_crack.wav")) == -1) throw;
	ChangeVolumeSoundMem((255 / 100) * 100, snd_se_crack);

	if ((snd_se_fall = LoadSoundMem("Resources/Sounds/SE_Falling.wav")) == -1) throw;
	ChangeVolumeSoundMem((255 / 100) * 100, snd_se_fall);

	if ((snd_se_fell = LoadSoundMem("Resources/Sounds/SE_Splash.wav")) == -1) throw;
	ChangeVolumeSoundMem((255 / 100) * 100, snd_se_fell);
};

GamePlayer::~GamePlayer() {
	for (int i = 0; i < 30; i++) {
		DeleteGraph(img_player[i]);
	};
	DeleteSoundMem(snd_se_flight);
	DeleteSoundMem(snd_se_walk);
	//DeleteSoundMem(snd_se_bound);
	DeleteSoundMem(snd_se_restart);
	DeleteSoundMem(snd_se_crack);
	DeleteSoundMem(snd_se_fall);
	DeleteSoundMem(snd_se_fell);
};

void GamePlayer::Init() {
	frameCounter = 0;

	player.hp = 2;
	player.position.x = FIRST_POSITION_X;
	player.position.y = FIRST_POSITION_Y;
	player.size.width = 15;
	player.size.height = 25;

	inputX = 0.0f;
	flapCount = 0;
	flightMove = 0;
	state[COLLIDE] = 0;
	state[TURN] = 1;
	state[ANIM] = 0;
	state[BLINK] = 1;
	speed[MOVE] = 0.0f;
	speed[FALL] = 1.0f;
};

void GamePlayer::Update() {

	frameCounter++;

	if (player.hp > 0) {

		//////////////////////////////////////////////////////////////////////
		// コントローラー・キーボード操作
		//////////////////////////////////////////////////////////////////////

		inputX = PadInput::GetLStick().x;
		if (PadInput::OnPressed(XINPUT_BUTTON_DPAD_LEFT) || CheckHitKey(KEY_INPUT_A)) inputX = -1.0f;
		else if (PadInput::OnPressed(XINPUT_BUTTON_DPAD_RIGHT) || CheckHitKey(KEY_INPUT_D)) inputX = 1.0f;
		if (inputX != 0.0f || frameCounter >= 700) state[BLINK] = 0;

		if (!flapCount && (PadInput::OnPress(XINPUT_BUTTON_B) || PadInput::OnPressed(XINPUT_BUTTON_A) || CheckHitKey(KEY_INPUT_SPACE))) {
			flapCount = 10; // 慣性の最適値：12
			state[ANIM] = 0;
			state[BLINK] = 0;
			if (inputX >= 0.3f || inputX <= -0.3f) flightMove = 12;
			PlaySoundMem(snd_se_flight, DX_PLAYTYPE_BACK, TRUE);
		};

		//////////////////////////////////////////////////////////////////////
		// 空中の慣性計算、落下処理
		//////////////////////////////////////////////////////////////////////

		float jumpForce = -0.1f;
		float fallSpeedMax = -jumpForce * 21.0f;
		if (flapCount) {
			speed[FALL] += jumpForce;
			if (speed[FALL] < jumpForce * 25.0f) speed[FALL] = jumpForce * 25.0f;
		}
		else {
			speed[FALL] += 0.1f;
			state[ANIM]++;
			if (fallSpeedMax < speed[FALL]) speed[FALL] = fallSpeedMax;
		};
		player.position.y += speed[FALL];
		if (--flapCount < 0) flapCount = 0;

		//////////////////////////////////////////////////////////////////////
		// 地面・天井・海との判定、慣性計算、移動処理
		//////////////////////////////////////////////////////////////////////

		state[COLLIDE] = 0;

		// 海
		//if (SCREEN_HEIGHT + 100 < (player.position.y - player.size.height)) Restart();

		// 地面
		if (player.state == 1) {
			player.position.y -= 0.1f;
			//player.position.y = collideData.ul.y - player.size.height;
			//if ((player.position.y + player.size.height - 0.2) > collideData.ul.y) {
			//	player.position.y -= 0.4;
			//}
			//else {
			//	player.position.y -= 0.1;
			//};
			state[COLLIDE] = 1;
			if (speed[FALL] > 0.0f) speed[FALL] = 0;
			if (inputX != 0.0f) if (CheckSoundMem(snd_se_walk) == 0) PlaySoundMem(snd_se_walk, DX_PLAYTYPE_BACK, TRUE);
			//else StopSoundMem(snd_se_walk);
		}
		else StopSoundMem(snd_se_walk);

		bool wallHit = false;

		// 天井
		if (player.state == 2) {
			player.position.y = collideData.lr.y + player.size.height + 1;

			wallHit = true;
		};

		// ステージの上端
		if (player.position.y - player.size.height <= 0) {
			//if (speed[FALL] == 0.0) speed[FALL] += 1;
			player.position.y += 0.1f;

			wallHit = true;
		};

		if (wallHit) speed[FALL] *= -1;

		//////////////////////////////////////////////////////////////////////
		// 移動速度・慣性の計算、移動処理
		//////////////////////////////////////////////////////////////////////

		float moveSpeedMax = 2.3f;
		if ((state[COLLIDE] != 0) || flightMove) {
			if (inputX >= 0.3) {
				if (speed[MOVE] < 0 && (state[COLLIDE] != 0)) speed[MOVE] += 0.2f;
				state[TURN] = 1;
				speed[MOVE] += 0.2f;
				state[ANIM]++;
				if (moveSpeedMax < speed[MOVE]) speed[MOVE] = moveSpeedMax;
			}
			else if (inputX <= -0.3) {
				if (0 < speed[MOVE] && (state[COLLIDE] != 0)) speed[MOVE] -= 0.2f;
				state[TURN] = 0;
				speed[MOVE] -= 0.2f;
				state[ANIM]++;
				if (speed[MOVE] < -moveSpeedMax) speed[MOVE] = -moveSpeedMax;
			}
			else if (state[COLLIDE] != 0) {
				if (0 < speed[MOVE]) {
					speed[MOVE] -= 0.2f;
					if (speed[MOVE] < 0) speed[MOVE] = 0;
				}
				else if (speed[MOVE] < 0) {
					speed[MOVE] += 0.2f;
					if (0 < speed[MOVE]) speed[MOVE] = 0;
				};
				state[ANIM] = 0;
			};
		};
		if (--flightMove < 0 || (inputX < 0.3 && inputX > -0.3)) flightMove = 0;
		player.position.x += speed[MOVE];

		//////////////////////////////////////////////////////////////////////
		// 画面左右端のワープ処理
		//////////////////////////////////////////////////////////////////////

		if (player.position.x <= 0) player.position.x = SCREEN_WIDTH - 1;      // 画面左端時
		else if (SCREEN_WIDTH <= player.position.x) player.position.x = 0 + 1; // 画面右端時

		//////////////////////////////////////////////////////////////////////
		// 壁の判定と跳ね返り処理
		//////////////////////////////////////////////////////////////////////

		wallHit = false;
		if (player.state == 3) {
			//player.position.x--;
			player.position.x = collideData.ul.x - player.size.width - 1;

			wallHit = true;
		};
		if (player.state == 4) {
			//player.position.x++;
			player.position.x = collideData.lr.x + player.size.width + 1;

			wallHit = true;
		};
		if (wallHit) speed[MOVE] *= -0.9f;

	}
	else if (player.hp == -1) {
		if (CheckSoundMem(snd_se_fall) == 0) PlaySoundMem(snd_se_fall, DX_PLAYTYPE_BACK, TRUE);
		player.position.y += 2.5f;
		if (SCREEN_HEIGHT + 10 < (player.position.y - player.size.height)) {
			StopSoundMem(snd_se_fall);
			PlaySoundMem(snd_se_fell, DX_PLAYTYPE_NORMAL, TRUE);
			stock--;
			player.hp = -10;
		};
	}
	else if (player.hp == -2) {
		// kaminari
		PlaySoundMem(snd_se_fell, DX_PLAYTYPE_NORMAL, TRUE);
		stock--;
		player.hp = -10;
	}
	else if (player.hp == -3) {
		PlaySoundMem(snd_se_fell, DX_PLAYTYPE_NORMAL, TRUE);
		stock--;
		player.hp = -10;
	}
	else if (player.hp == -10) {
		Restart();
	};
};

void GamePlayer::Draw() const {
	int anim = 0;
	if (state[BLINK]) { // スタート時の点滅
		if (frameCounter % 20 == 0) anim = 3;
		else anim = 1;
	}
	else if (player.hp == -1) { // ミスで落下時
		anim = frameCounter / 2 % 3;
		anim += 27;
	}
	else if (state[COLLIDE] == 0) { // 飛行
		anim = abs(-2 + (flapCount / 3 % 4));
		if (flapCount == 0) anim += state[ANIM] / 25 % 3;
		anim = anim + 17;
		if (player.hp == 1) anim += 5;
	}
	else if (speed[MOVE] == 0) { // 待機
		anim = frameCounter / 25 % 3;
		if (player.hp == 1) anim += 4;
	}
	else if (state[COLLIDE] == 1) { // 地面
		anim = state[ANIM] / 5 % 3;
		if ((inputX > -0.3 && 0.3 > inputX) || (speed[MOVE] < 0 && inputX >= 0.3) || (0 < speed[MOVE] && -0.3 >= inputX)) anim = 11; // スリップ
		else anim = anim + 8; // 歩行
		if (player.hp == 1) anim += 5;
	};

	// ワープ用にゲーム画面分の間隔をあけて3体描画する
	DrawRotaGraph2((int)player.position.x, (int)player.position.y, 32, 64 - (int)player.size.height, 1.0f, 0, img_player[anim], TRUE, state[TURN]);
	DrawRotaGraph2((int)player.position.x - SCREEN_WIDTH, (int)player.position.y, 32, 64 - (int)player.size.height, 1.0f, 0, img_player[anim], TRUE, state[TURN]);
	DrawRotaGraph2((int)player.position.x + SCREEN_WIDTH, (int)player.position.y, 32, 64 - (int)player.size.height, 1.0f, 0, img_player[anim], TRUE, state[TURN]);
};