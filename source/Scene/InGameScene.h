#pragma once

#include"SceneType.h"
#include"../Utilitys/Math.h"

int InGameInit(void);
eSceneType InGameUpdate(float delta_second);
void InGameDraw(void);


struct Icon
{
	int cicada;
	int dragonfly;
	int grasshopper;
};