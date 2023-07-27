/********************************
* ゲームステージ処理
* 編集者：
********************************/
#include "main.h"

//int GameStage::Stage=3;    //0が最初のステージとなる

GameStage::GameStage() {
	img_sea = LoadGraph("Resources/Images/Stage/Stage_Sea01.png");

	img_footing[0] = LoadGraph("Resources/Images/Stage/Stage_Footing01.png"); // 1
	img_footing[1] = LoadGraph("Resources/Images/Stage/Stage_Footing02.png"); // 2
	img_footing[2] = LoadGraph("Resources/Images/Stage/Stage_Footing03.png"); // 3
	img_footing[3] = LoadGraph("Resources/Images/Stage/Stage_Footing04.png"); // 4
	img_footing[4] = LoadGraph("Resources/Images/Stage/Stage_Footing05.png"); // 5
	img_footing[5] = LoadGraph("Resources/Images/Stage/Stage_Footing06.png"); // 6
	img_footing[6] = LoadGraph("Resources/Images/Stage/Stage_Footing07.png"); // 7
	img_footing[7] = LoadGraph("Resources/Images/Stage/Stage_Footing08.png"); // 8

	img_land[0] = LoadGraph("Resources/Images/Stage/Stage_Land_Left02.png");
	img_land[1] = LoadGraph("Resources/Images/Stage/Stage_Land_Right02.png");

	LoadDivGraph("Resources/Images/Stage/Stage_CloudAnimation.png", 3, 3, 1, 128, 64, img_cloud);       // 雲画像の分割読込
	//LoadDivGraph("Resources/Images/Stage/Stage_ThunderEffectAnimation.png", 3, 3, 1, 128, 64, img_ect); // 雷画像の分割読込

	// 仮 - ステージ１の足場の当たり判定用ボックス
	collisionData[0].footingMax = 3; // 足場最大数

	collisionData[0].footingBlock[0][0] = 180;    // 真ん中
	collisionData[0].footingBlock[0][1] = 250;
	collisionData[0].footingBlock[0][2] = 460;
	collisionData[0].footingBlock[0][3] = 270;

	collisionData[0].footingBlock[1][0] = 0 - 20; // 左下
	collisionData[0].footingBlock[1][1] = 430;
	collisionData[0].footingBlock[1][2] = 230;
	collisionData[0].footingBlock[1][3] = SCREEN_HEIGHT;

	collisionData[0].footingBlock[2][0] = 370;    // 右下
	collisionData[0].footingBlock[2][1] = 430;
	collisionData[0].footingBlock[2][2] = SCREEN_WIDTH + 20;
	collisionData[0].footingBlock[2][3] = SCREEN_HEIGHT;

	//仮ステージ２の足場の当たり判定
	collisionData[1].footingMax = 5; // 足場最大数

	collisionData[1].footingBlock[0][0] = 180;    // 真ん中
	collisionData[1].footingBlock[0][1] = 280;
	collisionData[1].footingBlock[0][2] = 460;
	collisionData[1].footingBlock[0][3] = 300;

	collisionData[1].footingBlock[1][0] = 0 - 20; // 左下
	collisionData[1].footingBlock[1][1] = 430;
	collisionData[1].footingBlock[1][2] = 230;
	collisionData[1].footingBlock[1][3] = SCREEN_HEIGHT;

	collisionData[1].footingBlock[2][0] = 370;    // 右下
	collisionData[1].footingBlock[2][1] = 430;
	collisionData[1].footingBlock[2][2] = SCREEN_WIDTH + 20;
	collisionData[1].footingBlock[2][3] = SCREEN_HEIGHT;

	collisionData[1].footingBlock[3][0] = 80;    // 左上
	collisionData[1].footingBlock[3][1] = 130;
	collisionData[1].footingBlock[3][2] = 200;
	collisionData[1].footingBlock[3][3] = 150;

	collisionData[1].footingBlock[4][0] = 450;    // 右上
	collisionData[1].footingBlock[4][1] = 130;
	collisionData[1].footingBlock[4][2] = 570;
	collisionData[1].footingBlock[4][3] = 150;

	//仮ステージ３の足場の当たり判定
	collisionData[2].footingMax = 7; // 足場最大数

	collisionData[2].footingBlock[0][0] = 180;    // 左上の小さい足場
	collisionData[2].footingBlock[0][1] = 280;
	collisionData[2].footingBlock[0][2] = 460;
	collisionData[2].footingBlock[0][3] = 300;

	collisionData[2].footingBlock[1][0] = 0 - 20; // 左下
	collisionData[2].footingBlock[1][1] = 430;
	collisionData[2].footingBlock[1][2] = 230;
	collisionData[2].footingBlock[1][3] = SCREEN_HEIGHT;

	collisionData[2].footingBlock[2][0] = 370;    // 右下
	collisionData[2].footingBlock[2][1] = 430;
	collisionData[2].footingBlock[2][2] = SCREEN_WIDTH + 20;
	collisionData[2].footingBlock[2][3] = SCREEN_HEIGHT;

	collisionData[2].footingBlock[3][0] = 80;    //右のT字の足場
	collisionData[2].footingBlock[3][1] = 130;
	collisionData[2].footingBlock[3][2] = 200;
	collisionData[2].footingBlock[3][3] = 150;

	collisionData[2].footingBlock[4][0] = 450;    //真ん中のT字の足場
	collisionData[2].footingBlock[4][1] = 130;
	collisionData[2].footingBlock[4][2] = 570;
	collisionData[2].footingBlock[4][3] = 150;

	collisionData[2].footingBlock[5][0] = 450;    //左のT字の足場
	collisionData[2].footingBlock[5][1] = 130;
	collisionData[2].footingBlock[5][2] = 570;
	collisionData[2].footingBlock[5][3] = 150;

	collisionData[2].footingBlock[6][0] = 270;	//海の上の足場    
	collisionData[2].footingBlock[6][1] = 310;
	collisionData[2].footingBlock[6][2] = 350;
	collisionData[2].footingBlock[6][3] = 350;
};

