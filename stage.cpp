#include "Stage.h"
#include "DxLib.h"

//コンストラクタ
Stage::Stage()
{
	//ステージ画像の読み込み
	StageImages = LoadGraph("Resources/images/Stage1.png");
}

//デストラクタ
Stage::~Stage()
{

}

AbstractScene* Stage::Update()
{
	return this;
}

//描画
void Stage::Draw() const
{
	//ステージ画像の表示
	DrawExtendGraph(0, 0, 640, 480, StageImages, TRUE);
	//プレイヤーの仮表示
	
}