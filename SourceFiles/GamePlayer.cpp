/********************************
* ゲームプレイヤー処理
* 編集者：島袋
********************************/
#include "main.h"

// プレイヤークラスのコンストラクタ
GamePlayer::GamePlayer() {
	// 初期化処理
	Init();

	// 画像読み込み
	if ((LoadDivGraph("Resources/Images/Player/Player_Animation.png", 30, 8, 4, 64, 64, img_player)) == -1) throw "ERROR : PLAYER IMG";

	// 仮
	if ((img_bg = LoadGraph("Resources/Images/kari.png")) == -1) throw "Resources/Images/kari.png";

	debug[0] = 1;
};

// プレイヤークラスのデストラクタ
GamePlayer::~GamePlayer() {
	// 終了処理
};

// プレイヤーの初期化
void GamePlayer::Init() {
	playerImg_state = 0;

	player.state = 0;
	player.hp = 0;
	player.position.x = 50;
	player.position.y = 380;
	player.size.width = 40;
	player.size.height = 50;
};

// プレイヤー更新処理
void GamePlayer::Update() {

	// 5m（300s）でカウントリセット
	if ((frameCounter++) >= 18000) {
		frameCounter = 1;
	};

	if (!Control()) {
		if (player.state >= 2) {
			if (player.state <= 3) {
				playerImg_state = 11;
			};
		}
		if(player.state > 1) {
			player.state = player.state - 2;
		};
	};

	//Gravity();
	Animation();

	// ステージ下の海に落ちればリスポーン地点へ
	if (SCREEN_HEIGHT <= player.position.y) {
		Init();
	};

	// ステージ横の外に出ると反対側へ
	if (SCREEN_WIDTH < player.position.x) {
		player.position.x = 0 - player.size.width;
	}
	else if (player.position.x < 0 - player.size.width) {
		player.position.x = SCREEN_WIDTH;
	}

	// 飛んだらしばらく経つまでは飛べない
	if (fly_state == 1) {
		player.position.y = player.position.y - 2;
		if (frameCounter % 30 == 0) {
			
			fly_state = 0;
		};
	};

	if (CheckHitKey(KEY_INPUT_UP)) {
		debug[0]++;
	}
	else if (CheckHitKey(KEY_INPUT_DOWN)) {
		if (debug[0] > 1) {
			debug[0]--;
		};
	};
};

// プレイヤー描画
void GamePlayer::Draw() const {
	// 仮 - 背景表示
	//DrawExtendGraph(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, img_bg, TRUE);

	// プレイヤー画像表示
	if (player.state % 2 == 0) {
		DrawRotaGraph((player.position.x + (player.size.width / 2)), (player.position.y - 8) + (player.size.height / 2), 1.0f, 0, img_player[playerImg_state], TRUE, FALSE);
	}
	else if (player.state % 2 == 1) {
		DrawRotaGraph((player.position.x + (player.size.width / 2)), (player.position.y - 8) + (player.size.height / 2), 1.0f, 0, img_player[playerImg_state], TRUE, TRUE);
	};
	//DrawGraph(player.position.x - playerImg_padding.width, player.position.y - playerImg_padding.height, img_player[playerImg_state], TRUE);

	// 仮
	DrawBox(player.position.x, player.position.y, (player.position.x + player.size.width), (player.position.y + player.size.height), 0xffffff, FALSE);
	//DrawBox(player.position.x + 12, player.position.y + 14, (player.position.x + 40) + 12, (player.position.y + 50) + 14, 0xffffff, FALSE);

	DrawFormatString(20, 55, 0xffffff, "PlayerClass State : %d", state);
	DrawFormatString(20, 70, 0xffffff, "PlayerClass FrameCounter : %d", frameCounter);
	DrawFormatString(20, 85, 0xffffff, "PlayerClass Elapsed time : %d s", (frameCounter / 60));

	DrawFormatString(20, 100, 0xffffff, "Player Position X : %0.1f", player.position.x);
	DrawFormatString(20, 115, 0xffffff, "Player Position Y : %0.1f", player.position.y);
	DrawFormatString(20, 130, 0xffffff, "Player State : %d", player.state);
	DrawFormatString(20, 145, 0xffffff, "Player Img State : %d", playerImg_state);

	DrawFormatString(20, 200, 0xffffff, "debug[0] : %d", debug[0]);
	

	/*
		state
		0 地面に足がついて待機
		1 歩行
		2 飛行
		3 ダメージ（風船消費）
		4 敵にやられて落下（残機消費）

		player.state
		0 左向きで静止
		1 右向きで静止
		2 左向きに歩行
		3 右向きに歩行
		4 左向きにスリップ
		5 右向きにスリップ
		6 左向きに飛行
		7 右向きに飛行
	*/
};

