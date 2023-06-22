#pragma once

#include "AbstractScene.h"

class Stage : public AbstractScene
{
private:

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

