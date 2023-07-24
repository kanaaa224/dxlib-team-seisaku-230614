/********************************
* ゲームステージギミック処理
* 編集者：
********************************/
#include "main.h"

GameStageGimmick::GameStageGimmick() {
	// シャボン玉画像読込
	LoadDivGraph("Resources/Images/Stage/Stage_BubbleAnimation.png", 4, 4, 1, 64, 64, img_bubble);

	frequency = 0;
	bubble_count = 0;
	frameCounter = 0;
	bubble_anim = 0;

	bubble_height = 400;

	bubble_flg = 0;

	//シャボン玉スコア画像　仮
	//GetScore_500 = LoadGraph("Resources/Images/Stage/GetScore_500.png");
};

GameStageGimmick::~GameStageGimmick() {

};

void GameStageGimmick::BubbleUpdate() {
	
	float amplitude = 50.0f;
	float frequency = 0.02;
	

	float bubble_x = 100;
	

	// if (CheckHitKey(KEY_INPUT_B) && !position_flg) {でx取得

	
	if (CheckHitKey(KEY_INPUT_B) && !position_flg && bubble_flg == 0) {
		position_flg = true; // フラグを立てる
		position = GetRand(400);
	}
	
	// フラグが立っていない
	if (!CheckHitKey(KEY_INPUT_B)) {
		position_flg = false;
	}

	if (CheckHitKey(KEY_INPUT_B)) {
		bubble_flg = 1;
		
	}
	if (bubble_flg == 1) {


		bubble_x += amplitude * sin(frequency * bubble_count);
		//amplitude波の大きさを決める　//frequency　1秒あたりに何回周期するかを決める
		bubble_width = bubble_x;
		bubble_width += position;
		bubble_count += 1;
		bubble_height -= 1;

		frameCounter++;

		if (frameCounter % 30 == 0) {
			 bubble_anim++;
		};

		if (bubble_anim == 3) bubble_anim = 0;

		if (bubble_height == 100) bubble_anim = 3;
	}
	if (bubble_height == -10) {
		bubble_flg = 0;
		bubble_height = 480;
	}


};
	

void GameStageGimmick::BubbleDraw() const {

	DrawGraph(bubble_width, bubble_height, img_bubble[bubble_anim], TRUE);  // シャボン

	// 仮 - 足場の当たり判定用ボックス
	//DrawBox((int)block[0][0], (int)block[0][1], (int)block[0][2], (int)block[0][3], 0xffffff, FALSE); // 真ん中
	//DrawBox((int)block[1][0], (int)block[1][1], (int)block[1][2], (int)block[1][3], 0xffffff, FALSE); // 左下
	//DrawBox((int)block[2][0], (int)block[2][1], (int)block[2][2], (int)block[2][3], 0xffffff, FALSE); // 右下

	DrawFormatString(100, 110, 0x00ffff, " bubble_anim %d", bubble_anim);
	DrawFormatString(100, 160, 0x00ffff, "bubble_height %d", bubble_height);

};
