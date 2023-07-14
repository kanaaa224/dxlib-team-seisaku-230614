/********************************
* ゲームプレイヤー処理
* 担当：島袋
********************************/
#include "main.h"

GamePlayer::GamePlayer() {
	Init();

	// 画像読み込み
	if ((LoadDivGraph("Resources/Images/Player/Player_animation.png", 30, 8, 4, 64, 64, img_player)) == -1) throw "ERROR : PLAYER IMG";
};

GamePlayer::~GamePlayer() {
	for (int i = 0; i < 30; i++) {
		DeleteGraph(img_player[i]);
	};
};

void GamePlayer::Init() {
	state = 0;
	player.hp = 0;

	player.position.x = 50; //50
	player.position.y = 380; //380

	player.size.width = 15;
	player.size.height = 25;

	speed[MOVE_SPEED] = 0;
	speed[FALL_SPEED] = 1;

	flapCount = 0;

	turnState = true;
	animState = 0;

	frameCounter = 0;

	leftEndX = player.position.x - player.size.width;
	rightEndX = player.position.x + player.size.width;
};

void GamePlayer::Update() {

	frameCounter++;

	inputX = PadInput::GetLStick().x;

	if (CheckHitKey(KEY_INPUT_A)) {
		inputX = -1.0;
	}
	else if (CheckHitKey(KEY_INPUT_D)) {
		inputX = 1.0;
	};

	float jumpForce = -0.1;
	float fallSpeedMax = -jumpForce * 21;

	if (!flapCount && (PadInput::OnPress(XINPUT_BUTTON_B) || PadInput::OnPressed(XINPUT_BUTTON_A) || CheckHitKey(KEY_INPUT_SPACE))) {
		flapCount = 12;
		animState = 0;
		if (inputX >= 0.3 || inputX <= -0.3) {
			flightMove = 12;
		};
	};

	if (flapCount) {
		speed[FALL_SPEED] += jumpForce;
		if (speed[FALL_SPEED] < jumpForce * 25) {
			speed[FALL_SPEED] = jumpForce * 25;
		};
	}
	else {
		speed[FALL_SPEED] += 0.1;
		animState++;
		if (fallSpeedMax < speed[FALL_SPEED]) {
			speed[FALL_SPEED] = fallSpeedMax;
		};
	};
	player.position.y += speed[FALL_SPEED];

	if (--flapCount < 0) {
		flapCount = 0;
	};

	state = 0;

	// 海
	if (SCREEN_HEIGHT < player.position.y - player.size.height) {
		Init();
	};

	// 地面
	if (player.state == 1) {
		player.position.y -= 0.1;
		//player.position.y = collideData.ul.y - player.size.height;
		//if ((player.position.y + player.size.height - 0.2) > collideData.ul.y) {
		//	player.position.y -= 0.4;
		//}
		//else {
		//	player.position.y -= 0.1;
		//};
		state = 1;
		if (speed[FALL_SPEED] > 0.0f) {
			speed[FALL_SPEED] = 0;
		};
	};

	bool wallHit = false;

	// 天井
	if (player.state == 2) {
		player.position.y = collideData.lr.y + player.size.height + 1;
		wallHit = true;
	};

	// ステージの上端
	if (player.position.y - player.size.height <= 0) {
		player.position.y += 0.1;
		wallHit = true;
	};

	if (wallHit) {
		speed[FALL_SPEED] *= -1;
	};


	// 移動
	float moveSpeedMax = 2.3;

	if ((state != 0) || flightMove) {
		if (inputX >= 0.3) {
			if (speed[MOVE_SPEED] < 0 && (state != 0)) {
				speed[MOVE_SPEED] += 0.2;
			};
			turnState = true;
			speed[MOVE_SPEED] += 0.2;
			animState++;
			if (moveSpeedMax < speed[MOVE_SPEED]) {
				speed[MOVE_SPEED] = moveSpeedMax;
			};
		}
		else if (inputX <= -0.3) {
			if (0 < speed[MOVE_SPEED] && (state != 0)) {
				speed[MOVE_SPEED] -= 0.2;
			};
			turnState = false;
			speed[MOVE_SPEED] -= 0.2;
			animState++;
			if (speed[MOVE_SPEED] < -moveSpeedMax) {
				speed[MOVE_SPEED] = -moveSpeedMax;
			};
		}
		else if ((state != 0)) {
			if (0 < speed[MOVE_SPEED]) {
				speed[MOVE_SPEED] -= 0.2;
				if (speed[MOVE_SPEED] < 0) {
					speed[MOVE_SPEED] = 0;
				};
			}
			else if (speed[MOVE_SPEED] < 0) {
				speed[MOVE_SPEED] += 0.2;
				if (0 < speed[MOVE_SPEED]) {
					speed[MOVE_SPEED] = 0;
				};
			};
			animState = 0;
		};
	};

	if (--flightMove < 0 || (inputX < 0.3 && inputX > -0.3)) {
		flightMove = 0;
	};

	player.position.x += speed[MOVE_SPEED];


	// 画面端に到達すると反対の画面端に移動
	if (player.position.x <= 0) {
		player.position.x = SCREEN_WIDTH - 1; // 画面左端時
	}
	else if (SCREEN_WIDTH <= player.position.x) {
		player.position.x = 0 + 1;            // 画面右端時
	};

	// プレイヤー右端の座標を更新
	leftEndX = player.position.x - player.size.width;
	if (leftEndX <= 0) {
		leftEndX = SCREEN_WIDTH + leftEndX;
	};

	// プレイヤー左端の座標を更新
	rightEndX = player.position.x + player.size.width;
	if (SCREEN_WIDTH <= rightEndX) {
		rightEndX = rightEndX - SCREEN_WIDTH;
	};


	wallHit = false;

	// 壁で移動を止める
	if (player.state == 3) {
		//player.position.x--;
		player.position.x = collideData.ul.x - player.size.width - 1;

		if (player.position.x <= 0) {
			player.position.x = SCREEN_WIDTH - 1;
		}
		else if (SCREEN_WIDTH <= player.position.x) {
			player.position.x = 0 + 1;
		};

		leftEndX = player.position.x - player.size.width;
		if (leftEndX <= 0) {
			leftEndX = SCREEN_WIDTH + leftEndX;
		};

		rightEndX = player.position.x + player.size.width;
		if (SCREEN_WIDTH <= rightEndX) {
			rightEndX = rightEndX - SCREEN_WIDTH;
		};

		wallHit = true;
	};

	if (player.state == 4) {
		//player.position.x++;
		player.position.x = collideData.lr.x + player.size.width + 1;

		if (player.position.x <= 0) {
			player.position.x = SCREEN_WIDTH - 1;
		}
		else if (SCREEN_WIDTH <= player.position.x) {
			player.position.x = 0 + 1;
		};

		leftEndX = player.position.x - player.size.width;
		if (leftEndX <= 0) {
			leftEndX = SCREEN_WIDTH + leftEndX;
		};

		rightEndX = player.position.x + player.size.width;
		if (SCREEN_WIDTH <= rightEndX) {
			rightEndX = rightEndX - SCREEN_WIDTH;
		};

		wallHit = true;
	};

	if (wallHit) {
		speed[MOVE_SPEED] *= -0.9;
	};
};

