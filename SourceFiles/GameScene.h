/********************************
* ゲームメインシーン
* 編集者：島袋
********************************/
#pragma once
#include "AbstractScene.h"

class Game : public AbstractScene {
private:
	int state;
public:
	// コンストラクタ
	Game();

	// デストラクタ
	~Game();

	// 描画以外の更新を実装
	virtual AbstractScene* Update() override;

	// 描画に関することを実装
	virtual void Draw() const override;
};
