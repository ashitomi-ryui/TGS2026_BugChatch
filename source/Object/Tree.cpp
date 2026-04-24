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
	
}

Tree::~Tree()
{

}

int Tree::Init()
{
	tree = LoadGraph("images/tree.PNG");

	if (tree == -1)
	{
		return FALSE;
	}

	for (int i = 0; i < 10; i++)
	{
		location[i] = { 100.0f + i * 200.0f, 100.0f + (float)(i % 3) * 400.0f };
	}
	return TRUE;
}

int Tree::Update()
{
	return TRUE;
}

void Tree::Draw()const
{
	//Camera::DrawBoxW({ 200.0f, 100.0f }, { 300.0f, 300.0f }, GetColor(210, 160, 100));
	//Camera::DrawBoxW({ 700.0f, 400.0f }, { 800.0f, 800.0f }, GetColor(210, 160, 100));
	for (int i = 0; i < 10; i++)
	{
		Camera::DrawGraphW(location[i], 0.25, 0.0, tree);
	}
}