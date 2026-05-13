#pragma once

#include "../Utilitys/Math.h"

#ifndef WEIRD_MOTION_H
#define WEIRD_MOTION_H

class Dragonfly
{
private:
	Vector2D m_location;	// 座標
	bool m_isAppearance;	// 出現フラグ

public:
	Dragonfly();
	~Dragonfly();

public:
	void Set(Vector2D location);

private:
	void TonboMotion(double t, int centerX, int centerY, int* x, int* y);
	void TonboDraw(void);
	void TonboUpdate(float delta_second);
	void TonboInit(void);
	void SetTonbo(class Bug* p);
	Vector2D* TonboLocation(void);
};

#endif