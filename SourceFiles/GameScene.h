/********************************
* ゲームメインシーン
* 担当：島袋、
********************************/
#pragma once
#include "AbstractScene.h"
#include "main.h"

class Game : public AbstractScene {
private:
	int btn_flg;
	int state;

	GamePlayer player;
	GameStage stage;

	// 仮
	int block[4];
public:
	// コンストラクタ
	Game();

	// デストラクタ
	~Game();

	// 描画以外の更新を実装
	virtual AbstractScene* Update() override;

	// 描画に関することを実装
	virtual void Draw() const override;


	// 当たり判定 - 島袋
	static int CheckCollideSquares(int s1x1, int s1y1, int s1x2, int s1y2, int s2x1, int s2y1, int s2x2, int s2y2) {
        // 四角形1の座標
        int s1_left = s1x1;
        int s1_right = s1x2;
        int s1_top = s1y1;
        int s1_bottom = s1y2;

        // 四角形2の座標
        int s2_left = s2x1;
        int s2_right = s2x2;
        int s2_top = s2y1;
        int s2_bottom = s2y2;

        // 衝突判定
        if (s1_bottom < s2_top) {
            return 1; // 四角形1の上辺と四角形2の下辺が衝突している
        }
        else if (s1_top > s2_bottom) {
            return 2; // 四角形1の下辺と四角形2の上辺が衝突している
        }
        else if (s1_right < s2_left) {
            return 3; // 四角形1の左辺と四角形2の右辺が衝突している
        }
        else if (s1_left > s2_right) {
            return 4; // 四角形1の右辺と四角形2の左辺が衝突している
        }
        else {
            return 0; // 衝突していない
        };
	};
};
