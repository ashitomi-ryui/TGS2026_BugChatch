#pragma once

#include"SceneType.h"
#include"../Utilitys/Input.h"

class Ranking
{
private:

public:
	Ranking();
	~Ranking();
public:
	int Init();
	eSceneType Update(float delta_second);
	void Draw()const;
};