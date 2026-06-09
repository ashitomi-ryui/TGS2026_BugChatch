#pragma once

#include"SceneType.h"
#include"../Utilitys/Input.h"
#include"../Object/Bug/Bug.h"
#include"../Object/Bug/Cicada.h"
#include"../Object/Bug/Dragonfly.h"
#include"../Object/Bug/Grasshopper.h"

#define DISPLAY_LIMIT (4)

class Result
{
private:
	int title_not_pressed;
	int title_pressed;
	int ranking_not_pressed;
	int ranking_pressed;
	int back_ground;
	int number;
	int numbers[10];
	int select_x;
	int pressed;
	float time;
	float time_rug;
private:
	struct point
	{
		int point[DISPLAY_LIMIT];
		int size[DISPLAY_LIMIT];
	};
	static int divisor[DISPLAY_LIMIT];
	static int display[DISPLAY_LIMIT][DISPLAY_LIMIT];
	point p;

public:
	Result();
	~Result();
public:
	int Init();
	eSceneType Update(float delta_second);
	void Draw()const;
};


