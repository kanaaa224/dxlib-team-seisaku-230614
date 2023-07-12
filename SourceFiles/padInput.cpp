/********************************
* ボタン・キー入力処理
* 作成：島袋
********************************/
#include "padInput.h"

int PadInput::nowBtn[PAD_BUTTONS];
int PadInput::oldBtn[PAD_BUTTONS];
XINPUT_STATE PadInput::inputState;
