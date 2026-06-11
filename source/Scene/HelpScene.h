#pragma once

#include"SceneType.h"
#include"../Utilitys/Input.h"

class Help
{
private:
	int select_x;
	int pressed;
	float time;
	float time_rug;
private:
	int ChoiceSE2;
	int DecisionSE2;
	int HelpBGM;
	int back_ground;
	int controller;
	struct b
	{
		int newtral;
		int select;
		int pressed;
	};
	b b;
public:
	Help();
	~Help();
public:
	int Init();
	void Draw()const;
	eSceneType Update(float delta_second);
};