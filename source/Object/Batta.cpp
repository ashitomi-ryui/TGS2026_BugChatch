#include"../Utilitys/Math.h"

#include "Math.h"
#include "DxLib.h" 

Vector2D Batta;
float time = 0;
float time2 = 1;
int count = 0;

void BattaInit(void)
{
	Batta.x = 100.0f;
	Batta.y = 580.0f;
}

void BattaUpdate(float delta_second)
{
	static int i = 1;
	static int j = 1;

	time += delta_second;
	time2 += delta_second;

	Batta.x += i;
	if (Batta.x > 400)
	{
		i = -1;
	}
	if (Batta.x < 50)
	{
		i = 1;
	}
	
	/*if ((int)time2 % 5 == 0)
	{
		count = 1;
	}*/

	/*Batta.y -= j;*/

	/*switch (count)
	{
	case 0:
	
		break;
	case 1:
		if (Batta.y > 400)
		{
			Batta.y *=1.1 ;
		}
		if (Batta.y < 400)
		{
			count = 0;
		}
		break;
	}*/

	

	/*if (Batta.y > 0)
	{
		
	}*/

	

	/*if (Batta.y > 670)
	{
		Batta.y -= 1.0f;
	}*/
}

void BattaDraw(void)
{
	
	DrawCircle(Batta.x, Batta.y, 20, GetColor(255, 0, 255),TRUE);
	DrawFormatString(100, 100, GetColor(255, 255, 255), "%f", time);
}