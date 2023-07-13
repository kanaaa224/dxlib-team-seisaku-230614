/********************************
* ゲームステージ処理
* 編集者：
********************************/
#include "common.h"

// ステージクラスのコンストラクタ
GameStage::GameStage() {
	// 初期化処理
	mx0 = StageX - 4;
	mx1 = StageX + 4;
	my0 = StageY - 4;
	my1 = StageY + 4;
	sx0 = playerX;
	sx1 = playerX + 60;
	sy0 = playerY;
	sy1 = playerY + 8;
	PlayerAngle = 0.624f;
	// 画像読み込み
	img_bg = LoadGraph("Resources/Images/Stage_Sea01.png");
	img_bg1 = LoadGraph("Resources/Images/Stage_Footing01.png");
};

// ステージクラスのデストラクタ
GameStage::~GameStage()
{
	// 終了処理
};

// ステージの更新
AbstractScene*GameStage::Update() 
{
	void HitStage();//ステージの当たり判定

	return this;
};

// ステージ描画
void GameStage::Draw() const
{
	// 背景表示
	DrawExtendGraph(0, 450, 640, 480, img_bg, FALSE);
	//DrawGraph(-50, 430, img_bg1, FALSE);
	DrawGraph(370, 430, img_bg1, FALSE);
	DrawGraph(180, 250, img_bg1, FALSE);
	DrawBox(0, 430, 230, 480, 0xff0000, FALSE);
	DrawBox(370, 430, 640, 480, 0xff0000, FALSE);
	DrawBox(180, 250, 460, 270, 0xff0000, FALSE);
};

//ステージの当たり判定
void GameStage::HitStage()
{
	//プレイヤーとステージの当たり判定
	if (sx0 <= mx1 && sx1 >= mx0 && sy0 <= my1 && sy1 >= my0) {
		if (StageFlg == 0) {
			PlayerAngle = (0.3f / 60) * (mx1 - sx0) + 0.6f;
			StageFlg = 1;
		}
	}
	else {
		if (StageFlg != 2)StageFlg = 0;
	}
}