// プレイヤー移動
bool GamePlayer::Control() {

	if (!CheckHitKey(KEY_INPUT_SPACE)) {
		keyInput_state[0] = 0;
	};
	if (!CheckHitKey(KEY_INPUT_A)) {
		keyInput_state[1] = 0;
	};
	if (!CheckHitKey(KEY_INPUT_D)) {
		keyInput_state[2] = 0;
	};	

	if (CheckHitKey(KEY_INPUT_SPACE) && keyInput_state[0] == 0) {



		keyInput_state[0] = 1;
	};

	// --------------------------------------------------------------------------------------------

	if (state == PLAYER_STOP) {
		if (CheckHitKey(KEY_INPUT_A)) {
			player.position.x = player.position.x - 2;
			if (player.state <= 1) {
				playerImg_state = 8;
			};
			player.state = 2;
			return true;
		}
		else if (CheckHitKey(KEY_INPUT_D)) {
			player.position.x = player.position.x + 2;
			if (player.state <= 1) {
				playerImg_state = 8;
			};
			player.state = 3;
			return true;
		};
	}
	else if (state == PLAYER_FLIGHT) {
		if (player.state <= 1) {
			player.state = player.state + 6;
		}
		else if (player.state <= 3) {
			player.state = player.state + 4;
		}
		else if (player.state <= 5) {
			player.state = player.state + 2;
		}
		if (CheckHitKey(KEY_INPUT_SPACE) && (fly_state == 0)) {
			if (CheckHitKey(KEY_INPUT_A)) {
				player.position.x = player.position.x - 2;
				return true;
			}
			else if (CheckHitKey(KEY_INPUT_D)) {
				player.position.x = player.position.x + 2;
				return true;
			};
		}
		else {
			if (CheckHitKey(KEY_INPUT_A)) {
				player.state = 6;
				return true;
			}
			else if (CheckHitKey(KEY_INPUT_D)) {
				player.state = 7;
				return true;
			};
		};
	};

	if (CheckHitKey(KEY_INPUT_W)) {
		player.position.y = player.position.y - 2;
		return true;
	}
	else if (CheckHitKey(KEY_INPUT_S)) {
		player.position.y = player.position.y + 2;
		return true;
	};

	if (CheckHitKey(KEY_INPUT_SPACE) && (fly_state == 0)) {
		//player.position.y = player.position.y - 30;
		fly_state = 1;
		return true;
	};

	return false;
};

void GamePlayer::Gravity() {
	if (SCREEN_HEIGHT > player.position.y) {
		player.position.y = player.position.y + 1;
	};
};

void GamePlayer::Animation() {
	if (player.state <= 1) {
		if (frameCounter % 30 == 0) {
			if (playerImg_state >= 2) {
				playerImg_state = 0;
			}
			else {
				playerImg_state++;
			};
		};
	}
	else if (player.state <= 3) {
		if (frameCounter % 5 == 0) {
			if (playerImg_state >= 10) {
				playerImg_state = 8;
			}
			else {
				playerImg_state++;
			};
		};
	}
	else if (player.state <= 7) {
		if (player.state != 6) {
			if (player.state != 7) {
				playerImg_state = 18;
			};
		};
		if (frameCounter % 30 == 0) {
			if (playerImg_state >= 20) {
				playerImg_state = 18;
			}
			else {
				playerImg_state++;
			};
		};
	}

};

void GamePlayer::Bounce() {

};