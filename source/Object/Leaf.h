#pragma once

#include"../Utilitys/Math.h"

class Leaf
{
private:
	Vector2D location;
public:
	Leaf();
	~Leaf();
public:
	int LeafInit();
	void LeafDraw()const;
	int LeafUpdate(float delta_second);
};
