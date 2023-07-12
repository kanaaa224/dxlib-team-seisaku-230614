/********************************
* ゲームプレイヤー処理
* 担当：島袋
********************************/
#include "main.h"

// プレイヤークラスのコンストラクタ
GamePlayer::GamePlayer() {
	// 初期化処理
	Init();

	// 画像読み込み
	if ((LoadDivGraph("Resources/Images/Player/Player_animation.png", 30, 8, 4, 64, 64, img_player)) == -1) throw "ERROR : PLAYER IMG";
};

// プレイヤークラスのデストラクタ
GamePlayer::~GamePlayer() {
	for (int i = 0; i < 30; i++) {
		DeleteGraph(img_player[i]);
	};
};

void GamePlayer::Init() {
	player.state = 0;
	player.hp = 0;

	player.position.x = 50; //50
	player.position.y = 380; //380

	player.size.width = 15;
	player.size.height = 45 / 2;

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

	inputX = PadInput::GetLStick().x;

	if (CheckHitKey(KEY_INPUT_A)) {
		inputX = -1.0;
	}
	else if (CheckHitKey(KEY_INPUT_D)) {
		inputX = 1.0;
	};

	int BlockSize = BLOCK_SIZE;

	float jumpForce = -0.1;
	float fallSpeedMax = -jumpForce * 21;

	if (!flapCount && (PadInput::OnPress(XINPUT_BUTTON_B) || PadInput::OnPressed(XINPUT_BUTTON_A) || CheckHitKey(KEY_INPUT_SPACE))) {
		flapCount = 12;
		animState = 0;
		//if (player.state)speed[FALL_SPEED] = jumpForce * 12;
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

	bool WallHit = false;

	// 天井
	while (MapData[(int)(player.position.y - player.size.height) / BlockSize][(int)leftEndX / BlockSize] > 0 ||
		MapData[(int)(player.position.y - player.size.height) / BlockSize][(int)player.position.x / BlockSize] > 0 ||
		MapData[(int)(player.position.y - player.size.height) / BlockSize][(int)rightEndX / BlockSize] > 0 ||
		player.position.y - player.size.height <= 0) {
		player.position.y += 0.1;
		WallHit = true;
	};

	if (WallHit) {
		speed[FALL_SPEED] *= -1;
	};

	player.state = false;

	// 床
	while (MapData[(int)(player.position.y + player.size.height) / BlockSize][(int)leftEndX / BlockSize] > 0 ||
		MapData[(int)(player.position.y + player.size.height) / BlockSize][(int)player.position.x / BlockSize] > 0 ||
		MapData[(int)(player.position.y + player.size.height) / BlockSize][(int)rightEndX / BlockSize] > 0 ||
		SCREEN_HEIGHT + BLOCK_SIZE * 2 <= player.position.y + player.size.height + 1) {
		player.position.y -= 0.1;
		player.state = true;
		if (speed[FALL_SPEED] > 0.f) {
			speed[FALL_SPEED] = 0;
		};
	};

	// 移動
	float MoveSpeedMax = 2.3;

	if (player.state || flightMove) {
		if (inputX >= 0.3) {
			if (speed[MOVE_SPEED] < 0 && player.state)speed[MOVE_SPEED] += 0.2;
			turnState = true;
			speed[MOVE_SPEED] += 0.2;
			animState++;
			if (MoveSpeedMax < speed[MOVE_SPEED])speed[MOVE_SPEED] = MoveSpeedMax;
		}
		else if (inputX <= -0.3) {
			if (0 < speed[MOVE_SPEED] && player.state)speed[MOVE_SPEED] -= 0.2;
			turnState = false;
			speed[MOVE_SPEED] -= 0.2;
			animState++;
			if (speed[MOVE_SPEED] < -MoveSpeedMax)speed[MOVE_SPEED] = -MoveSpeedMax;
		}
		else if (player.state) {
			if (0 < speed[MOVE_SPEED]) {
				speed[MOVE_SPEED] -= 0.2;
				if (speed[MOVE_SPEED] < 0)speed[MOVE_SPEED] = 0;
			}
			else if (speed[MOVE_SPEED] < 0) {
				speed[MOVE_SPEED] += 0.2;
				if (0 < speed[MOVE_SPEED])speed[MOVE_SPEED] = 0;
			}
			animState = 0;
		}
	};

	if (--flightMove < 0 || (inputX < 0.3 && inputX > -0.3)) {
		flightMove = 0;
	};

	// プレイヤー横移動反映
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


	WallHit = false;

	// 壁で移動を止める
	bool Wall = false;
	for (float i = 0; i < player.size.height && !Wall; i++) {
		if (MapData[(int)(player.position.y + i) / BlockSize][(int)rightEndX / BlockSize] > 0) Wall = true;
		if (MapData[(int)(player.position.y - i) / BlockSize][(int)rightEndX / BlockSize] > 0) Wall = true;
	};

	while (Wall) {
		player.position.x--;

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

		WallHit = true;

		Wall = false;
		for (float i = 0; i < player.size.height && !Wall; i++) {
			if (MapData[(int)(player.position.y + i) / BlockSize][(int)rightEndX / BlockSize] > 0) Wall = true;
			if (MapData[(int)(player.position.y - i) / BlockSize][(int)rightEndX / BlockSize] > 0) Wall = true;
		}
	};

	Wall = false;
	for (float i = 0; i < player.size.height && !Wall; i++) {
		if (MapData[(int)(player.position.y + i) / BlockSize][(int)leftEndX / BlockSize] > 0) Wall = true;
		if (MapData[(int)(player.position.y - i) / BlockSize][(int)leftEndX / BlockSize] > 0) Wall = true;
	};

	while (Wall) {
		player.position.x++;
		
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

		WallHit = true;

		Wall = false;
		for (float i = 0; i < player.size.height && !Wall; i++)
		{
			if (MapData[(int)(player.position.y + i) / BlockSize][(int)leftEndX / BlockSize] > 0) Wall = true;
			if (MapData[(int)(player.position.y - i) / BlockSize][(int)leftEndX / BlockSize] > 0) Wall = true;
		};
	};

	if (WallHit) {
		speed[MOVE_SPEED] *= -0.9;
	};

	frameCounter++;
};

void GamePlayer::Draw() const {
	int anim = 0;

	if (!player.state) { // 飛行
		anim = abs(-2 + (flapCount / 3 % 4));
		if (flapCount == 0)anim += animState / 25 % 3;

		// ワープ用にゲーム画面分の間隔をあけて3体描画する
		DrawRotaGraph2(player.position.x, player.position.y, 32, 64 - player.size.height, 1, 0, img_player[16 + anim], true, turnState);
		DrawRotaGraph2(player.position.x - SCREEN_WIDTH, player.position.y, 32, 64 - player.size.height, 1, 0, img_player[16 + anim], true, turnState);
		DrawRotaGraph2(player.position.x + SCREEN_WIDTH, player.position.y, 32, 64 - player.size.height, 1, 0, img_player[16 + anim], true, turnState);
	}
	else if (speed[MOVE_SPEED] == 0) { // 待機
		anim = frameCounter / 25 % 3;
		DrawRotaGraph2(player.position.x, player.position.y, 32, 64 - player.size.height, 1, 0, img_player[anim], true, turnState);
		DrawRotaGraph2(player.position.x - SCREEN_WIDTH, player.position.y, 32, 64 - player.size.height, 1, 0, img_player[anim], true, turnState);
		DrawRotaGraph2(player.position.x + SCREEN_WIDTH, player.position.y, 32, 64 - player.size.height, 1, 0, img_player[anim], true, turnState);

	}
	else if (player.state) { // 地面
		anim = animState / 5 % 3;
		if ((inputX > -0.3 && 0.3 > inputX) ||
			(speed[MOVE_SPEED] < 0 && inputX >= 0.3) ||
			(0 < speed[MOVE_SPEED] && -0.3 >= inputX)) { // スリップ
			DrawRotaGraph2(player.position.x, player.position.y, 32, 64 - player.size.height, 1, 0, img_player[11], true, turnState);
			DrawRotaGraph2(player.position.x - SCREEN_WIDTH, player.position.y, 32, 64 - player.size.height, 1, 0, img_player[11], true, turnState);
			DrawRotaGraph2(player.position.x + SCREEN_WIDTH, player.position.y, 32, 64 - player.size.height, 1, 0, img_player[11], true, turnState);
		}
		else { // 歩行
			DrawRotaGraph2(player.position.x, player.position.y, 32, 64 - player.size.height, 1, 0, img_player[8 + anim], true, turnState);
			DrawRotaGraph2(player.position.x - SCREEN_WIDTH, player.position.y, 32, 64 - player.size.height, 1, 0, img_player[8 + anim], true, turnState);
			DrawRotaGraph2(player.position.x + SCREEN_WIDTH, player.position.y, 32, 64 - player.size.height, 1, 0, img_player[8 + anim], true, turnState);
		};
	};

	DrawBox(player.position.x - player.size.width, player.position.y - player.size.height, player.position.x + player.size.width, player.position.y + player.size.height, 0xffffff, false);
};