/********************************
* ゲームプレイヤー処理
* 編集者：島袋
********************************/
#include "main.h"

// プレイヤークラスのコンストラクタ
GamePlayer::GamePlayer() {
	// 初期化処理
	state = 0;

	player.width = 40;
	player.height = 50;

	// 画像読み込み
	if ((LoadDivGraph("Resources/Images/Player/Player_Animation.png", 30, 8, 4, 64, 64, img_player)) == -1) throw "ERROR : PLAYER IMG";

	// 画像読み込み
	if ((img_bg = LoadGraph("Resources/Images/kari.png")) == -1) throw "Resources/Images/kari.png";
};

// プレイヤークラスのデストラクタ
GamePlayer::~GamePlayer() {
	// 終了処理
};

// プレイヤー更新処理
void GamePlayer::Update() {

	// 飛んだらしばらく経つまでは飛べない
	if (fly_state == 1) {
		if ((frameCounter++) % 10 == 0) {
			fly_state = 0;
		};
	};
};

// プレイヤー描画
void GamePlayer::Draw() const {
	// 背景表示
	DrawExtendGraph(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, img_bg, TRUE);

	DrawGraph(player.position.x, player.position.y, img_player[0], TRUE);

	DrawBox(player.position.x + 12, player.position.y + 14, (player.position.x + 40) + 12, (player.position.y + 50) + 14, 0xffffff, FALSE);

	DrawFormatString(20, 100, 0xffffff, "Player X : %0.1f", player.position.x);
	DrawFormatString(20, 115, 0xffffff, "Player Y : %0.1f", player.position.y);
};

// プレイヤー移動
void GamePlayer::Control() {
	if (CheckHitKey(KEY_INPUT_A)) {
		player.position.x = player.position.x - 2;
	}
	else if (CheckHitKey(KEY_INPUT_D)) {
		player.position.x = player.position.x + 2;
	};

	if (CheckHitKey(KEY_INPUT_W)) {
		player.position.y = player.position.y - 2;
	}
	else if (CheckHitKey(KEY_INPUT_S)) {
		player.position.y = player.position.y + 2;
	};

	if (CheckHitKey(KEY_INPUT_SPACE) && (fly_state == 0)) {
		player.position.y = player.position.y - 30;
		fly_state = 1;
	};
};

void GamePlayer::Gravity() {
	if (SCREEN_HEIGHT > player.position.y) {
		player.position.y = player.position.y + 1;
	};
};