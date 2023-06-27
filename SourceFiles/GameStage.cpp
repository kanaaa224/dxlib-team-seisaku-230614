/********************************
* ゲームステージ処理
* 編集者：
********************************/
#include "main.h"

// プレイヤークラスのコンストラクタ
GameStage::GameStage() {
	// 初期化処理
	state = 0;

	// 画像読み込み
	if ((img_bg = LoadGraph("Resources/Images/Stage1.png")) == -1) throw "Resources/Images/Stage1.png";

	w = 30;
	h = 60;

	x = SCREEN_WIDTH / 2;
	y = 270;
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
	DrawExtendGraph(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, img_bg, TRUE);

	DrawBox(x, y, x + w, y + h, 0xffffff, FALSE);
};