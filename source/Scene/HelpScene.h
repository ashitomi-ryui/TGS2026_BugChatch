#pragma once

#include"SceneType.h"
#include"../Utilitys/Input.h"

class Help
{
private:
	int back_ground;
	int start_pressed;
	int start_not_pressed;
	int title_pressed;
	int title_not_pressed;
	int controller;
	int select_y;
	int pressed;
	float time;
	float time_rug;
public:
	Help();
	~Help();
public:
	int Init();
	void Draw()const;
	eSceneType Update(float delta_second);
};