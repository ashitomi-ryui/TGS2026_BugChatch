#pragma once

#include"SceneType.h"
#include"../Utilitys/Input.h"

class Title
{
private:
	static int Titlebgm;
	static int ChoiceSE;
	static int DecisionSE;
private:
	static int back_ground;
	static int title_logo;
	static int select_x;
	static int select_y;
	static int pressed;
	static float time;
	static float time_rug;
	float shiita;
private:
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
public:
	Title();
	~Title();
public:
	int Init();
	void Draw()const;
	eSceneType Update(float delta_second);
};