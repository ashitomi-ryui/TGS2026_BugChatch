#pragma once

#include"SceneType.h"
#include"../Utilitys/Input.h"

class Title
{
private:
	int Titlebgm;
	int ChoiceSE;
	int DecisionSE;
	int start_pressed;
	int start_not_pressed;
	int help_pressed;
	int help_not_pressed;
	int end_pressed;
	int end_not_pressed;
	int ranking_pressed;
	int ranking_not_pressed;
	int back_ground;
	int select_x;
	int select_y;
	int pressed;
	float time;
	float time_rug;
public:
	Title();
	~Title();
public:
	int Init();
	void Draw()const;
	eSceneType Update(float delta_second);
};