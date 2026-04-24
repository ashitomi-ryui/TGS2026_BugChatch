#include<DxLib.h>
#include"Tree.h"
#include"../Utilitys/Camera.h"

//void DrawTree(void)
//{
//	DrawBox(100, 100, 200, 300, GetColor(210, 160, 100), TRUE);
//	DrawBox(700, 400, 800, 800, GetColor(210, 160, 100), TRUE);
//}

Tree::Tree()
{
	tree = LoadGraph("images/tree.PNG");
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
	//Camera::DrawBoxW({ 200.0f, 100.0f }, { 300.0f, 300.0f }, GetColor(210, 160, 100));
	//Camera::DrawBoxW({ 700.0f, 400.0f }, { 800.0f, 800.0f }, GetColor(210, 160, 100));
	Camera::DrawGraphW({ 200.0f,100.0f }, 1.0, 0.0, tree);
}