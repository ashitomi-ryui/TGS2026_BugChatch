#pragma once

#include"SceneType.h"
#include"../Utilitys/Input.h"

class Title
{
private:
	static int Titlebgm;
	static int ChoiceSE;
	static int DecisionSE;
	
	static int back_ground;
	static int title_logo;

	static int buttonImage;

	static int netImage;

	static int buttonSelect;	// 0スタート、1ヘルプ、2おわり、3ランキング
	static bool pressed;

	float shiita;
	int changeProduction;	// シーン切替演出

private:
	struct rank_b
	{
		int newtral;
		int select;
		int pressed;
	};
	rank_b rank_b;
public:
	Title();
	~Title();
public:
	int Init();
	void Draw()const;
	eSceneType Update(float delta_second);
};