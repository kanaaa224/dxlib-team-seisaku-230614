/********************************
* コントローラー入力処理
* 作成：島袋
********************************/
#pragma once
#include "DxLib.h"

#define PAD_BUTTONS 16
#define PAD_STICK_MAX 32767.f

// スティック 構造体
struct PadStick {
    float x, y;
};

// パッドインプットコントローラー クラス
class PadInput {
public:
    static int nowBtn[PAD_BUTTONS];
    static int oldBtn[PAD_BUTTONS];
    static XINPUT_STATE inputState;

private:
    PadInput() = default;

public:
    // 入力状態の更新
    static void Update() {
        GetJoypadXInputState(DX_INPUT_KEY_PAD1, &inputState);
        for (int i = 0; i < PAD_BUTTONS; i++) {
            oldBtn[i] = nowBtn[i];
            nowBtn[i] = inputState.Buttons[i];
        };
    };

    // ボタンの押された瞬間
    static bool OnPress(int Btn) {
        return (nowBtn[Btn] == 1 && oldBtn[Btn] == 0);
    };

    // ボタンの押してる間
    static bool OnPressed(int Btn) {
        return (nowBtn[Btn] == 1);
    };

    // ボタンの離した瞬間
    static bool OnRelease(int Btn) {
        return (nowBtn[Btn] == 1 && oldBtn[Btn] == 0);
    };

    // Lスティックの傾き割合（返り値：スティック構造体）
    static PadStick GetLStick() {
        PadStick padStick;
        padStick.x = inputState.ThumbLX / PAD_STICK_MAX;
        padStick.y = inputState.ThumbLY / PAD_STICK_MAX;
        return padStick;
    };

    // デバッグ表示
    static void Debug() {
        // 画面クリア
        clsDx();

        printfDx("ボタンの入力情報\n");

        // 各ボタンの入力情報出力
        for (int i = 0; i < PAD_BUTTONS; i++) {
            printfDx("OLD: %d\tNOW: %d\n", oldBtn[i], nowBtn[i]);
        };

        // スティックの入力情報出力
        printfDx("\nスティックの入力情報\n");
        printfDx("LX: %d\tLY: %d\n", inputState.ThumbLX, inputState.ThumbLY);
        printfDx("RX: %d\tRY: %d\n", inputState.ThumbRX, inputState.ThumbRY);

        // トリガーの入力情報出力
        printfDx("\nトリガーの入力情報\n");
        printfDx("LT: %d\n", inputState.LeftTrigger);
        printfDx("RT: %d\n", inputState.RightTrigger);
    };
};