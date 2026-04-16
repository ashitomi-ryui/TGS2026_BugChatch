#pragma once

#include"SceneType.h"

//int TitleInit(void);
//eSceneType TitleUpdate(float delta_second);
//void TitleDraw(void);

class Title
{
private:
	int x;
	int y;
	int start_pressed;
	int start_not_pressed;
	int help_pressed;
	int help_not_pressed;
	int end_pressed;
	int end_not_pressed;
	int select;
	int pressed;
	float time;
	float time_rug;
public:
	Title();
	~Title();
public:
	int TitleInit();
	void TitleDraw()const;
	eSceneType TitleUpdate(float delta_second);
};