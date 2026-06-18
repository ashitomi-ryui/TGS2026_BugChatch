#pragma once

#include"SceneType.h"
#include"../Object/Cage.h"
#include"../Utilitys/Input.h"
#include"../Object/Bug/Bug.h"
#include"../Object/Bug/Cicada.h"
#include"../Object/Bug/Dragonfly.h"
#include"../Object/Bug/Grasshopper.h"

#define DISPLAY_LIMIT (4)

class Result
{
private:
	int buttonSelect;
	bool pressed;
private:
	int ChoiceSE3;
	int DecisionSE3;
	int ResultBGM;
	int back_ground;
	int bugIcon[3];

	static int netImage;
	static int buttonImage;

private:
	static struct point
	{
		int point[DISPLAY_LIMIT];
		int size[DISPLAY_LIMIT];
	};
	static int divisor[DISPLAY_LIMIT];
	static int display[DISPLAY_LIMIT][DISPLAY_LIMIT];
	static point p;

	bool isRankIn;
	float colorHue;	// 赤0～緑1～青2～赤3

	float timer;

	float shiita;
	int changeProduction;	// シーン切替演出

public:
	Result();
	~Result();
public:
	int Init();
	eSceneType Update(float delta_second);
	void Draw()const;

	/// <summary>
	/// ポイントを追加する
	/// </summary>
	/// <param name="type">虫の種類</param>
	static void AddPoint(Cage::Type type);
};


