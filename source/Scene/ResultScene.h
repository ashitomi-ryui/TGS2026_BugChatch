#pragma once

#include"SceneType.h"
#include"../Utilitys/Input.h"

class Result
{
private:
	int title_not_pressed;
	int title_pressed;
	int ranking_not_pressed;
	int ranking_pressed;
	int select_x;
	int pressed;
	float time;
	float time_rug;
public:
	Result();
	~Result();
public:
	int Init();
	eSceneType Update(float delta_second);
	void Draw()const;
};


