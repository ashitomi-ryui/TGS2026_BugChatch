#pragma once

#include"SceneType.h"
#include"../Utilitys/Input.h"

class Help
{
private:
	int buttonSelect;
	bool pressed;
private:
	int ChoiceSE;
	int DecisionSE;
	int HelpBGM;
	int back_ground;
	int controller[2];

	static int netImage;
	static int productionImage[2];
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