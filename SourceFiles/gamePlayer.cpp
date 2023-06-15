/********************************
* ゲームプレイヤー処理
* 編集者：島袋
********************************/
#include "main.h"

// プレイヤークラスのコンストラクタ
GamePlayer::GamePlayer() {
	// 初期化処理
	state = 0;
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
	DrawFormatString(20, 100, 0xffffff, "プレイヤークラス実行中！");
};