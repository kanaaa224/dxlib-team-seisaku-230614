
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

	/* if (CheckHitKey(KEY_INPUT_B) && !position_flg) {でx取得*/




	if (playerCollide.ul.y >= 500 && bubble[count].flg == 0) {
		bubble[count].flg = 1;
		bubble[count].y = 480;
		bubble[count].spawnX = playerCollide.ul.x;
	}

	position = bubble[count].spawnX;



	// シャボン玉が上昇中の処理

	if (bubble[count].flg == 1) {
		if (bubble[count].y >= 0) {

			bubble_x += amplitude * sin(frequency * bubble_count) - 140;
			//amplitude波の大きさを決める　//frequency　1秒あたりに何回周期するかを決める
			bubble[count].x = bubble_x;
			bubble[count].x += position;
			bubble_count += 1;
			bubble[count].y -= 1;

			frameCounter++;

			if (frameCounter % 30 == 0) {
				bubble[count].anim++;
			};

			if (bubble[count].anim == 3) bubble[count].anim = 0;

		}

		else {
			bubble[count].flg = 0;
			bubble[count].y = 480;
		}

		/*if (bubble[count].y == -1) {
			bubble[count].flg = 0;
			bubble[count].y = 480;
		}*/

	}
	if (playerCollide.ul.y >= 500) {
		count++; // 次のシャボン玉へ
	}
	if (count >= 10) {
		count = 0; // シャボン玉が10個以上なら最初のシャボン玉に戻る
	}

};


void GameStageGimmick::BubbleDraw() const {

	// シャボン玉の描画
	for (int i = 0; i < 10; i++) {
		if (bubble[count].flg == 1) {
			DrawGraph(bubble[i].x, bubble[i].y, img_bubble[bubble[i].anim], TRUE);

		}
		DrawFormatString(100, 100, 0x00ffff, "%d", bubble[0].y);

		// 仮 - 足場の当たり判定用ボックス
		//DrawBox((int)block[0][0], (int)block[0][1], (int)block[0][2], (int)block[0][3], 0xffffff, FALSE); // 真ん中
		//DrawBox((int)block[1][0], (int)block[1][1], (int)block[1][2], (int)block[1][3], 0xffffff, FALSE); // 左下
		//DrawBox((int)block[2][0], (int)block[2][1], (int)block[2][2], (int)block[2][3], 0xffffff, FALSE); // 右下

	}
};


