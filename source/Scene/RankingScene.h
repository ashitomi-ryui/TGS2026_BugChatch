#pragma once

#include"SceneType.h"
#include"../Utilitys/Input.h"

#define MAX_RANK (6)

class Ranking
{
private:
	int buttonSelect;
	bool pressed;
private:
	static int ranking[MAX_RANK];
	static int new_data;
	static int new_rank;
	bool check_blend;
	float blend;
private:
	int RankingBGM;
	int ChoiceSE;
	int DecisionSE;
	int back_ground;
   

	static int netImage;
	static int productionImage[2];
	static int buttonImage;

	float shiita;
	int changeProduction;	// ƒV[ƒ“Ø‘Ö‰‰o

public:
	Ranking();
	~Ranking();
public:
	static int LoadRankData();
	static int CheckRankData(int p_point);
	static int SortRankData();
	static int AddRankData();
public:
	int Init();
	eSceneType Update(float delta_second);
	void Draw()const;
};