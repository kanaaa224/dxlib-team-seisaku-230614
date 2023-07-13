/********************************
* ゲームステージ処理
* 編集者：
********************************/
#include "main.h"

// ステージクラスのコンストラクタ
GameStage::GameStage() {
	// 初期化処理
	
	// 画像読み込み
	img_bg = LoadGraph("Resources/Images/Stage_Sea01.png");
	img_bg1 = LoadGraph("Resources/Images/Stage_Footing01.png");
	LoadDivGraph("Resources/Images/Stage_CloudAnimation.png", 3, 3, 1, 128, 64, cloudimg);
};

// ステージクラスのデストラクタ
GameStage::~GameStage()
{
	// 終了処理
};

// ステージの更新
void GameStage::Update() 
{
	void HitStage();//ステージの当たり判定


};

// ステージ描画
void GameStage::Draw() const
{
	// 背景表示
	DrawExtendGraph(0, 450, 640, 480, img_bg, FALSE);
	//DrawGraph(-50, 430, img_bg1, FALSE);
	DrawGraph(370, 430, img_bg1, FALSE);
	DrawGraph(180, 250, img_bg1, FALSE);

	DrawGraph(320, 80, cloudimg[0], TRUE);//雲の画像表示

	DrawGraph(-50, 430, img_bg1, FALSE);
	DrawBox(0, 430, 230, 480, 0xff0000, FALSE);
	DrawBox(370, 430, 640, 480, 0xff0000, FALSE);
	DrawBox(180, 250, 460, 270, 0xff0000, FALSE);
};
