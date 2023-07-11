/********************************
* ゲームステージ処理
* 編集者：
********************************/
#include "common.h"

// プレイヤークラスのコンストラクタ
GameStage::GameStage() {
	// 初期化処理

	// 画像読み込み
	img_bg = LoadGraph("Resources/Images/Stage_Sea01.png");
	img_bg1 = LoadGraph("Resources/Images/Stage_Footing01.png");

};

// プレイヤークラスのデストラクタ
GameStage::~GameStage() {
	// 終了処理
};

// プレイヤー更新処理
AbstractScene*GameStage::Update() {
	return this;
};

// プレイヤー描画
void GameStage::Draw() const {
	// 背景表示
	DrawExtendGraph(0, 450, 640, 480, img_bg, FALSE);
	DrawGraph(-50, 430, img_bg1, FALSE);
	DrawGraph(370, 430, img_bg1, FALSE);
	DrawGraph(180, 250, img_bg1, FALSE);

};