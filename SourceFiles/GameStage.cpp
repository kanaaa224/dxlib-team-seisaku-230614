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
};

// プレイヤークラスのデストラクタ
GameStage::~GameStage() {
	// 終了処理
};

// プレイヤー更新処理
void GameStage::Update() {

};

// プレイヤー描画
void GameStage::Draw() const {
	// 背景表示
	//DrawGraph(0, 0, img_bg, TRUE);
};