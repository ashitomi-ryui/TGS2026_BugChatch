#include"../Utilitys/Math.h"
#include "DxLib.h" 

Vector2D Batta;

void BattaInit(void)
{
	Batta.x = 100.0f;
	Batta.y = 580.0f;
}

void BattaUpdate(void)
{
	static int i = 1;
	static int j = 1;

	Batta.x += i;

	/*Batta.y -= j;*/

	if (Batta.x > 400)
	{
		i = -1;
	}

	/*if (Batta.y > 0)
	{
		
	}*/

	if (Batta.x < 50)
	{
		i = 1;
	}

	/*if (Batta.y > 670)
	{
		Batta.y -= 1.0f;
	}*/
}

void BattaDraw(void)
{
	DrawCircle(Batta.x, Batta.y, 20, GetColor(255, 0, 255),TRUE);
}