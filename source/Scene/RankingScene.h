#pragma once

#include"SceneType.h"
#include"../Utilitys/Input.h"

class Ranking
{
private:
	int ranking;
	int start_pressed;
	int start_not_pressed;
	int title_pressed;
	int title_not_pressed;
	int back_ground;
	int select_x;
	int pressed;
	float time;
	float time_rug;
public:
	Ranking();
	~Ranking();
public:
	int Init();
	eSceneType Update(float delta_second);
	void Draw()const;
};