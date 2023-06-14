/********************************
* シーンマネージャー
* 作者：島袋
********************************/
#include "SceneManager.h"

// シーン更新メンバ関数
AbstractScene* SceneManager::Update() {
	AbstractScene* p = mScene->Update();

	if (p != mScene) {
		delete mScene;
		mScene = p; // 次に表示したいシーン
	};

	return p;
};

// シーン描画メンバ関数
void SceneManager::Draw() const {
	mScene->Draw();
};