/********************************
* ゲームプレイヤー処理
* 担当：島袋
********************************/
#include "main.h"

GamePlayer::GamePlayer() {
	Init();

	if (LoadDivGraph("Resources/Images/Player/Player_animation.png", 30, 8, 4, 64, 64, img_player) == -1) throw;
};

GamePlayer::~GamePlayer() {
	for (int i = 0; i < 30; i++) {
		DeleteGraph(img_player[i]);
	};
};

void GamePlayer::Init() {
	frameCounter = 0;

	player.hp = 0;
	player.position.x = 50; //50
	player.position.y = 380; //380
	player.size.width = 15;
	player.size.height = 25;

	inputX = 0.0f;
	flapCount = 0;
	flightMove = 0;
	state[COLLIDE] = 0;
	state[TURN] = 1;
	state[ANIM] = 0;
	speed[MOVE] = 0.0f;
	speed[FALL] = 1.0f;

	leftEndX = player.position.x - player.size.width;
	rightEndX = player.position.x + player.size.width;
};

void GamePlayer::Update() {

	frameCounter++;

	//////////////////////////////////////////////////////////////////////
	// コントローラー・キーボード操作
	//////////////////////////////////////////////////////////////////////

	inputX = PadInput::GetLStick().x;
	if (PadInput::OnPressed(XINPUT_BUTTON_DPAD_LEFT) || CheckHitKey(KEY_INPUT_A)) inputX = -1.0f;
	else if (PadInput::OnPressed(XINPUT_BUTTON_DPAD_RIGHT) || CheckHitKey(KEY_INPUT_D)) inputX = 1.0f;

	if (!flapCount && (PadInput::OnPress(XINPUT_BUTTON_B) || PadInput::OnPressed(XINPUT_BUTTON_A) || CheckHitKey(KEY_INPUT_SPACE))) {
		flapCount = 12;
		state[ANIM] = 0;
		if (inputX >= 0.3f || inputX <= -0.3f) flightMove = 12;
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
	if (SCREEN_HEIGHT < player.position.y - player.size.height) Init();

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
	};

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
	leftEndX = player.position.x - player.size.width;
	if (leftEndX <= 0) leftEndX = SCREEN_WIDTH + leftEndX;
	rightEndX = player.position.x + player.size.width;
	if (SCREEN_WIDTH <= rightEndX) rightEndX = rightEndX - SCREEN_WIDTH;

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
};

void GamePlayer::Draw() const {
	int anim = 0;
	if (state[COLLIDE] == 0) { // 飛行
		anim = abs(-2 + (flapCount / 3 % 4));
		if (flapCount == 0) anim += state[ANIM] / 25 % 3;
		anim = anim + 16;		
	}
	else if (speed[MOVE] == 0) { // 待機
		anim = frameCounter / 25 % 3;
	}
	else if (state[COLLIDE] == 1) { // 地面
		anim = state[ANIM] / 5 % 3;
		if ((inputX > -0.3 && 0.3 > inputX) || (speed[MOVE] < 0 && inputX >= 0.3) || (0 < speed[MOVE] && -0.3 >= inputX)) anim = 11; // スリップ
		else anim = anim + 8; // 歩行
	};

	// ワープ用にゲーム画面分の間隔をあけて3体描画する
	DrawRotaGraph2((int)player.position.x, (int)player.position.y, 32, 64 - (int)player.size.height, 1, 0, img_player[anim], TRUE, state[TURN]);
	DrawRotaGraph2((int)player.position.x - SCREEN_WIDTH, (int)player.position.y, 32, 64 - (int)player.size.height, 1, 0, img_player[anim], TRUE, state[TURN]);
	DrawRotaGraph2((int)player.position.x + SCREEN_WIDTH, (int)player.position.y, 32, 64 - (int)player.size.height, 1, 0, img_player[anim], TRUE, state[TURN]);
};