void GamePlayer::Draw() const {
	int anim = 0;

	if ((state == 0)) { // 飛行
		anim = abs(-2 + (flapCount / 3 % 4));
		if (flapCount == 0) {
			anim += animState / 25 % 3;
		};
		anim = anim + 16;		
	}
	else if (speed[MOVE_SPEED] == 0) { // 待機
		anim = frameCounter / 25 % 3;
	}
	else if ((state == 1)) { // 地面
		anim = animState / 5 % 3;
		if ((inputX > -0.3 && 0.3 > inputX) || (speed[MOVE_SPEED] < 0 && inputX >= 0.3) || (0 < speed[MOVE_SPEED] && -0.3 >= inputX)) { // スリップ
			anim = 11;
		}
		else { // 歩行
			anim = anim + 8;
		};
	};

	// ワープ用にゲーム画面分の間隔をあけて3体描画する
	DrawRotaGraph2(player.position.x, player.position.y, 32, 64 - player.size.height, 1, 0, img_player[anim], true, turnState);
	DrawRotaGraph2(player.position.x - SCREEN_WIDTH, player.position.y, 32, 64 - player.size.height, 1, 0, img_player[anim], true, turnState);
	DrawRotaGraph2(player.position.x + SCREEN_WIDTH, player.position.y, 32, 64 - player.size.height, 1, 0, img_player[anim], true, turnState);

	// 仮
	DrawBox(player.position.x - player.size.width, player.position.y - player.size.height, player.position.x + player.size.width, player.position.y + player.size.height, 0xffffff, false);
};