#pragma once

#include"SceneType.h"
#include"../Utilitys/Input.h"

#define TITLE_WORD (13)

class Title
{
private:
	static int Titlebgm;
	static int ChoiceSE;
	static int DecisionSE;
	static int start_pressed;
	static int start_not_pressed;
	static int help_pressed;
	static int help_not_pressed;
	static int end_pressed;
	static int end_not_pressed;
	static int ranking_pressed;
	static int ranking_not_pressed;
	static int back_ground;
	static int select_x;
	static int select_y;
	static int pressed;
	static float time;
	static float time_rug;

	float shiita;

private:
	static int word1[50];
	static int word2[15];
	static int word3[10];
public:
	Title();
	~Title();
public:
	int Init();
	void Draw()const;
	eSceneType Update(float delta_second);
};