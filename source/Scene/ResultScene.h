#pragma once

#include"SceneType.h"
#include"../Utilitys/Input.h"
#include"../Object/Bug/Bug.h"
#include"../Object/Bug/Cicada.h"
#include"../Object/Bug/Dragonfly.h"
#include"../Object/Bug/Grasshopper.h"

class Result
{
private:
	int title_not_pressed;
	int title_pressed;
	int ranking_not_pressed;
	int ranking_pressed;
	int result;
	int number;
	int numbers[10];
	int select_x;
	int pressed;
	float time;
	float time_rug;
private:
	int c_count;
	int d_count;
	int g_count;
public:
	Result();
	~Result();
public:
	int Init();
	eSceneType Update(float delta_second);
	void Draw()const;
};


