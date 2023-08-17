
/********************************
* ゲームステージギミック処理
* 編集者：
********************************/
#define _USE_MATH_DEFINES
#include "main.h"

GameStageGimmick::GameStageGimmick() {
	LoadDivGraph("Resources/Images/Stage/Stage_BubbleAnimation.png", 4, 4, 1, 64, 64, img_bubble);

	if ((LoadDivGraph("Resources/Images/Stage/Stage_ThunderEffectAnimation.png", 3, 3, 1, 32, 32, Thunder)) == -1) throw;
	ThunderAnim = 0;
	ThunderAnimFlg = 0;
	AnimChangefps = 3;


};

GameStageGimmick::~GameStageGimmick() {
	for (int i = 0; i < 4; i++) {
		DeleteGraph(img_bubble[i]);
	};
};

void GameStageGimmick::UpdateBubble() {
	for (int i = 0; i < BUBBLE_MAX; i++) {
		if (bubble[i].flg) {
			bubble[i].frameCounter++;
			if (bubble[i].flg >= 20) bubble[i].flg = 0;
			else if (bubble[i].flg == 10) {
				bubble[i].anim = 3;
				bubble[i].flg = 11;
			}
			else if (bubble[i].flg >= 11) bubble[i].flg++;
			else if (bubble[i].y < -70) bubble[i].flg = 0;
			else {
				bubble[i].y--;

				float swingMax = 100.0f;
				float moveX = swingMax * sin(2 * M_PI * bubble[i].frameCounter / 240.0f);

				if (bubble[i].flg == 1) bubble[i].drawX = bubble[i].x + moveX;
				else bubble[i].drawX = bubble[i].x - moveX;

				if (bubble[i].frameCounter % 30 == 0) {
					if (bubble[i].anim >= 2) bubble[i].anim = 0;
					else bubble[i].anim++;
				};
			};
		};
	};
};

void GameStageGimmick::DrawBubble() const {


}
void GameStageGimmick::UpdateThunder()
{


	// 雷
	ThunderAnim++;
	if (ThunderAnim > 0 && ThunderAnim <= AnimChangefps)
	{
		ThunderAnimFlg = 0;
	}
	else if (ThunderAnim > AnimChangefps && ThunderAnim <= AnimChangefps * 2)
	{
		ThunderAnimFlg = 1;
	}
	else if (ThunderAnim > AnimChangefps * 2 && ThunderAnim <= AnimChangefps * 3)
	{
		ThunderAnimFlg = 2;
	}
	else if (ThunderAnim > AnimChangefps * 3) {
		ThunderAnim = 0;
	};


	// ボールの移動
	//ここにif文で雷のスタート条件？


	ThunderX += MoveX;
	ThunderY -= MoveY;

	// 壁・天井での反射
	if (ThunderX < 4 || ThunderX > 630) { // 横の壁
		if (ThunderX < 4) {
			ThunderX = 4;
		}
		else {
			ThunderX = 630;
		}
		ThunderAngle = (1 - ThunderAngle) + 0.5f;
		if (ThunderAngle > 1) ThunderAngle -= 1.0f;
		ChangeAngle();
	}
	if (ThunderY < 8) { // 上の壁
		ThunderAngle = (1 - ThunderAngle);
		ChangeAngle();
	}

	if (ThunderY > 470) { // 下の壁
		ThunderAngle = (1 - ThunderAngle);
		ChangeAngle();
	}
	thunderx = ThunderX;
	thundery = ThunderY;
}

void GameStageGimmick::ChangeAngle()
{
	float rad = ThunderAngle * (float)M_PI * 2;
	MoveX = (int)(Speed * cosf(rad));
	MoveY = (int)(Speed * sinf(rad));
}

void GameStageGimmick::DrawThunder()const
{
	//雷
	DrawGraph(ThunderX, ThunderY,  Thunder[ThunderAnimFlg], TRUE);
	DrawFormatString(300, 300, 0xffffff, "%d", ThunderX);

}



