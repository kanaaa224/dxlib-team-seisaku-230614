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
	if ((LoadDivGraph("Resources/Images/Player/Player_Animation.png", 30, 8, 4, 64, 64, img_player)) == -1) throw "ERROR : PLAYER IMG";

	// 画像読み込み
	if ((img_bg = LoadGraph("Resources/Images/kari.png")) == -1) throw "Resources/Images/kari.png";

	w = 40;
	h = 50;

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

	DrawGraph(x, y, img_player[0], TRUE);
	DrawBox(x + 12, y + 14, (x + w) + 12, (y + h) + 14, 0xffffff, FALSE);
	DrawFormatString(20, 100, 0xffffff, "プレイヤークラス実行中！");
};

// プレイヤー
void GamePlayer::Control() {
	if (CheckHitKey(KEY_INPUT_A)) {
		x--;
	}
	else if (CheckHitKey(KEY_INPUT_D)) {
		x++;
	};

	if (CheckHitKey(KEY_INPUT_W)) {
		y--;
	}
	else if (CheckHitKey(KEY_INPUT_S)) {
		y++;
	};
};