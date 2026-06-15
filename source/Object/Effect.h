#pragma once

#include"../Utilitys/Math.h"

#define D_EFFECT_MAX		(20)

class Effect
{
private:
	Vector2D m_location;
	static int m_images[4];
	unsigned int m_color;

	float m_animTime;
	int m_animCount;

	bool m_isDisplay;

public:
	Effect();
	~Effect();
public:
	static void Init();
	void Set(Vector2D location, unsigned int color);
	void Update(float delta);
	void Draw()const;

public:
	void SetHidden();
	bool GetIsDisplay()const;
};
