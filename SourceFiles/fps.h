/********************************
* FPS固定処理
* 作成：島袋
********************************/
#pragma once

#include <math.h>
#include "DxLib.h"

class FPS {
	int start, now, count;
	float fps;
	static const int sample = 60;
	static const int settingFPS = 60;

public:
	FPS() {
		start = 0;
		now = 0;
		count = 0;
		fps = 0.0f;
	};

	bool Update() {
		if (count == 0) start = GetNowCount();
		if (count == sample) {
			int t = GetNowCount();
			fps = 1000.f / ((t - start) / (float)sample);
			count = 0;
			start = t;
		};
		count++;
		now = GetNowCount();
		return true;
	};

	void Draw() {
		SetFontSize(16);
		DrawFormatString(10, 10, GetColor(255, 255, 255), "FPS: %0.0f", fps);
	};

	void Wait() {
		int tookTime = GetNowCount() - start;
		int waitTime = count * 1000 / settingFPS - tookTime;
		if (waitTime > 0) Sleep(waitTime);
	};
};