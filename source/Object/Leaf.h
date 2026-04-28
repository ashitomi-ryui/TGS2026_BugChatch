#pragma once

#include"../Utilitys/Math.h"

class Leaf
{
private:
	Vector2D location[10];
public:
	Leaf();
	~Leaf();
public:
	int Init();
	int Update(float delta_second);
	void Draw()const;
};
