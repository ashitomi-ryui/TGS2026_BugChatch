#pragma once

#include"SceneType.h"
#include"../Utilitys/Math.h"

int InGameInit(void);
eSceneType InGameUpdate(float delta_second);
void InGameDraw(void);
Vector2D GetRingLocation();
float GetPlayerMaxSpeed();
Vector2D GetPlayerLocation();
void PlayerLocationMove(Vector2D vector);