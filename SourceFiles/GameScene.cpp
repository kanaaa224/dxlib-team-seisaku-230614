/********************************
* ゲームメインシーン
* 編集者：島袋
********************************/
#include "main.h"

Game::Game() {
	// 初期化処理
	state = 0;
	GameMain::Init();
};

Game::~Game() {
	// 終了処理
};

AbstractScene* Game::Update() {
	// 自分の手の処理
	if (InputCtrl::GetPressKey(KEY_INPUT_Z) || InputCtrl::GetPress(XINPUT_BUTTON_X)) {
		GameMain::SetScore(ME, ROCK);     // グー
		state = 1;
	}
	else if (InputCtrl::GetPressKey(KEY_INPUT_X) || InputCtrl::GetPress(XINPUT_BUTTON_A)) {
		GameMain::SetScore(ME, SCISSORS); // チョキ
		state = 1;
	}
	else if (InputCtrl::GetPressKey(KEY_INPUT_C) || InputCtrl::GetPress(XINPUT_BUTTON_B)) {
		GameMain::SetScore(ME, PAPER);    // パー
		state = 1;
	};

	// 結果処理
	if (state == 1) {
		GameMain::SetScore(AITE, GetRand(2));
		int result = GameMain::GetScore(ME) - GameMain::GetScore(AITE);
		if (result == 0) {
			// 引き分け
		}
		else if (result == -1 || result == 2) {
			// 勝ち
			GameMain::SetClearFlg(1);
		}
		else {
			// 負け
			GameMain::SetClearFlg(2);
		};
		return new Result(); // リザルトシーンへ推移
	};

	if (InputCtrl::GetPressKey(KEY_INPUT_ESCAPE) || InputCtrl::GetPress(XINPUT_BUTTON_BACK)) {
		return new Title(); // タイトルシーンへ推移（戻る）
	};

	return this;
};

void Game::Draw() const {
	SetFontSize(16);

	DrawFormatString(20, 50, 0xffffff, "いくよー、じゃん、、けん、、");

	DrawFormatString(20, 95, 0xffffff, "> 出してください");
	DrawFormatString(20, 110, 0xffffff, "グー：Zキー、チョキ：Xキー、パー：Cキー、やめる：Escキー");
};

int GameMain::score[] = { 0, 0 };
int GameMain::clearFlg = 0;
