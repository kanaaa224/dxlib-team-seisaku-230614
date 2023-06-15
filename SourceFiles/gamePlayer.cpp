/********************************
* ゲームプレイヤー
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

// プレイヤークラス
//GamePlayer::Draw() {
//	DrawFormatString(20, 50, 0xffffff, "プレイヤークラス実行中！");
//};