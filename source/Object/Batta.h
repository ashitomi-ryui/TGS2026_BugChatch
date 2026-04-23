#pragma once

#include"../Utilitys/Math.h"


void BattaInit(void);
void BattaUpdate(float delta_second);
void BattaDraw(void);
Vector2D* BattaLocation(void);
void SetBatta(class Bug* p);