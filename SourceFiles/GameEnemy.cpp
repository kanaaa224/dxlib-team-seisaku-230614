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
	
};

void GameEnemy::Update() {
	frameCounter++;

}

void GameEnemy::Draw() const{
	int anim = 0;

	//if (speed[MOVE] == 0) { // 待機
	//	anim = frameCounter / 25 % 3; framecountはカウントし続けていてずっと１，２，３がAnimに入ってる
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