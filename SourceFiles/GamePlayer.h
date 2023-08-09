/********************************
* ゲームプレイヤー処理
* 担当：島袋
********************************/
#pragma once
#include "main.h"

#define COLLIDE 0
#define TURN    1
#define ANIM    2
#define BLINK   3
#define MISS    4

#define MOVE 0
#define FALL 1

#define MISS_LIGHTNING   1
#define MISS_FALLSEA     2

#define PLAYER_DEFAULT_POSITION_X 50
#define PLAYER_DEFAULT_POSITION_Y 405

#define INPUT_X_MAGIN 0.3

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

	Person player;    // プレイヤーの位置、サイズ、状態、風船の状態

	float inputX;     // スティック横軸の入力
	int flapCount;    // ジャンプ数
	int flightMove;   // 空中で羽ばたき中の移動
	int state[5];     // 当たり判定の状態、左右反転状態、アニメーションのフレームカウンター、最初の点滅フラグ、ミス時のフレーム
	Position inertia; // 移動・落下の慣性
	int stock;        // 残機

	int img_player[31];
	int snd_se_flight;
	int snd_se_walk;
	int snd_se_bound;
	int snd_se_restart;
	int snd_se_crack;
	int snd_se_electricShock;
	int snd_se_fall;
	int snd_se_fell;

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
	void SetState(int State /*, int isFloor*/) {
		player.state = State;
	};

	// プレイヤーの状態を取得
	int GetState() {
		return player.state;
	};

	// プレイヤーの位置を設定（float型 座標 構造体）
	void SetPosition(Position _Position) {
		player.position = _Position;
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
	void SetCollide(Collide CollideData) {
		collideData.ul.x = CollideData.ul.x;
		collideData.ul.y = CollideData.ul.y;
		collideData.lr.x = CollideData.lr.x;
		collideData.lr.y = CollideData.lr.y;
	};

	// プレイヤー左上・右上の座標の取得
	Collide GetCollide() {
		Collide CollideData;
		CollideData.ul.x = (player.position.x - player.size.width);
		CollideData.ul.y = (player.position.y - player.size.height);
		CollideData.lr.x = (player.position.x + player.size.width);
		CollideData.lr.y = (player.position.y + player.size.height);
		return CollideData;
	};

	// 風船エリアの左上・右上の座標の取得
	Collide GetWeakCollide() {
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
			//else if (MissType == 3) player.hp = -4;
			state[MISS] = frameCounter;
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

		DrawBox(collideData.ul.x, collideData.ul.y, collideData.lr.x, collideData.lr.y, 0xffffff, FALSE);

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
		DrawFormatString(x, y, GetColor(255, 255, 255), "missState: %d", state[MISS]);
		y += 15;
		DrawFormatString(x, y, GetColor(255, 255, 255), "inertiaX: %0.1f inertiaY: %0.1f", inertia.x, inertia.y);
		y += 15;
		DrawFormatString(x, y, GetColor(255, 255, 255), "frameCounter: %d", frameCounter);
		y += 30;
		DrawFormatString(x, y, GetColor(255, 255, 255), "stock: %d", stock);
	};

	//// ミス時の水しぶきエフェクト
	//void DrawSplashEffect(int frame) {

	//};

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

////////////////////////////////////////////////////////////////////////////////////////////////////

// エフェクトクラス
class GameEffect {
private:
	int state, frameCounter[2];

	bool splash;
	int splash_anim, splash_x, splash_y;

	int point, point_x, point_y;

	int img_splash[4];
	int img_point[5];
public:
	GameEffect() {
		state = 0;
		frameCounter[0] = 0;
		frameCounter[1] = 0;

		splash = false;
		splash_anim = 0;
		splash_x = 0;
		splash_y = 0;

		point = 0;
		point_x = 0;
		point_y = 0;

		if (LoadDivGraph("Resources/images/Stage/Stage_SplashAnimation.png", 4, 4, 1, 64, 32, img_splash) == -1) throw;
		if ((img_point[0] = LoadGraph("Resources/Images/Score/GetScore_500.png")) == -1) throw;
		if ((img_point[1] = LoadGraph("Resources/Images/Score/GetScore_750.png")) == -1) throw;
		if ((img_point[2] = LoadGraph("Resources/Images/Score/GetScore_1000.png")) == -1) throw;
		if ((img_point[3] = LoadGraph("Resources/Images/Score/GetScore_1500.png")) == -1) throw;
		if ((img_point[4] = LoadGraph("Resources/Images/Score/GetScore_2000.png")) == -1) throw;
	};

	~GameEffect() {
		for (int i = 0; i < 4; i++) {
			DeleteGraph(img_splash[i]);
		};
		for (int i = 0; i < 5; i++) {
			DeleteGraph(img_point[i]);
		};
	};

	void Update() {
		if (!splash) {
			frameCounter[0] = 0;
			splash_anim = 0;
		};
		if (splash) {
			frameCounter[0]++;
			if (frameCounter[0] % 5 == 0) {
				if (splash_anim < 4) {
					splash_anim++;
				}
				else {
					splash = false;
				};
			};
		};
		if (!point) frameCounter[1] = 0;
		if (point) if (frameCounter[1]++ % 90 == 0) point = 0;
	};

	void Draw() const {
		if (splash && (splash_anim <= 3)) DrawRotaGraph(splash_x, splash_y, 1.0f, 0, img_splash[splash_anim], TRUE);
		if (point) DrawRotaGraph(point_x, point_y - 20, 1.0f, 0, img_point[point - 1], TRUE);
	};

	void Splash(int x, int y) {
		if (!splash) {
			splash_x = x;
			splash_y = y;
			splash = true;
		};
	};

	void Point(int x, int y, int p) {
		if (!point) {
			point_x = x;
			point_y = y;
			point = p;
		};
	};
};

////////////////////////////////////////////////////////////////////////////////////////////////////
/*
class Collider {
public:
	static int CheckCollide(Collide collideA, Collide collideB) {
		if (collideA.lr.x <= collideB.ul.x || collideA.ul.x >= collideB.lr.x || collideA.lr.y <= collideB.ul.y || collideA.ul.y >= collideB.lr.y) return 0;
		if (fabsf(collideA.lr.y - collideB.ul.y) < 10) return 1;
		else if (fabsf(collideA.ul.y - collideB.lr.y) < 10) return 2;
		else if (fabsf(collideA.lr.x - collideB.ul.x) < 10) return 3;
		else if (fabsf(collideA.ul.x - collideB.lr.x) < 10) return 4;
		else return 0;
	};

	static int CheckCollideBox(float s1X1, float s1Y1, float s1X2, float s1Y2, float s2X1, float s2Y1, float s2X2, float s2Y2) {
		if (s1X2 <= s2X1 || s1X1 >= s2X2 || s1Y2 <= s2Y1 || s1Y1 >= s2Y2) return 0;
		if (fabsf(s1Y2 - s2Y1) < 10) return 1;
		else if (fabsf(s1Y1 - s2Y2) < 10) return 2;
		else if (fabsf(s1X2 - s2X1) < 10) return 3;
		else if (fabsf(s1X1 - s2X2) < 10) return 4;
		else return 0;
	};
};*/