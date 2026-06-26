#pragma once

#include"SceneType.h"
#include"../Utilitys/Math.h"

#define D_TIME_LIMIT	(60.0f)

class InGame
{
private:
	struct Icon
	{
		int cicada;
		int dragonfly;
		int grasshopper;
	};

	int get[3];
	float timer;
	int timeStep;

	int BGM;
	int whistleSE;

	static int groundImage;
	static int productionImage[6];

	int countSE;
	int startSE;
	int FinishSE;

	int changeProduction;	// ƒV[ƒ“Ø‘Ö‰‰o
	float shiita;

	float animTime;
	int animCount;

public:
	InGame();
	~InGame();

public:
	int Init();
	eSceneType Update(float delta_second);
	void Draw() const;
};
