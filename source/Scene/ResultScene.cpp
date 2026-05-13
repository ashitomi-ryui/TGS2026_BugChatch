#include"ResultScene.h"
#include"../Utilitys/Input.h"
#include<DxLib.h>

Result::Result()
{

}

Result::~Result()
{

}

int Result::Init()
{
	title_not_pressed = LoadGraph("assets/images/Result/title_off.png");
	title_pressed = LoadGraph("assets/images/Result/title_on.png");
	return TRUE;
}

eSceneType Result::Update(float delta_second)
{
	return eResult;
}

void Result::Draw()const
{
	DrawRotaGraph(600, 600, 1.0, 0.0, title_not_pressed, TRUE);
}