#include <DxLib.h>
#include"Leaf.h"

Leaf::Leaf()
{

}

Leaf::~Leaf()
{

}

int Leaf::LeafInit()
{
	return TRUE;
}

int Leaf::LeafUpdate(float delta_second)
{
	return TRUE;
}

void Leaf::LeafDraw()const
{
	DrawString(0, 600, "wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww", GetColor(0, 255, 0), TRUE);
}