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
	int select_x;
	int pressed;
	float time;
	float time_rug;
private:
	int ChoiceSE3;
	int DecisionSE3;
	int ResultBGM;
	int back_ground;
	int bugIcon[3];

	struct b
	{
		int newtral;
		int select;
		int pressed;
	};
	struct rank_b
	{
		int newtral;
		int select;
		int pressed;
	};
	b b;
	rank_b rank_b;
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