GameStage::~GameStage() {

};

void GameStage::Update() {
	
};

void GameStage::Draw() const {
	DrawExtendGraph(0, 450, 640, 480, img_sea, FALSE); // 海

	// ステージ１の表示
	if (nowStage == 0) {
		DrawGraph(180, 250, img_footing[0], TRUE); // 真ん中
		DrawGraph(-50, 430, img_footing[0], TRUE); // 左下
		DrawGraph(370, 430, img_footing[0], TRUE); // 右下

		DrawGraph(320, 80, img_cloud[0], TRUE);  // 雲
	}
	// ステージ２の表示
	if (nowStage == 1) {
		DrawGraph(180, 280, img_footing[0], TRUE); // 真ん中
		DrawGraph(-50, 430, img_footing[0], TRUE); // 左下
		DrawGraph(370, 430, img_footing[0], TRUE); // 右下
		DrawGraph(80, 130, img_footing[1], TRUE);  //左上
		DrawGraph(450, 130, img_footing[1], TRUE); //右上

		DrawGraph(50, 180, img_cloud[0], TRUE);  // 雲
		DrawGraph(480,180, img_cloud[0], TRUE);  // 雲
	}
	// ステージ３の表示
	else if (nowStage == 2) {
		DrawGraph(-70, 430, img_footing[0], TRUE); // 左下
		DrawGraph(400, 430, img_footing[0], TRUE); // 右下
		DrawGraph(470, 100, img_footing[3], TRUE); // 右のT字の足場
		DrawBox(470, 100, 530, 170, 0xffffff, FALSE);
		DrawGraph(330, 180, img_footing[3], TRUE); // 真ん中のT字の足場
		DrawBox(330, 180, 390, 250, 0xffffff, FALSE);
		DrawGraph(180, 240, img_footing[3], TRUE); // 左のT字の足場
		DrawBox(180, 240, 240, 310, 0xffffff, FALSE);
		DrawGraph(220, 130, img_footing[4], TRUE); // 左上の小さい足場
		DrawBox(220, 130, 265, 150, 0xffffff, FALSE);
		DrawGraph(270, 330, img_footing[2], TRUE); // 海の上の足場
		DrawBox(270, 330, 350, 350, 0xffffff, FALSE);

		DrawGraph(320, 80, img_cloud[0], TRUE);  // 雲
	}
	// ステージ４の表示
	else if (nowStage == 3) {
		DrawGraph(0, 430, img_land[0], TRUE); // 左下
		DrawGraph(480, 430, img_land[1], TRUE); // 右下

		DrawGraph(250, 130, img_footing[5], TRUE);
		DrawGraph(100, 230, img_footing[5], TRUE);
		DrawGraph(430, 200, img_footing[5], TRUE);
		DrawGraph(200, 300, img_footing[5], TRUE);
		DrawGraph(350, 350, img_footing[5], TRUE);
	}
	// ステージ５の表示
	else if (nowStage == 4) {
		DrawGraph(0, 430, img_land[0], TRUE); // 左下
		DrawGraph(480, 430, img_land[1], TRUE); // 右下

		DrawGraph(180, 120, img_footing[5], TRUE);
		DrawGraph(190, 330, img_footing[5], TRUE);
		DrawGraph(350, 330, img_footing[5], TRUE);
		DrawGraph(130, 230, img_footing[6], TRUE);
		DrawGraph(250, 180, img_footing[6], TRUE);
		DrawGraph(480, 180, img_footing[6], TRUE);
	};


	// 仮 - 足場の当たり判定用ボックス
	//DrawBox((int)block[0][0], (int)block[0][1], (int)block[0][2], (int)block[0][3], 0xffffff, FALSE); // 真ん中
	//DrawBox((int)block[1][0], (int)block[1][1], (int)block[1][2], (int)block[1][3], 0xffffff, FALSE); // 左下
	//DrawBox((int)block[2][0], (int)block[2][1], (int)block[2][2], (int)block[2][3], 0xffffff, FALSE); // 右下
};
