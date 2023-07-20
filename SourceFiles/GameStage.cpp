/********************************
* ゲームステージ処理
* 編集者：
********************************/
#include "main.h"

GameStage::GameStage() {
	// 初期化処理
	bubble_width = 200;
	frequency = 0;
	bubble_count = 0;
	frameCounter = 0;
	bubble_anm = 0;

	// 画像読み込み
	img_sea = LoadGraph("Resources/Images/Stage/Stage_Sea01.png");
	img_footing = LoadGraph("Resources/Images/Stage/Stage_Footing01.png");
	LoadDivGraph("Resources/Images/Stage/Stage_CloudAnimation.png", 3, 3, 1, 128, 64, img_cloud);//雲画像の分割読込
	LoadDivGraph("Resources/Images/Stage/Stage_ThunderEffectAnimation.png", 3, 3, 1, 128, 64, img_ect);//雷画像の分割読込
	
	//シャボン玉画像読込
	LoadDivGraph("Resources/Images/Stage/Stage_BubbleAnimation.png", 4, 4, 1, 64 , 64, img_bubble);

	//シャボン玉スコア画像　仮
	GetScore_500 = LoadGraph("Resources/Images/Stage/GetScore_500.png");
	// 仮 - 足場の当たり判定用ボックス
	block[0][0] = 180; // 真ん中
	block[0][1] = 250;
	block[0][2] = 460;
	block[0][3] = 270;

	block[1][0] = 0;   // 左下
	block[1][1] = 430;
	block[1][2] = 230;
	block[1][3] = SCREEN_HEIGHT;

	block[2][0] = 370; // 右下
	block[2][1] = 430;
	block[2][2] = SCREEN_WIDTH;
	block[2][3] = SCREEN_HEIGHT;

	//
	bubble_width = 200;
	bubble_height = 400;
};

GameStage::~GameStage() {
	// 終了処理
};

void GameStage::Update() {
	
	void HitStage();//ステージの当たり判定
	
	float amplitude = 50.0f;
	float frequency = 0.02;
	
	float bubble_x = 200;

	bubble_x += amplitude * sin(frequency * bubble_count);
		//amplitude波の大きさを決める　//frequency　1秒あたりに何回周期するかを決める
		bubble_width = bubble_x;
		bubble_count += 1;
		bubble_height -=0.5;

		frameCounter++;
		if (frameCounter % 20 == 0) {
			if (bubble_anm == 0) bubble_anm = 1;
			else if (bubble_anm == 1) bubble_anm = 2;
		};
		if (frameCounter % 60  == 0) {
			frameCounter = 0;
			bubble_anm = 0;
		};

		// 仮 - 9キーで雷テスト
		if (CheckHitKey(KEY_INPUT_9)) {
			
		}
};
	

void GameStage::Draw() const {
	DrawExtendGraph(0, 450, 640, 480, img_sea, FALSE); // 海

	// 足場
	//DrawGraph(-50, 430, img_bg1, FALSE);
	DrawGraph(180, 250, img_footing, TRUE); // 真ん中
	DrawGraph(-50, 430, img_footing, TRUE); // 左下
	DrawGraph(370, 430, img_footing, TRUE); // 右下

	DrawGraph(320, 80, img_cloud[0], TRUE);  // 雲
	DrawGraph(320, 80, img_ect[0], TRUE);  // 雲
	DrawGraph(bubble_width, bubble_height, img_bubble[bubble_anm], TRUE);  // シャボン


	// 仮 - 足場の当たり判定用ボックス
	//DrawBox((int)block[0][0], (int)block[0][1], (int)block[0][2], (int)block[0][3], 0xffffff, FALSE); // 真ん中
	//DrawBox((int)block[1][0], (int)block[1][1], (int)block[1][2], (int)block[1][3], 0xffffff, FALSE); // 左下
	//DrawBox((int)block[2][0], (int)block[2][1], (int)block[2][2], (int)block[2][3], 0xffffff, FALSE); // 右下

	DrawFormatString(100, 110, 0x00ffff, "%d", bubble_anm);
	DrawFormatString(100, 120, 0x00ffff, "%d", frameCounter);
};
