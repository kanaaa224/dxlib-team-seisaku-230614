/********************************
* ゲームステージ処理
* 編集者：
********************************/
#include "main.h"

//int GameStage::Stage=0;    //0が最初のステージとなる

GameStageGimmick bubble;

GameStage::GameStage() {


	// 画像読み込み
	img_sea = LoadGraph("Resources/Images/Stage/Stage_Sea01.png");

	img_footing[0] = LoadGraph("Resources/Images/Stage/Stage_Footing01.png");//1
	img_footing[1] = LoadGraph("Resources/Images/Stage/Stage_Footing02.png");//2
	img_footing[2] = LoadGraph("Resources/Images/Stage/Stage_Footing03.png");//3
	img_footing[3] = LoadGraph("Resources/Images/Stage/Stage_Footing04.png");//4
	img_footing[4] = LoadGraph("Resources/Images/Stage/Stage_Footing05.png");//5
	img_footing[5] = LoadGraph("Resources/Images/Stage/Stage_Footing06.png");//6
	img_footing[6] = LoadGraph("Resources/Images/Stage/Stage_Footing07.png");//7
	img_footing[7] = LoadGraph("Resources/Images/Stage/Stage_Footing08.png");//8
	img_Stage[0] = LoadGraph("Resources/Images/Stage/Stage_Land_Left02.png");
	img_Stage[1] = LoadGraph("Resources/Images/Stage/Stage_Land_Right02.png");


	LoadDivGraph("Resources/Images/Stage/Stage_CloudAnimation.png", 3, 3, 1, 128, 64, img_cloud);//雲画像の分割読込
	LoadDivGraph("Resources/Images/Stage/Stage_ThunderEffectAnimation.png", 3, 3, 1, 128, 64, img_ect);//雷画像の分割読込
	

	// 仮 - 足場の当たり判定用ボックス
	block[0][0] = 180; // 真ん中
	block[0][1] = 250;
	block[0][2] = 460;
	block[0][3] = 270;

	block[1][0] = 0 - 20;   // 左下
	block[1][1] = 430;
	block[1][2] = 210;
	block[1][3] = SCREEN_HEIGHT;

	block[2][0] = 400; // 右下
	block[2][1] = 430;
	block[2][2] = SCREEN_WIDTH + 20;
	block[2][3] = SCREEN_HEIGHT;

	// GameStageGimmickオブジェクトの初期化
	bubble = GameStageGimmick(img_bubble);

};

GameStage::~GameStage() {
	// 終了処理
};

void GameStage::Update() {
	bubble.bubble_Update();
};
	

void GameStage::Draw() const {
	DrawExtendGraph(0, 450, 640, 480, img_sea, FALSE); // 海

	int Stage = 0;

	// 足場
	//DrawGraph(-50, 430, img_bg1, FALSE);
		//仮ステージ１の表示
		if (Stage == 0)
		{
			DrawGraph(180, 250, img_footing[0], TRUE); // 真ん中
			DrawGraph(-50, 430, img_footing[0], TRUE); // 左下
			DrawGraph(370, 430, img_footing[0], TRUE); // 右下

			DrawGraph(320, 80, img_cloud[0], TRUE);  // 雲
		}
		//仮ステージ２の表示
		if (Stage == 1)
		{
			DrawGraph(180, 280, img_footing[0], TRUE); // 真ん中
			DrawGraph(-50, 430, img_footing[0], TRUE); // 左下
			DrawGraph(370, 430, img_footing[0], TRUE); // 右下
			DrawGraph(80, 150, img_footing[1], TRUE);
			DrawGraph(450, 150, img_footing[1], TRUE);

			DrawGraph(320, 80, img_cloud[0], TRUE);  // 雲
		}
		//仮ステージ３の表示
		if (Stage == 2)
		{
			DrawGraph(-70, 430, img_footing[0], TRUE); // 左下
			DrawGraph(400, 430, img_footing[0], TRUE); // 右下
			DrawGraph(470, 100, img_footing[3], TRUE); // 右のT字の足場
			DrawGraph(330, 180, img_footing[3], TRUE); // 真ん中のT字の足場
			DrawGraph(180, 240, img_footing[3], TRUE); // 左のT字の足場
			DrawGraph(220, 130, img_footing[4], TRUE); // 左上の小さい足場
			DrawGraph(270, 330, img_footing[2], TRUE); // 海の上の足場
		}
		//仮ステージ４の表示
		if (Stage == 3)
		{
			DrawGraph(-70, 430, img_footing[0], TRUE); // 左下
			DrawGraph(400, 430, img_footing[0], TRUE); // 右下
			DrawGraph(250, 110, img_footing[2], TRUE);
			DrawGraph(100, 210, img_footing[2], TRUE);
			DrawGraph(400, 180, img_footing[2], TRUE);
			DrawGraph(230, 250, img_footing[2], TRUE);
			DrawGraph(300, 330, img_footing[2], TRUE);
		}
		//仮ステージ５の表示
		if (Stage == 4)
		{
			DrawGraph(0, 430, img_Stage[0], TRUE); // 左下
			DrawGraph(480, 430, img_Stage[1], TRUE); // 右下
			DrawGraph(180, 120, img_footing[5], TRUE);
			DrawGraph(190, 330, img_footing[5], TRUE);
			DrawGraph(350, 330, img_footing[5], TRUE);
			DrawGraph(130, 230, img_footing[6], TRUE);
			DrawGraph(250, 180, img_footing[6], TRUE);
			DrawGraph(480, 180, img_footing[6], TRUE);
		}

	
	DrawGraph(320, 80, img_cloud[0], TRUE);  // 雲
	DrawGraph(320, 80, img_ect[0], TRUE);  // 雲

	  // シャボン
	bubble.bubble_Draw();


	// 仮 - 足場の当たり判定用ボックス
	//DrawBox((int)block[0][0], (int)block[0][1], (int)block[0][2], (int)block[0][3], 0xffffff, FALSE); // 真ん中
	//DrawBox((int)block[1][0], (int)block[1][1], (int)block[1][2], (int)block[1][3], 0xffffff, FALSE); // 左下
	//DrawBox((int)block[2][0], (int)block[2][1], (int)block[2][2], (int)block[2][3], 0xffffff, FALSE); // 右下

	
};
