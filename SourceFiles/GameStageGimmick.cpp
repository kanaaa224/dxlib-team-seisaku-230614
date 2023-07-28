/********************************
* ゲームステージギミック処理
* 編集者：
********************************/
#include "main.h"

GameStageGimmick::GameStageGimmick() {
	// シャボン玉画像読込
	LoadDivGraph("Resources/Images/Stage/Stage_BubbleAnimation.png", 4, 4, 1, 64, 64, img_bubble);

	frequency = 0;
	bubble_count = 0;
	frameCounter = 0;
	bubble_anim = 0;

	bubble_height = 400;

	bubble_flg = 0;

	count = 0;
	spawnflg = 0; // 追加：プレイヤーが500以上に行った時のフラグ

	//シャボン玉スコア画像　仮
	//GetScore_500 = LoadGraph("Resources/Images/Stage/GetScore_500.png");
};

GameStageGimmick::~GameStageGimmick() {

};

void GameStageGimmick::BubbleUpdate() {

	float amplitude = 50.0f;
	float frequency = 0.02;

	float bubble_x = 100;

    /* if (CheckHitKey(KEY_INPUT_B) && !position_flg) {でx取得*/

    if (playerCollide.ul.y >= 500 && bubble[count].flg == 0) {
        spawnflg = 1;
        bubble[count].flg = 1;
        bubble[count].y = 500;
        bubble[count].spawnX = playerCollide.ul.x;
    }

    // countを1だけプラスする（プレイヤーが500以上のy座標に到達した後に一度だけ実行される）
    if (playerCollide.ul.y >= 500 && !spawnflg) {
        count++;
        if (count >= max_bubbles) {
            count = 0; // countがmax_bubbles以上になった場合、最初のシャボン玉に戻る
        }
        spawnflg = 1;
    }
    else if (playerCollide.ul.y < 500) {
        spawnflg = 0; // プレイヤーが500未満の場合、フラグをリセット
    }

    // シャボン玉が上昇中の処理
    for (int i = 0; i < max_bubbles; i++) {
        if (bubble[i].flg == 1) {
            bubble_x = 100; // 初期位置に戻す
            bubble_x += amplitude * sin(frequency * bubble_count) - 140;
            bubble[i].x = bubble_x + bubble[i].spawnX;
            bubble_count++;
            bubble[i].y--;
            if (bubble[i].y < 0) {
                bubble[i].flg = 0;
                bubble[i].y = 480;
            }
            if (bubble_count % 30 == 0) {
                bubble[i].anim++;
            }
            if (bubble[i].anim == 3) {
                bubble[i].anim = 0;
            }
        }
    }
}
void GameStageGimmick::BubbleDraw() const {
	// 全てのシャボン玉を描画
	for (int i = 0; i < max_bubbles; i++) {
		if (bubble[i].flg == 1) {
			DrawGraph(bubble[i].x, bubble[i].y, img_bubble[bubble[i].anim], TRUE);
		}
	}

	
	DrawFormatString(100, 130, 0x00ffff, "count %d", count);
	DrawFormatString(100, 100, 0x00ffff, "%d", bubble[0].y);
	DrawFormatString(100, 160, 0x00ffff, "player %f", playerCollide.ul.y);
};