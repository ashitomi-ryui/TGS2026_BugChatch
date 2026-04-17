#include "Batta.h"
#include "bug.h"
#include "Math.h"
#include "DxLib.h" 

Vector2D Batta;
float time = 0;
float time2 = 1;

int count = 0;
bool BattaDestroy;

void BattaInit(void)
{
	Batta.x = 100.0f;
	Batta.y = 580.0f;
}

void BattaUpdate(float delta_second)
{
	BattaDestroy = TRUE;
	static float vx = 0.0f;
	static float vy = 0.0f;
	static float Watitime = 0.0f;
	float Gravity = 0.45f;
	float groundyY = 690.0f;
	static bool Groundy = TRUE;

	time += delta_second;
	time2 += delta_second;


	if (Groundy == TRUE)
	{
		Batta.y = groundyY;
		vy = 0.0f;
		vx = 0.0f;

		Watitime += delta_second;

		if (Watitime > 1.5f)
		{
			Watitime = 0.0f;
			Groundy = FALSE;

			if (rand() % 2 == 0)
			{
				vx = 5.0f;
			}
			else
			{
				vx = -5.0f;
			}
			
			vy = -15.0f;
		}

	}
	else
	{
		vy += Gravity;

		vx *= 0.995f;

		Batta.x += vx;
		Batta.y += vy;
		if (Batta.y >= groundyY)
		{
			Batta.y = groundyY;
			vy = 0.0f;
			vx = 0.0f;
			Groundy = TRUE;
		}
	}
	if (Batta.x < 20.0f)
	{
		Batta.x = 20.0f;
	}
	if (Batta.x > 650.0f)
	{
		Batta.x = 650.0f;
	}

	/*if (GetBattaScore() == 1)
	{
		BattaDestroy = FALSE;
	}

	if (Batta.y >= groundyY)
	{
		Batta.y = groundyY;
		vy = 0;

	

		
	}

	vy += Gravity;
	Batta.x += vx;
	Batta.y += vy;
	if (Batta.x > 720 || Batta.x < 300)
	{
		vx *= -10;
	}*/
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
	if (BattaDestroy == TRUE)
	{
		DrawCircle(Batta.x, Batta.y, 20, GetColor(255, 0, 255), TRUE);
		DrawFormatString(100, 100, GetColor(255, 255, 255), "%f", time);
	}
}
	

Vector2D* BattaLocation(void)
{
	return &Batta;
}