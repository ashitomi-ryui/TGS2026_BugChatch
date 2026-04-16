#include "Batta.h"

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
	float vx = 0;
	float vy = 0;
	static float Watitime = 0;
	float Gravity = 0.5f;
	float groundyY = 700.0f;
	static int i = 1;
	static int j = 1;

	time += delta_second;
	time2 += delta_second;

	Batta.x += i;
	Batta.y += j;

	if (Batta.y >= groundyY)
	{
		Batta.y = groundyY;
		vy = 0;

		Watitime += delta_second;

		if (Watitime > 1.5f)
		{
			Watitime = 0;

			vx = (rand() % 5 + 2) * (rand() % 2 ? 1 : -1);
			vy = -10.0f;
		}
	}

	vy += Gravity;
	Batta.x += vx;
	Batta.y += vy;
	//if (Batta.x > 720)
	//{
	//	
	//	i = -1;
	//}
	//if (Batta.x < 300)
	//{
	//	
	//	i = 1;
	//}
	//if (Batta.y > 720)
	//{
	//	j = 1;
	//}
	
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

Vector2D* BattaLocation(void)
{
	return &Batta;
}