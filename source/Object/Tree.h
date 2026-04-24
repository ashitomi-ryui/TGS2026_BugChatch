#pragma once

#include"../Utilitys/Math.h"

#define D_TREE_WIDTH	(70)
#define D_TREE_HEIGHT	(150)

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