#pragma once

#include"../Utilitys/Math.h"

class Shadow
{
private:
	Vector2D m_location;
	static int m_image;

	bool m_isDisplay;

public:
	Shadow();
	~Shadow();
public:
	static void Init();
	void Set(Vector2D location, float height, bool isDisplay);
	void Draw()const;
};
