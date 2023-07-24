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

	//シャボン玉スコア画像　仮
	//GetScore_500 = LoadGraph("Resources/Images/Stage/GetScore_500.png");
};

GameStageGimmick::~GameStageGimmick() {

};

void GameStageGimmick::BubbleUpdate() {
	
	float amplitude = 50.0f;
	float frequency = 0.02;
	
	float bubble_x = 0;

	if (CheckHitKey(KEY_INPUT_B)) {
		
		bubble_x += amplitude * sin(frequency * bubble_count);
		//amplitude波の大きさを決める　//frequency　1秒あたりに何回周期するかを決める
		bubble_width = bubble_x;
		bubble_count += 1;
		bubble_height -= 0.5;

		frameCounter++;
		if (frameCounter % 20 == 0) {
			if (bubble_anim == 0) bubble_anim = 1;
			else if (bubble_anim == 1) bubble_anim = 2;
		};
		if (frameCounter % 60 == 0) {
			frameCounter = 0;
			bubble_anim = 0;
		};
	}
};
	

void GameStageGimmick::BubbleDraw() const {

	DrawGraph(bubble_width, bubble_height, img_bubble[bubble_anim], TRUE);  // シャボン

	// 仮 - 足場の当たり判定用ボックス
	//DrawBox((int)block[0][0], (int)block[0][1], (int)block[0][2], (int)block[0][3], 0xffffff, FALSE); // 真ん中
	//DrawBox((int)block[1][0], (int)block[1][1], (int)block[1][2], (int)block[1][3], 0xffffff, FALSE); // 左下
	//DrawBox((int)block[2][0], (int)block[2][1], (int)block[2][2], (int)block[2][3], 0xffffff, FALSE); // 右下

	DrawFormatString(100, 110, 0x00ffff, "%d", bubble_anim);
	DrawFormatString(100, 120, 0x00ffff, "%d", frameCounter);
};
