
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
	ThunderAnimB = 0;
	ThunderAnimFlg = 0;
	ThunderAnimFlgB = 0;
	AnimChangefps = 3;
	AnimChangefpsB = 5;
	//最初に雷をランダムな方向に進ませる
	Thunderrandom = GetRand(2);


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
	for (int i = 0; i < BUBBLE_MAX; i++) {
		if (bubble[i].flg) DrawRotaGraph(bubble[i].drawX, bubble[i].y, 1.0f, 0, img_bubble[bubble[i].anim], TRUE);
		//if (bubble[i].flg) DrawBox(bubble[i].drawX - 32, bubble[i].y - 32, bubble[i].drawX + 32, bubble[i].y + 32, 0xffffff, FALSE);
		//DrawFormatString(10, 50 + (15 * i), 0xffffff, "%d : x:%f y:%f flg:%d drawX:%f", i, bubble[i].x, bubble[i].y, bubble[i].flg, bubble[i].drawX);
	};

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

	// 雷 雲から伸びるやつ
	ThunderAnimB++;
	if (ThunderAnimB > 0 && ThunderAnimB <= AnimChangefps)
	{
		ThunderAnimFlgB = 0;
	}
	else if (ThunderAnimB > AnimChangefps && ThunderAnimB <= AnimChangefps * 2)
	{
		ThunderAnimFlgB = 1;
	}
	else if (ThunderAnimB> AnimChangefps * 2 && ThunderAnimB <= AnimChangefps * 3)
	{
		ThunderAnimFlgB = 2;
	}
	else if (ThunderAnimB > AnimChangefps * 2 && ThunderAnimB <= AnimChangefps * 4)
	{
		ThunderAnimFlgB = 3;
	}
	else if (ThunderAnimB > AnimChangefps * 2 && ThunderAnimB <= AnimChangefps * 5)
	{
		ThunderAnimFlgB = 4;
	}
	else if (ThunderAnimB > AnimChangefps * 5) {
		ThunderAnimB = 0;
	};

	// ボールの移動
	//ここにif文で雷のスタート条件？
	if (CheckHitKey(KEY_INPUT_V)) {
		Thunder_flg = 1;
		Thunder_flg2 = 1;
	}
	if (Thunder_flg == 1) {
		framecounter++;

		if (Thunder_flg == 1) {
			if (Thunderrandom == 0) {//左下
				ThunderX[ThunderStart] += MoveX;
				ThunderY[ThunderStart] -= MoveY;

				ThunderAngleB = M_PI / 4;
			}

			else if (Thunderrandom == 1) {//右下
				ThunderX[ThunderStart] -= MoveX;
				ThunderY[ThunderStart] -= MoveY;

				ThunderAngleB = M_PI - 80;
			}

			else if (Thunderrandom == 2) {//左上
				ThunderX[ThunderStart] += MoveX;
				ThunderY[ThunderStart] += MoveY;

				ThunderAngleB = M_PI / 2;
			}

			// 壁・天井での反射
			if (ThunderX[ThunderStart] < 4 || ThunderX[ThunderStart] > 630) { // 横の壁
				if (ThunderX[ThunderStart] < 4) {
					ThunderX[ThunderStart] = 4;
				}
				else {
					ThunderX[ThunderStart] = 630;
				}
				ThunderAngle = (1 - ThunderAngle) + 0.5f;
				if (ThunderAngle > 1) ThunderAngle -= 1.0f;
				ChangeAngle();
			}
			if (ThunderY[ThunderStart] < 8) { // 上の壁
				ThunderAngle = (1 - ThunderAngle);
				ChangeAngle();
			}

			if (ThunderY[ThunderStart] > 470) { // 下の壁
				ThunderAngle = (1 - ThunderAngle);
				ChangeAngle();
			}

			//現在のステージ

			ThunderStart = GameMain::GetNowStageIndex();
			thunderx = ThunderX[ThunderStart];
			thundery = ThunderY[ThunderStart];
		}
	}
	if (framecounter % 500 == 0) {
		Thunder_flg = 0;
		ThunderX[ThunderStart] = SaveThunderX[ThunderStart];
		ThunderY[ThunderStart] = SaveThunderY[ThunderStart];
	}
	if (framecounter % 100 == 0) Thunder_flg2 = 0;
}

void GameStageGimmick::ChangeAngle()
{
	float rad = ThunderAngle * (float)M_PI * 2;
	MoveX = (int)(Speed * cosf(rad));
	MoveY = (int)(Speed * sinf(rad));
}

void GameStageGimmick::DrawThunder()const
{
	if (Thunder_flg == 1) {
		//雷
		DrawGraph(ThunderX[ThunderStart], ThunderY[ThunderStart], Thunder[ThunderAnimFlg], TRUE);

		if (Thunder_flg2 == 1) {
			//雲から出る雷
			DrawRotaGraph(ThunderBX[ThunderStart], ThunderBY[ThunderStart], 1.0, ThunderAngleB, ThunderB[ThunderAnimFlgB], TRUE);
		}
	}
}



