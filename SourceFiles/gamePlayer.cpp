/********************************
* ゲームプレイヤー処理
* 編集者：島袋
********************************/
#include "main.h"

// プレイヤークラスのコンストラクタ
GamePlayer::GamePlayer() {
	// 初期化処理
	state = 0;

	// 画像読み込み
	if ((img_bg = LoadGraph("Resources/Images/kari.png")) == -1) throw "Resources/Images/kari.png";

	w = 30;
	h = 60;

	x = SCREEN_WIDTH / 2;
	y = 270;
};

// プレイヤークラスのデストラクタ
GamePlayer::~GamePlayer() {
	// 終了処理
};

// プレイヤー更新処理
void GamePlayer::Update() {



};

// プレイヤー描画
void GamePlayer::Draw() const {
	// 背景表示
	DrawExtendGraph(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, img_bg, TRUE);

	DrawBox(x, y, x + w, y + h, 0xffffff, FALSE);
	DrawFormatString(20, 100, 0xffffff, "プレイヤークラス実行中！");
};