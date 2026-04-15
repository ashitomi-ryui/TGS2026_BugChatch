#pragma once

class Tree
{
private:
	int x;
	int y;
public:
	Tree();
	~Tree();
public:
	int TreeInit();
	void TreeDraw()const;
	int TreeUpdate();
};