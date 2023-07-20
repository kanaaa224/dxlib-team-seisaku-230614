/********************************
* ゲームステージ処理
* 編集者：
********************************/
#include "main.h"

//GameStage::GameStage() {
//	// 初期化処理
//	bubble_width = 200;
//	frequency = 0;
//	bubble_count = 0;
//	frameCounter = 0;
//	bubble_anm = 0;
//
//	// 画像読み込み
//	img_sea = LoadGraph("Resources/Images/Stage/Stage_Sea01.png");
//	img_footing = LoadGraph("Resources/Images/Stage/Stage_Footing01.png");
//	LoadDivGraph("Resources/Images/Stage/Stage_CloudAnimation.png", 3, 3, 1, 128, 64, img_cloud);
//
//	//シャボン玉画像読込
//	LoadDivGraph("Resources/Images/Stage/Stage_BubbleAnimation.png", 4, 4, 1, 64 , 64, img_bubble);
//
//	//シャボン玉スコア画像　仮
//	GetScore_500 = LoadGraph("Resources/Images/Stage/GetScore_500.png");
//	
//
//	//
//	bubble_width = 200;
//	bubble_height = 400;
//};
//
//GameStage::~GameStage() {
//	// 終了処理
//};
//
//void GameStage::Update() {
//	
//	
//	float amplitude = 50.0f;
//	float frequency = 0.02;
//	
//	float bubble_x = 200;
//
//	bubble_x += amplitude * sin(frequency * bubble_count);
//		//amplitude波の大きさを決める　//frequency　1秒あたりに何回周期するかを決める
//		bubble_width = bubble_x;
//		bubble_count += 1;
//		bubble_height -=0.5;
//
//		frameCounter++;
//		if (frameCounter % 20 == 0) {
//			if (bubble_anm == 0) bubble_anm = 1;
//			else if (bubble_anm == 1) bubble_anm = 2;
//		};
//		if (frameCounter % 60  == 0) {
//			frameCounter = 0;
//			bubble_anm = 0;
//		};
//};
//	
//
//void GameStage::Draw() const {
//
//
//	DrawGraph(bubble_width, bubble_height, img_bubble[bubble_anm], TRUE);  // シャボン
//
//
//	// 仮 - 足場の当たり判定用ボックス
//	//DrawBox((int)block[0][0], (int)block[0][1], (int)block[0][2], (int)block[0][3], 0xffffff, FALSE); // 真ん中
//	//DrawBox((int)block[1][0], (int)block[1][1], (int)block[1][2], (int)block[1][3], 0xffffff, FALSE); // 左下
//	//DrawBox((int)block[2][0], (int)block[2][1], (int)block[2][2], (int)block[2][3], 0xffffff, FALSE); // 右下
//
//	DrawFormatString(100, 110, 0x00ffff, "%d", bubble_anm);
//	DrawFormatString(100, 120, 0x00ffff, "%d", frameCounter);
//};
//
//GameStageGimmick::GameStageGimmick()
//{
//}
//
//GameStageGimmick::~GameStageGimmick()
//{
//}
//
//void GameStageGimmick::bubble_Update()
//{
//}
//
//void GameStageGimmick::bubble_Draw() const
//{
//}
