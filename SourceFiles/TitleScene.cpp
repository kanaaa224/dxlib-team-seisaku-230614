/********************************
* タイトルシーン
* 担当：島袋
********************************/
#include "main.h"

Title::Title() {
	state = 0;
	frameCounter = 0;

	ctrl = false;

	if ((img_logo = LoadGraph("Resources/Images/Title/Title_Logo.png")) == -1) throw;
	if ((img_mode = LoadGraph("Resources/images/Title/Title_ModeSelect.png")) == -1) throw;
	if ((img_credit = LoadGraph("Resources/images/Title/Title_Credit.png")) == -1) throw;
	if (LoadDivGraph("Resources/images/Title/Title_CursorAnimation.png", 4, 4, 1, 32, 64, img_cursor) == -1) throw;
};

Title::~Title() {
	DeleteGraph(img_logo);
	DeleteGraph(img_mode);
	DeleteGraph(img_credit);
	for (int i = 0; i < 4; i++) {
		DeleteGraph(img_cursor[i]);
	};
};

AbstractScene* Title::Update() {
	if (frameCounter++ % 30 == 0) state++;
	if ((state % 10) >= 4) state -= 4;

	if ((PadInput::GetLStick().y == 0.0f) && !CheckHitKey(KEY_INPUT_UP) && !CheckHitKey(KEY_INPUT_DOWN) && !CheckHitKey(KEY_INPUT_W) && !CheckHitKey(KEY_INPUT_S)) ctrl = true;
	if (PadInput::OnPress(XINPUT_BUTTON_DPAD_UP) || (((PadInput::GetLStick().y >= 0.7f) || CheckHitKey(KEY_INPUT_UP) || CheckHitKey(KEY_INPUT_W)) && ctrl)) {
		if (state < 10) state += 20;
		else state -= 10;
		ctrl = false;
	}
	else if (PadInput::OnPress(XINPUT_BUTTON_BACK) || PadInput::OnPress(XINPUT_BUTTON_DPAD_DOWN) || (((PadInput::GetLStick().y <= -0.7f) || CheckHitKey(KEY_INPUT_DOWN) || CheckHitKey(KEY_INPUT_S)) && ctrl)) {
		if (state >= 20) state -= 20;
		else state += 10;
		ctrl = false;
	}
	else if (PadInput::OnPress(XINPUT_BUTTON_START) || PadInput::OnPress(XINPUT_BUTTON_B) || CheckHitKey(KEY_INPUT_RETURN)) {
		if (state >= 0 && state <= 9) return new Game();
	};

	return this;
};

void Title::Draw() const {
	DrawRotaGraph(320, 140, 1.0f, 0, img_logo, TRUE);
	DrawRotaGraph(340, 330, 1.0f, 0, img_mode, TRUE);
	DrawRotaGraph(320, 450, 1.0f, 0, img_credit, TRUE);

	int y = 300;
	if (state >= 10 && state <= 19) y += 35;
	else if (state >= 20 && state <= 29) y += 70;

	DrawRotaGraph(150, y, 1.0f, 0, img_cursor[state % 10], TRUE, FALSE);
};