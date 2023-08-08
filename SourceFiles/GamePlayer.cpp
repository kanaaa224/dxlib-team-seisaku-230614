/********************************
* ゲームプレイヤー処理
* 担当：島袋
********************************/
#include "main.h"

GamePlayer::GamePlayer() {
	stock = 2;

	Init();

	if (LoadDivGraph("Resources/Images/Player/Player_animation.png", 31, 8, 4, 64, 64, img_player) == -1) throw;

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

	//if ((snd_se_electricShock = LoadSoundMem("Resources/Sounds/SE_.wav")) == -1) throw;
	//ChangeVolumeSoundMem((255 / 100) * 100, snd_se_electricShock);

	if ((snd_se_fall = LoadSoundMem("Resources/Sounds/SE_Falling.wav")) == -1) throw;
	ChangeVolumeSoundMem((255 / 100) * 100, snd_se_fall);

	if ((snd_se_fell = LoadSoundMem("Resources/Sounds/SE_Splash.wav")) == -1) throw;
	ChangeVolumeSoundMem((255 / 100) * 100, snd_se_fell);
};

GamePlayer::~GamePlayer() {
	for (int i = 0; i < 31; i++) {
		DeleteGraph(img_player[i]);
	};
	DeleteSoundMem(snd_se_flight);
	DeleteSoundMem(snd_se_walk);
	//DeleteSoundMem(snd_se_bound);
	DeleteSoundMem(snd_se_restart);
	DeleteSoundMem(snd_se_crack);
	//DeleteSoundMem(snd_se_electricShock);
	DeleteSoundMem(snd_se_fall);
	DeleteSoundMem(snd_se_fell);
};

void GamePlayer::Init() {
	frameCounter = 0;

	player.hp = 2;
	player.position.x = PLAYER_DEFAULT_POSITION_X;
	player.position.y = PLAYER_DEFAULT_POSITION_Y;
	player.size.width = 15;
	player.size.height = 25;

	inputX = 0.0f;
	flapCount = 0;
	flightMove = 0;
	state[COLLIDE] = 0;
	state[TURN] = 1;
	state[ANIM] = 0;
	state[BLINK] = 1;
	state[MISS] = 0;
	speed[MOVE] = 0.0f;
	speed[FALL] = 1.0f;
};

