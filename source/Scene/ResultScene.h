#pragma once

#include"SceneType.h"
#include"../Utilitys/Input.h"

class Result
{
private:
	int title_not_pressed;
	int title_pressed;
public:
	Result();
	~Result();
public:
	int Init();
	eSceneType Update(float delta_second);
	void Draw()const;
};


