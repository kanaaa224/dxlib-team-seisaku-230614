/********************************
* ゲームステージ処理
* 編集者：
********************************/
#include "main.h"


GameStageGimmick::GameStageGimmick(int* img_bubble)
{

	// 画像ポインタを受け取る処理
	for (int i = 0; i < 3; i++) {
		img_bubble[i] = img_bubble[i];
	}

	// 初期化処理
	bubble_width = 200;
	frequency = 0;
	bubble_count = 0;
	frameCounter = 0;
	bubble_anm = 0;


	// 画像読み込み//シャボン玉画像読込
	LoadDivGraph("Resources/Images/Stage/Stage_BubbleAnimation.png", 4, 4, 1, 64, 64, img_bubble);
	

	//
	//bubble_width = 200;
	//bubble_height = 400;
}

GameStageGimmick::~GameStageGimmick()
{
	// 終了処理
}

void GameStageGimmick::bubble_Update()
{
	float amplitude = 50.0f;
	float frequency = 0.02;

	float bubble_x = 200;

	bubble_x += amplitude * sin(frequency * bubble_count);
	//amplitude波の大きさを決める　//frequency　1秒あたりに何回周期するかを決める
	bubble_width = bubble_x;
	bubble_count += 1;
	bubble_height -= 0.5;

	frameCounter++;
	if (frameCounter % 20 == 0) {
		if (bubble_anm == 0) bubble_anm = 1;
		else if (bubble_anm == 1) bubble_anm = 2;
	};
	if (frameCounter % 60 == 0) {
		frameCounter = 0;
		bubble_anm = 0;
	};
}

void GameStageGimmick::bubble_Draw() const
{
	DrawFormatString(100, 110, 0x00ffff, "%d", bubble_anm);
	DrawFormatString(100, 120, 0x00ffff, "%d", frameCounter);

	DrawGraph(bubble_width, bubble_height, img_bubble[bubble_anm], TRUE);  // シャボン
}