void GamePlayer::Update() {
	frameCounter++;
	if (player.hp > 0) {
		//if (player.state >= 1) PlaySoundMem(snd_se_bound, DX_PLAYTYPE_BACK, TRUE);

		//////////////////////////////////////////////////////////////////////
		// コントローラー・キーボード操作
		//////////////////////////////////////////////////////////////////////

		inputX = PadInput::GetLStick().x;
		if (PadInput::OnPressed(XINPUT_BUTTON_DPAD_LEFT) || CheckHitKey(KEY_INPUT_A)) inputX = -1.0f;
		else if (PadInput::OnPressed(XINPUT_BUTTON_DPAD_RIGHT) || CheckHitKey(KEY_INPUT_D)) inputX = 1.0f;

		if (!flapCount && (PadInput::OnPress(XINPUT_BUTTON_B) || PadInput::OnPressed(XINPUT_BUTTON_A) || CheckHitKey(KEY_INPUT_SPACE))) {
			flapCount = 10; // 慣性の最適値：12
			state[ANIM] = 0;
			state[BLINK] = 0;
			if (inputX >= INPUT_X_MAGIN || inputX <= -INPUT_X_MAGIN) flightMove = 12;
			PlaySoundMem(snd_se_flight, DX_PLAYTYPE_BACK, TRUE);
		};

		if ((inputX > INPUT_X_MAGIN || inputX < -INPUT_X_MAGIN) || frameCounter >= 700) state[BLINK] = 0;

		if (inputX >= INPUT_X_MAGIN) state[TURN] = 1;
		else if (inputX <= -INPUT_X_MAGIN) state[TURN] = 0;

		//////////////////////////////////////////////////////////////////////
		// 空中の慣性計算、落下処理
		//////////////////////////////////////////////////////////////////////

		float jumpForce = 0.08f,
		   jumpSpeedMax = 2.5f,
		   fallSpeedMax = 2.1f;

		if (player.hp == 1) jumpForce = 0.03f;

		if (flapCount) {
			speed[FALL] -= jumpForce;
			if (speed[FALL] < -jumpSpeedMax) speed[FALL] = -jumpSpeedMax;
		}
		else {
			state[ANIM]++;
			speed[FALL] += jumpForce;
			if (speed[FALL] > fallSpeedMax) speed[FALL] = fallSpeedMax;
		};

		if (--flapCount < 0) flapCount = 0;

		player.position.y += speed[FALL];

		//////////////////////////////////////////////////////////////////////
		// 地面・天井・壁との判定、慣性計算、移動処理
		//////////////////////////////////////////////////////////////////////

		state[COLLIDE] = 0;

		bool wallHit = false;

		// 地面
		if (player.state == 1) {
			player.position.y -= jumpForce;
			state[COLLIDE] = 1;
			if (speed[FALL] > 0.0f) speed[FALL] = 0;
			if (inputX >= INPUT_X_MAGIN || inputX <= -INPUT_X_MAGIN) if (CheckSoundMem(snd_se_walk) == 0) PlaySoundMem(snd_se_walk, DX_PLAYTYPE_BACK, TRUE);
		}
		else StopSoundMem(snd_se_walk);

		// 天井
		if (player.state == 2) {
			player.position.y = collideData.lr.y + player.size.height + 1;

			wallHit = true;
		};

		// ステージ（画面）の上端
		if (player.position.y - player.size.height <= 0) {
			player.position.y += 0.1f;

			wallHit = true;
		};

		if (wallHit) speed[FALL] *= -1;

		wallHit = false;

		// 壁
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

		if (wallHit) speed[MOVE] = -speed[MOVE];

		//////////////////////////////////////////////////////////////////////
		// 移動速度・慣性計算、移動処理
		//////////////////////////////////////////////////////////////////////

		float moveSpeed, moveSpeedMax = 2.3f;

		if (flightMove) {
			moveSpeed = 0.15f;
			if (inputX >= INPUT_X_MAGIN) {
				if (speed[MOVE] < 0) speed[MOVE] += 0.05f;
				else speed[MOVE] += moveSpeed;
   				state[ANIM]++;
				if (speed[MOVE] > moveSpeedMax) speed[MOVE] = moveSpeedMax;
			}
			else if (inputX <= -INPUT_X_MAGIN) {
				if (speed[MOVE] > 0) speed[MOVE] -= 0.05f;
				else speed[MOVE] -= moveSpeed;
				state[ANIM]++;
				if (speed[MOVE] < -moveSpeedMax) speed[MOVE] = -moveSpeedMax;
			};
		}
		else if (state[COLLIDE]) {
			moveSpeed = 0.2f;
			if (inputX >= INPUT_X_MAGIN) {
				speed[MOVE] += moveSpeed;
				state[ANIM]++;
				if (speed[MOVE] > moveSpeedMax) speed[MOVE] = moveSpeedMax;
			}
			else if (inputX <= -INPUT_X_MAGIN) {
				speed[MOVE] -= moveSpeed;
				state[ANIM]++;
				if (speed[MOVE] < -moveSpeedMax) speed[MOVE] = -moveSpeedMax;
			}
			else {
				moveSpeed = 0.1f;
				if (speed[MOVE] > 0) {
					speed[MOVE] -= moveSpeed;
					if (speed[MOVE] < 0) speed[MOVE] = 0;
				}
				else if (speed[MOVE] < 0) {
					speed[MOVE] += moveSpeed;
					if (speed[MOVE] > 0) speed[MOVE] = 0;
				};
				state[ANIM] = 0;
			};
		};
		/*
		if (state[COLLIDE] || flightMove) {
			if (inputX >= INPUT_X_MAGIN) {
				if (speed[MOVE] < 0 && state[COLLIDE]) speed[MOVE] += 0.2f;
				else speed[MOVE] += 0.2f;
				state[TURN] = 1;
				state[ANIM]++;
				if (moveSpeedMax < speed[MOVE]) speed[MOVE] = moveSpeedMax;
			}
			else if (inputX <= -INPUT_X_MAGIN) {
				if (0 < speed[MOVE] && state[COLLIDE]) speed[MOVE] -= 0.2f;
				else speed[MOVE] -= 0.2f;
				state[TURN] = 0;
				state[ANIM]++;
				if (speed[MOVE] < -moveSpeedMax) speed[MOVE] = -moveSpeedMax;
			}
			else if (state[COLLIDE]) {
				moveSpeed = 0.1f;
				if (0 < speed[MOVE]) {
					speed[MOVE] -= moveSpeed;
					if (speed[MOVE] < 0) speed[MOVE] = 0;
				}
				else if (speed[MOVE] < 0) {
					speed[MOVE] += moveSpeed;
					if (0 < speed[MOVE]) speed[MOVE] = 0;
				};
				state[ANIM] = 0;
			};
		};
		*/

		if (--flightMove < 0 || (inputX < INPUT_X_MAGIN && inputX > -INPUT_X_MAGIN)) flightMove = 0;

		player.position.x += speed[MOVE];

		//////////////////////////////////////////////////////////////////////
		// 画面左右端のワープ処理
		//////////////////////////////////////////////////////////////////////

		if (player.position.x <= 0) player.position.x = SCREEN_WIDTH - 1;      // 画面左端時
		else if (SCREEN_WIDTH <= player.position.x) player.position.x = 0 + 1; // 画面右端時		
	}

	//////////////////////////////////////////////////////////////////////
	// ミス・ダメージ処理
	//////////////////////////////////////////////////////////////////////

	else if (player.hp == -1) {
		if (SCREEN_HEIGHT + 10 < (player.position.y - player.size.height)) {
			StopSoundMem(snd_se_fall);
			player.hp = -3;
		}
		else {
			if (CheckSoundMem(snd_se_fall) == 0) {
				PlaySoundMem(snd_se_fall, DX_PLAYTYPE_BACK, TRUE);
				speed[FALL] = -3.0f;
			};
			speed[FALL] += 0.1f;
			player.position.y += speed[FALL];
			state[MISS] = frameCounter;
		};
	}
	else if (player.hp == -2) {
		//PlaySoundMem(snd_se_electricShock, DX_PLAYTYPE_BACK, TRUE);
		if ((state[MISS] + 60) < frameCounter) {
			//StopSoundMem(snd_se_electricShock);
			player.hp = -1;
		};
	}
	else if (player.hp == -3) {
		if ((CheckSoundMem(snd_se_fell) == 0) && (frameCounter == (state[MISS] + 2))) {
			PlaySoundMem(snd_se_fell, DX_PLAYTYPE_BACK, TRUE);
		};
		if ((state[MISS] + 90) < frameCounter) {
			stock--;
			player.hp = -10;
		};
	}
	else if (player.hp == -10) Restart();
};

