/********************************
* ゲームステージ処理
* 編集者：
********************************/
#include "main.h"

GameStage::GameStage() {
	// 初期化処理
	
	// 画像読み込み
	img_sea = LoadGraph("Resources/Images/Stage/Stage_Sea01.png");
	img_footing = LoadGraph("Resources/Images/Stage/Stage_Footing01.png");
	LoadDivGraph("Resources/Images/Stage/Stage_CloudAnimation.png", 3, 3, 1, 128, 64, img_cloud);

	//シャボン玉画像読込
	LoadDivGraph("Resources/Images/Stage/Stage_BubbleAnimation.png", 4, 4, 1, 64 , 64, img_bubble);

	// 仮 - 足場の当たり判定用ボックス
	block[0][0] = 180; // 真ん中
	block[0][1] = 250;
	block[0][2] = 460;
	block[0][3] = 270;

	block[1][0] = 0;   // 左下
	block[1][1] = 430;
	block[1][2] = 230;
	block[1][3] = SCREEN_HEIGHT;

	block[2][0] = 370; // 右下
	block[2][1] = 430;
	block[2][2] = SCREEN_WIDTH;
	block[2][3] = SCREEN_HEIGHT;
};

GameStage::~GameStage() {
	// 終了処理
};

void GameStage::Update() {

	void HitStage();//ステージの当たり判定

};

void GameStage::Draw() const {
	DrawExtendGraph(0, 450, 640, 480, img_sea, FALSE); // 海

	// 足場
	//DrawGraph(-50, 430, img_bg1, FALSE);
	DrawGraph(180, 250, img_footing, TRUE); // 真ん中
	DrawGraph(-50, 430, img_footing, TRUE); // 左下
	DrawGraph(370, 430, img_footing, TRUE); // 右下

	DrawGraph(320, 80, img_cloud[0], TRUE);  // 雲

	DrawGraph(320, 300, img_bubble[0], TRUE);  // シャボン

	// 仮 - 足場の当たり判定用ボックス
	//DrawBox((int)block[0][0], (int)block[0][1], (int)block[0][2], (int)block[0][3], 0xffffff, FALSE); // 真ん中
	//DrawBox((int)block[1][0], (int)block[1][1], (int)block[1][2], (int)block[1][3], 0xffffff, FALSE); // 左下
	//DrawBox((int)block[2][0], (int)block[2][1], (int)block[2][2], (int)block[2][3], 0xffffff, FALSE); // 右下
};
