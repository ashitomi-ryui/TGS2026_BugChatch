#pragma once

#include "../Utilitys/Math.h"

void SemiInit(void);
void SemiUpdate(float delta_second);
void SemiDraw(void);
void SetSemi(class Bug* p);
Vector2D* SemiLocation(void);