void GamePlayer::Draw() const {
	int anim = 0;
	if (state[BLINK]) { // スタート時の点滅
		if (frameCounter % 20 == 0) anim = 3;
		else anim = 1;
	}
	else if (player.hp == -1) { // ミスで落下時
		anim = frameCounter / 3 % 3;
		anim += 27;
	}
	else if (player.hp == -2) { // 感電
		anim = frameCounter / 2 % 2;
		anim += 29;
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
	else if (state[COLLIDE]) { // 地面
		anim = state[ANIM] / 5 % 3;
		if ((inputX > -INPUT_X_MAGIN && INPUT_X_MAGIN > inputX) || (speed[MOVE] < 0 && inputX >= INPUT_X_MAGIN) || (0 < speed[MOVE] && -INPUT_X_MAGIN >= inputX)) anim = 11; // スリップ
		else anim = anim + 8; // 歩行
		if (player.hp == 1) anim += 5;
	};

	// ワープ用にゲーム画面分の間隔をあけて3体描画する
	DrawRotaGraph2((int)player.position.x, (int)player.position.y, 32, 64 - (int)player.size.height, 1.0f, 0, img_player[anim], TRUE, state[TURN]);
	DrawRotaGraph2((int)player.position.x - SCREEN_WIDTH, (int)player.position.y, 32, 64 - (int)player.size.height, 1.0f, 0, img_player[anim], TRUE, state[TURN]);
	DrawRotaGraph2((int)player.position.x + SCREEN_WIDTH, (int)player.position.y, 32, 64 - (int)player.size.height, 1.0f, 0, img_player[anim], TRUE, state[TURN]);
};