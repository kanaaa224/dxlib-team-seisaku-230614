/********************************
* ゲームステージ処理
* 編集者：
********************************/
#include "main.h"

// ステージクラスのコンストラクタ
GameStage::GameStage() {
	// 初期化処理
	
	// 画像読み込み
	img_sea = LoadGraph("Resources/Images/Stage_Sea01.png");
	img_footing = LoadGraph("Resources/Images/Stage_Footing01.png");
	LoadDivGraph("Resources/Images/Stage_CloudAnimation.png", 3, 3, 1, 128, 64, img_cloud);
};

// ステージクラスのデストラクタ
GameStage::~GameStage() {
	// 終了処理
};

// ステージの更新
void GameStage::Update() {

	void HitStage();//ステージの当たり判定
};

// ステージ描画
void GameStage::Draw() const {
	// 海
	DrawExtendGraph(0, 450, 640, 480, img_sea, FALSE);

	//DrawGraph(-50, 430, img_bg1, FALSE);
	DrawGraph(180, 250, img_footing, FALSE); // 真ん中
	DrawGraph(-50, 430, img_footing, FALSE); // 左下
	DrawGraph(370, 430, img_footing, FALSE); // 右下

	DrawGraph(320, 80, img_cloud[0], TRUE);  // 雲の画像表示
};
