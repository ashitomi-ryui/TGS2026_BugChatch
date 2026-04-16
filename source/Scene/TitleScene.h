#pragma once

#include"SceneType.h"

int TitleInit(void);
eSceneType TitleUpdate(float delta_second);
void TitleDraw(void);

class Title
{
private:
	int x;
	int y;
	int start_pressed;
	int start_not_pressed;
public:
	Title();
	~Title();
public:
	int TitleInit();
	void TitleDraw()const;
	eSceneType TitleUpdate(float delta_second);
};