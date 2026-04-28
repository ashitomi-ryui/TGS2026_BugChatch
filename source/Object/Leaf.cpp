#include <DxLib.h>
#include"Leaf.h"

Leaf::Leaf()
{

}

Leaf::~Leaf()
{

}

int Leaf::Init()
{
	for (int i = 0; i < 10; i++)
	{
		location[i] = { 150.0f + i * 200.0f, 150.0f + (float)(i % 3) * 400.0f };
	}
	return TRUE;
}

int Leaf::Update(float delta_second)
{
	return TRUE;
}

void Leaf::Draw()const
{
	DrawString(0, 600, "wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww", GetColor(0, 255, 0), TRUE);
}