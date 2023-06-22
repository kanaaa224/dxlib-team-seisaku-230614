#include "Stage.h"
#include "DxLib.h"

//コンストラクタ
Stage::Stage()
{

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
	DrawString(250, 240 - 32, "Hello C World!", 0xffffff);
}