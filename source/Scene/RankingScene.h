#pragma once

#include"SceneType.h"
#include"../Utilitys/Input.h"

#define MAX_RANK (3)

class Ranking
{
private:
	int back_ground2;
	int start_pressed;
	int start_not_pressed;
	int title_pressed;
	int title_not_pressed;
	int back_ground;
	int select_x;
	int pressed;
	float time;
	float time_rug;
private:
	int ranking[MAX_RANK];
public:
	Ranking();
	~Ranking();
public:
	int LoadRankData();
	int CheckRankData(int p_point);
	int SortRankData();
	int AddRankData();
public:
	int Init();
	eSceneType Update(float delta_second);
	void Draw()const;
};