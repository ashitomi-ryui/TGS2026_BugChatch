#pragma once

#include"SceneType.h"
#include"../Utilitys/Input.h"

class Help
{
private:
	int buttonSelect;
	bool pressed;
private:
	int ChoiceSE2;
	int DecisionSE2;
	int HelpBGM;
	int back_ground;
	int controller;

	static int netImage;
	static int buttonImage;

	float shiita;
	int changeProduction;	// ƒV[ƒ“Ø‘Ö‰‰o

public:
	Help();
	~Help();
public:
	int Init();
	void Draw()const;
	eSceneType Update(float delta_second);
};