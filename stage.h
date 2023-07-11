#pragma once
#include "SourceFiles/AbstractScene.h"
#include "SourceFiles/GameScene.h"

class Stage : public AbstractScene
{
private:
	int StageImages;
	int StageImages1;

public:
	//コンストラクタ
	Stage();
	//デストラクタ
	~Stage();
	//描画以外の更新を実行
	AbstractScene* Update() override;
	//描画以外に関することを実装
	void Draw() const override;
};

