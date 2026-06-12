#pragma once

#include"SceneType.h"
#include"../Utilitys/Input.h"

#define MAX_RANK (6)

class Ranking
{
private:
	int select_x;
	int pressed;
	float time;
	float time_rug;
private:
	int ranking[MAX_RANK];
private:
	int RankingBGM2;
	int Choicebgm2;
	int DecisionSE2;
	int back_ground;
	struct b
	{
		int newtral;
		int select;
		int pressed;
	};
	b b;
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