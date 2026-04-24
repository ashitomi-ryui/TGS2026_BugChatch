#pragma once

#include "../Utilitys/Math.h"

#ifndef WEIRD_MOTION_H
#define WEIRD_MOTION_H

class Tonbo
{
public:

void TonboMotion(double t, int centerX, int centerY, int* x, int* y);
void TonboDraw(void);
void TonboUpdate(float delta_second);
void TonboInit(void);
void SetTonbo(class Bug* p);
Vector2D* TonboLocation(void);
};

#endif