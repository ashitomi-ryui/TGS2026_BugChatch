#pragma once

#include"../Utilitys/Math.h"

class Shadow
{
private:
	Vector2D m_location;
	static int m_image;

	bool m_isDisplay;
	bool m_isBack;

public:
	Shadow();
	~Shadow();
public:
	static void Init();
	void Set(Vector2D location, float height, bool isDisplay, bool isBack);
	void Draw()const;
	void DrawOnTheBack() const;		// ”w–Ê‚É•`‰æ
};
