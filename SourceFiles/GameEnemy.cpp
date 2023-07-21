/********************************
* ゲームステージ処理
* 編集者：
********************************/
#include "main.h"
#include "GameEnemy.h"

GameEnemy::GameEnemy() {
	Init();
	LoadDivGraph("Resources/Images/Enemy/Enemy_R_Animation.png", 18, 6, 3, 64, 64, r_enemy);
	LoadDivGraph("Resources/Images/Enemy/Enemy_G_Animation.png", 18, 6, 3, 64, 64, g_enemy);
	LoadDivGraph("Resources/Images/Enemy/Enemy_P_Animation.png", 18, 6, 3, 64, 64, p_enemy);
};

GameEnemy::~GameEnemy() {
	for (int i = 0; i < 30; i++) {
		DeleteGraph(r_enemy[i]);
	}
}

void GameEnemy::Init() {

	enemy.hp = 1;
	enemy.position.x = FIRST_POSITION_X + 15;
	enemy.position.y = FIRST_POSITION_Y - 200;
	enemy.size.width = 15;
	enemy.size.height = 25;

	flapCount = 0;
	flightMove = 0;
	state[COLLIDE] = 0;
	state[TURN] = 1;
	state[ANIM] = 0;
	state[BLINK] = 1;
	speed[MOVE] = 0.0f;
	speed[FALL] = 1.0f;

	leftEndX = enemy.position.x - enemy.size.width;
	rightEndX = enemy.position.x + enemy.size.width;
};

void GameEnemy::Update() {
	frameCounter++;

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
	enemy.position.y += speed[FALL];
	if (--flapCount < 0) flapCount = 0;

	//////////////////////////////////////////////////////////////////////
	// 画面左右端のワープ処理
	//////////////////////////////////////////////////////////////////////

	if (enemy.position.x <= 0) enemy.position.x = SCREEN_WIDTH - 1;      // 画面左端時
	else if (SCREEN_WIDTH <= enemy.position.x) enemy.position.x = 0 + 1; // 画面右端時
	leftEndX = enemy.position.x - enemy.size.width;
	if (leftEndX <= 0) leftEndX = SCREEN_WIDTH + leftEndX;
	rightEndX = enemy.position.x +enemy.size.width;
	if (SCREEN_WIDTH <= rightEndX) rightEndX = rightEndX - SCREEN_WIDTH;

	//////////////////////////////////////////////////////////////////////
	// 壁の判定と跳ね返り処理
	//////////////////////////////////////////////////////////////////////

	bool wallHit = false;
	if (enemy.state == 3) {
		//player.position.x--;
		enemy.position.x = collideData.ul.x - enemy.size.width - 1;

		wallHit = true;
	};
	if (enemy.state == 4) {
		//player.position.x++;
		enemy.position.x = collideData.lr.x + enemy.size.width + 1;

		wallHit = true;
	};
	if (wallHit) speed[MOVE] *= -0.9f;
}

void GameEnemy::Draw() const{
	int anim = 0;

	//if (speed[MOVE] == 0) { // 待機
	//	anim = frameCounter / 25 % 3;
	//}   

	DrawRotaGraph2((int)enemy.position.x, (int)enemy.position.y, 32, 64 - (int)enemy.size.height, 1.0f, 0, r_enemy[anim], TRUE, state[TURN]);
	DrawRotaGraph2((int)enemy.position.x - SCREEN_WIDTH, (int)enemy.position.y, 32, 64 - (int)enemy.size.height, 1.0f, 0, r_enemy[anim], TRUE, state[TURN]);
	DrawRotaGraph2((int)enemy.position.x + SCREEN_WIDTH, (int)enemy.position.y, 32, 64 - (int)enemy.size.height, 1.0f, 0, r_enemy[anim], TRUE, state[TURN]);

	DrawRotaGraph2((int)enemy.position.x, (int)enemy.position.y, 32, 64 - (int)enemy.size.height, 1.0f, 0, r_enemy[anim], TRUE, state[TURN]);
	DrawRotaGraph2((int)enemy.position.x - SCREEN_WIDTH, (int)enemy.position.y, 32, 64 - (int)enemy.size.height, 1.0f, 0, g_enemy[anim], TRUE, state[TURN]);
	DrawRotaGraph2((int)enemy.position.x + SCREEN_WIDTH, (int)enemy.position.y, 32, 64 - (int)enemy.size.height, 1.0f, 0, g_enemy[anim], TRUE, state[TURN]);

	DrawRotaGraph2((int)enemy.position.x, (int)enemy.position.y, 32, 64 - (int)enemy.size.height, 1.0f, 0, r_enemy[anim], TRUE, state[TURN]);
	DrawRotaGraph2((int)enemy.position.x - SCREEN_WIDTH, (int)enemy.position.y, 32, 64 - (int)enemy.size.height, 1.0f, 0, p_enemy[anim], TRUE, state[TURN]);
	DrawRotaGraph2((int)enemy.position.x + SCREEN_WIDTH, (int)enemy.position.y, 32, 64 - (int)enemy.size.height, 1.0f, 0, p_enemy[anim], TRUE, state[TURN]);

}