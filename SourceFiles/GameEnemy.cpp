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
	GamePlayer player;
	frameCounter++;

	if (frameCounter % 3 == 0) anim++;
	if (anim >= 12) anim = 8;

	Position playerposition = player.GetPosition();

	if (playerposition.x <= enemy.position.x)
	{
		enemy.position.x--;
	}
	else if (playerposition.x >= enemy.position.x)
	{
		enemy.position.x++;
	}
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