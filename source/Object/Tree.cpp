#include<DxLib.h>
#include"Tree.h"

//void DrawTree(void)
//{
//	DrawBox(100, 100, 200, 300, GetColor(210, 160, 100), TRUE);
//	DrawBox(700, 400, 800, 800, GetColor(210, 160, 100), TRUE);
//}

Tree::Tree()
{

}

Tree::~Tree()
{

}

int Tree::TreeUpdate()
{
	return TRUE;
}

void Tree::TreeDraw()const
{
	DrawBox(200, 100, 300, 300, GetColor(210, 160, 100), TRUE);
	DrawBox(700, 400, 800, 800, GetColor(210, 160, 100), TRUE);
}