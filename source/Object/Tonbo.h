#pragma once
#ifndef WEIRD_MOTION_H
#define WEIRD_MOTION_H

void TonboMotion(double t, int centerX, int centerY, int* x, int* y);
void TonboDraw(void);
void TonboUpdate(float delta_second);
void TonboInit(void);
int TonboLocation(void);
#endif