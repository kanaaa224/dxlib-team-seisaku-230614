/********************************
* ゲームプレイヤー処理
* 担当：島袋
********************************/
#pragma once
#include "main.h"

#define COLLIDE 0
#define TURN    1
#define ANIM    2
#define BLINK 3
#define MOVE 0
#define FALL 1

#define MISS_FALLSEA -1
#define MISS_BALLOONZERO -2
#define MISS_LIGHTNING -3

#define FIRST_POSITION_X 50
#define FIRST_POSITION_Y 405

// float型 2次元座標 構造体
struct Position {
	float x = 0.0f;
	float y = 0.0f;
};

// 大きさ 構造体
struct Size {
	float width = 0.0f;
	float height = 0.0f;
};

// ブロック 構造体
struct Collide {
	Position ul, lr; // UpperLeft LowerRight
};

// 人 構造体
struct Person {
	Position position;
	Size size;
	int state = 0;
	int hp = 0;
};

// プレイヤークラス
class GamePlayer {
private:
	int frameCounter;

	Person player;  // プレイヤーの位置、サイズ、状態、風船の状態

	float inputX;   // スティック横軸の入力
	int flapCount;  // ジャンプ数
	int flightMove; // 空中で羽ばたき中の移動
	int state[4];   // 当たり判定の状態、左右反転状態、アニメーションのフレームカウンター、最初の点滅フラグ
	float speed[2]; // 移動、落下速度
	int stock;      // 残機

	int img_player[30];
	int snd_se_flight;
	int snd_se_walk;
	int snd_se_bound;
	int snd_se_restart;
	int snd_se_crack;   // 風船が割れた音
	int snd_se_fall;    // 風船が割れて落下中の音
	int snd_se_fell;    // 海に落ちた音

	Collide collideData;

public:
	// コンストラクタ
	GamePlayer();

	// デストラクタ
	~GamePlayer();

	// 初期化
	void Init();

	// 更新
	void Update();

	// 描画
	void Draw() const;

	// プレイヤーの状態を設定
	void SetState(int State) {
		player.state = State;
	};

	// プレイヤーの状態を取得
	int GetState() {
		return player.state;
	};

	// プレイヤーの位置を取得（float型 座標 構造体）
	Position GetPosition() {
		return player.position;
	};

	// プレイヤーのサイズを取得（大きさ 構造体）
	Size GetSize() {
		return player.size;
	};

	// 当たり判定用の左上・右上の座標を設定
	void SetCollideData(Collide CollideData) {
		collideData.ul.x = CollideData.ul.x;
		collideData.ul.y = CollideData.ul.y;
		collideData.lr.x = CollideData.lr.x;
		collideData.lr.y = CollideData.lr.y;
	};

	// 風船の部分のボックスデータの取得
	Collide GetCollideData() {
		Collide CollideData;
		CollideData.ul.x = (player.position.x - player.size.width);
		CollideData.ul.y = (player.position.y - player.size.height);
		CollideData.lr.x = (player.position.x + player.size.width);
		CollideData.lr.y = (player.position.y - player.size.height) + 20;
		return CollideData;
	};

	// リスポーン
	void Restart() {
		Init();
		PlaySoundMem(snd_se_restart, DX_PLAYTYPE_BACK, TRUE);
	};

	// ダメージ（風船消失、無ければミス）
	void Damage() {
		if (player.hp > 1) {
			player.hp--;
			PlaySoundMem(snd_se_crack, DX_PLAYTYPE_BACK, TRUE);
		}
		else Miss(0);
	};

	// ミス（0で通常ミス、1で感電ミス、2で海落下ミス、3で魚に捕まりミス）
	void Miss(int MissType) {
		if (player.hp >= 0) {
			if (MissType == 0) player.hp = -1;
			else if (MissType == 1) player.hp = -2;
			else if (MissType == 2) player.hp = -3;
		};
	};

	// プレイヤーのHPを設定
	void SetHP(int HP) {
		player.hp = HP;
	};

	// プレイヤーのHPを取得
	int GetHP() {
		return player.hp;
	};

	// プレイヤーの残機を設定
	void SetStock(int Stock) {
		stock = Stock;
	};

	// プレイヤーの残機を取得
	int GetStock() {
		return stock;
	};

	// デバッグ表示
	void Debug() const {
		DrawBox((int)(player.position.x - player.size.width), (int)(player.position.y - player.size.height), (int)(player.position.x + player.size.width), (int)(player.position.y + player.size.height), 0xffffff, FALSE);

		int x = 10;
		int y = 50;

		DrawFormatString(x, y, GetColor(255, 255, 255), "プレイヤークラス データ");
		y += 30;
		DrawFormatString(x, y, GetColor(255, 255, 255), "x: %0.0f y: %0.0f", player.position.x, player.position.y);
		y += 30;
		DrawFormatString(x, y, GetColor(255, 255, 255), "playerState: %d", player.state);
		y += 15;
		DrawFormatString(x, y, GetColor(255, 255, 255), "playerHP: %d", player.hp);
		y += 15;
		DrawFormatString(x, y, GetColor(255, 255, 255), "inputX: %0.1f", inputX);
		y += 15;
		DrawFormatString(x, y, GetColor(255, 255, 255), "flapCount: %d", flapCount);
		y += 15;
		DrawFormatString(x, y, GetColor(255, 255, 255), "flightMove: %d", flightMove);
		y += 15;
		DrawFormatString(x, y, GetColor(255, 255, 255), "collideState: %d", state[COLLIDE]);
		y += 15;
		DrawFormatString(x, y, GetColor(255, 255, 255), "turnState: %d", state[TURN]);
		y += 15;
		DrawFormatString(x, y, GetColor(255, 255, 255), "animState: %d", state[ANIM]);
		y += 15;
		DrawFormatString(x, y, GetColor(255, 255, 255), "blinkState: %d", state[BLINK]);
		y += 15;
		DrawFormatString(x, y, GetColor(255, 255, 255), "moveSpeed: %0.1f fallSpeed: %0.1f", speed[0], speed[1]);
		y += 15;
		DrawFormatString(x, y, GetColor(255, 255, 255), "frameCounter: %d", frameCounter);
	};

	//// プレイヤー移動
	//bool Control();

	//// 重力を作用させる
	//void Gravity();

	//// プレイヤー画像のアニメーションを行う
	//void Animation();

	//// 跳ね返りさせる
	//void Bounce();
};

//enum struct PlayerState {
//	stay, walk, flight
//};