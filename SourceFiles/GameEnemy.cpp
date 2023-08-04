/********************************
* ゲームエネミー処理
* 編集者：
********************************/
#include "main.h"

GameEnemy::GameEnemy() {
	Init();
	LoadDivGraph("Resources/Images/Enemy/Enemy_R_Animation.png", 18, 6, 3, 64, 64, r_enemy);
	LoadDivGraph("Resources/Images/Enemy/Enemy_G_Animation.png", 18, 6, 3, 64, 64, g_enemy);
	LoadDivGraph("Resources/Images/Enemy/Enemy_P_Animation.png", 18, 6, 3, 64, 64, p_enemy);

	isChasingPlayer = false;
	nextStateChange = rand() % 300 + 180;
	currentStateDuration = 0;

	anim = 8;
};

GameEnemy::~GameEnemy() {
	for (int i = 0; i < 18; i++) {
		DeleteGraph(r_enemy[i]);
		DeleteGraph(g_enemy[i]);
		DeleteGraph(p_enemy[i]);
	}
}

void GameEnemy::Init() {

	enemy.hp = 1;
	enemy.position.x = 50 + 15;
	enemy.position.y = 405 - 200;
	enemy.size.width = 15;
	enemy.size.height = 25;

	
};

void GameEnemy::Update() {
	
	frameCounter++;

	if (frameCounter % 3 == 0) anim++;
	if (anim >= 12) anim = 8;

	XDistance = playerCollide.ul.x - enemy.position.x;
	YDistance = playerCollide.ul.y - enemy.position.y;

	/*float Distance = sqrt(XDistance * XDistance + YDistance * YDistance);
	float Angle = atan2f(XDistance, YDistance);
	float UpperAngle = M_PI / 6.0f;*/

	const float escapeThreshold = 50.0f;
	bool isPlayerneaby = (fabs(XDistance) < escapeThreshold) && (YDistance < 0) && (fabs(YDistance) < escapeThreshold);

	if (isPlayerneaby) {
		RunAwayfromPlayer();
	}
	else {
		ChacePlayer();
	}

	if (enemy.position.x <= 0) enemy.position.x = SCREEN_WIDTH - 1;      // 画面左端時
	else if (SCREEN_WIDTH <= enemy.position.x) enemy.position.x = 0 + 1; // 画面右端時
}

