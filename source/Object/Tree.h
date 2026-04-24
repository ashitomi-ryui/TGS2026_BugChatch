#pragma once

#include"../Utilitys/Math.h"

class Tree
{
private:
	Vector2D location[10];
    int tree;
public:
	Tree();
	~Tree();
public:
	int Init();
	void Draw()const;
	int Update();
};