void GameEnemy::Draw() const{
	//int anim = 0;

	////anim = frameCounter / 7 % 5;

	////if (speed[MOVE] == 0) { // 待機 8~12
	//anim += frameCounter / 25 % 2;
	////anim +=  14;		
	////}  

	DrawRotaGraph2((int)enemy.position.x, (int)enemy.position.y, 32, 64 - (int)enemy.size.height, 1.0f, 0, r_enemy[anim], TRUE);
	DrawRotaGraph2((int)enemy.position.x - SCREEN_WIDTH, (int)enemy.position.y, 32, 64 - (int)enemy.size.height, 1.0f, 0, r_enemy[anim], TRUE);
	DrawRotaGraph2((int)enemy.position.x + SCREEN_WIDTH, (int)enemy.position.y, 32, 64 - (int)enemy.size.height, 1.0f, 0, r_enemy[anim], TRUE);

	DrawRotaGraph2((int)enemy.position.x + 30, (int)enemy.position.y, 32, 64 - (int)enemy.size.height, 1.0f, 0, g_enemy[anim], TRUE);
	DrawRotaGraph2((int)enemy.position.x - SCREEN_WIDTH, (int)enemy.position.y, 32, 64 - (int)enemy.size.height, 1.0f, 0, g_enemy[anim], TRUE);
	DrawRotaGraph2((int)enemy.position.x + SCREEN_WIDTH, (int)enemy.position.y, 32, 64 - (int)enemy.size.height, 1.0f, 0, g_enemy[anim], TRUE);

	DrawRotaGraph2((int)enemy.position.x + 60, (int)enemy.position.y, 32, 64 - (int)enemy.size.height, 1.0f, 0, p_enemy[anim], TRUE);
	DrawRotaGraph2((int)enemy.position.x - SCREEN_WIDTH, (int)enemy.position.y, 32, 64 - (int)enemy.size.height, 1.0f, 0, p_enemy[anim], TRUE);
	DrawRotaGraph2((int)enemy.position.x + SCREEN_WIDTH, (int)enemy.position.y, 32, 64 - (int)enemy.size.height, 1.0f, 0, p_enemy[anim], TRUE);
}
void GameEnemy::ChacePlayer() {
	const float ChaseSpeedMax = 0.8f;

	float ChaseSpeedX = (enemy.position.x - playerCollide.ul.x) * 0.1f;
	moveSpeed = moveSpeed * inertiaCoefficient + ChaseSpeedX * (1.0f - inertiaCoefficient);

	float ChaseSpeedY = (enemy.position.y - playerCollide.ul.y) * 0.1f;
	moveSpeed = moveSpeed * inertiaCoefficient + ChaseSpeedY * (1.0f - inertiaCoefficient);

	ChaseSpeedX = ChaseSpeedX;
	ChaseSpeedY = ChaseSpeedY;

	if (lagCounter <= lagTime) {
		float Progress = static_cast<float>(lagCounter) / lagTime;
		moveSpeedX = moveSpeedX * inertiaCoefficient + ChaseSpeedX * (1.0f - inertiaCoefficient);
		moveSpeedY = moveSpeedY * inertiaCoefficient + ChaseSpeedY * (1.0f - inertiaCoefficient);
		lagCounter++;
	}
	else {
		moveSpeedX = -ChaseSpeedX;
		moveSpeedY = -ChaseSpeedY;
	}

	//if (moveSpeed > moveSpeedMax) {
	//	moveSpeed = moveSpeedMax;
	//}
	//else if (moveSpeed < -moveSpeedMax) {
	//	moveSpeed = -moveSpeedMax;
	//}

	//if (moveSpeed > moveSpeedMax) {
	//	moveSpeed = moveSpeedMax;
	//}
	//else if (moveSpeed < moveSpeedMax) {
	//	moveSpeed = -moveSpeedMax;
	//}

	//enemy.position.x = playerCollide.ul.x;
	//enemy.position.y = playerCollide.ul.y;

	float currentSpeed = sqrt(moveSpeedX * moveSpeedX + moveSpeedY * moveSpeedY);
	if (currentSpeed > ChaseSpeedMax) {
		float ratio = ChaseSpeedMax / currentSpeed;
		moveSpeedX *= ratio;
		moveSpeedY *= ratio;
	}

	enemy.position.x += moveSpeedX;
	enemy.position.y += moveSpeedY;
}
void GameEnemy::RunAwayfromPlayer()
{
	const float RunawaySpeedMax = 0.5f;

	float EscapeSpeedX = (enemy.position.x - playerCollide.ul.x) * 0.1f;
	moveSpeed = moveSpeed * inertiaCoefficient + EscapeSpeedX * (1.0f - inertiaCoefficient);

	float EscapeSpeedY = (enemy.position.y - playerCollide.ul.y) * 0.1f;
	moveSpeed = moveSpeed * inertiaCoefficient + EscapeSpeedY * (1.0f - inertiaCoefficient);

	EscapeSpeedX = EscapeSpeedX;
	EscapeSpeedY = EscapeSpeedY;

	if (lagCounter <= lagTime) {
		float Progress = static_cast<float>(lagCounter) / lagTime;
		moveSpeedX = moveSpeedX * inertiaCoefficient + EscapeSpeedX * (1.0f - inertiaCoefficient);
		moveSpeedY = moveSpeedY * inertiaCoefficient + EscapeSpeedY * (1.0f - inertiaCoefficient);
		lagCounter++;
	}
	else {
		moveSpeedX = EscapeSpeedX;
		moveSpeedY = EscapeSpeedY;
	}

	//if (moveSpeed > moveSpeedMax) {
	//	moveSpeed = moveSpeedMax;
	//}
	//else if (moveSpeed < -moveSpeedMax) {
	//	moveSpeed = -moveSpeedMax;
	//}

	//if (moveSpeed > moveSpeedMax) {
	//	moveSpeed = moveSpeedMax;
	//}
	//else if (moveSpeed < moveSpeedMax) {
	//	moveSpeed = -moveSpeedMax;
	//}

	//enemy.position.x = playerCollide.ul.x;
	//enemy.position.y = playerCollide.ul.y;

	float currentSpeed = sqrt(moveSpeedX * moveSpeedX + moveSpeedY * moveSpeedY);
	if (currentSpeed > RunawaySpeedMax) {
		float ratio = RunawaySpeedMax / currentSpeed;
		moveSpeedX *= ratio;
		moveSpeedY *= ratio;
	}

	enemy.position.x += moveSpeedX;
	enemy.position.y += moveSpeedY;
}