#include"../Utilitys/Math.h"

#include "Math.h"
#include "DxLib.h" 

Vector2D Semi;
float time3 = 0;
float time4 = 0.0f;
int count2 = 0;

void SemiInit(void)
{
	Semi.x = 640.0f;
	Semi.y = 500.0f;
}

void SemiUpdate(float delta_second)
{
	static int i = 1;
	static int j = 1;
	static int Reverse = 1;
	static bool isStop = false;    // ¡Ž~‚Ü‚Á‚Ä‚¢‚é‚©
	static float StopTimer = 0.0f; // Ž~‚Ü‚Á‚Ä‚¢‚éŽžŠÔ
	const float speed = 500.0f; //‘¬“x
	time3 += delta_second;
	time4 += delta_second;

	
	if (isStop)
	{
		StopTimer += delta_second;

		if (StopTimer >= 2.0f)
		{
			isStop = false;
			StopTimer = 0.0f;

			Reverse *= -1;
		}
		return;
	}

	

	Semi.x += Reverse * speed * delta_second;
	if (Semi.x >= 1250)
	{
		Semi.x = 1250;
		isStop = true;
		StopTimer = 0.0f;
	}
		
	if (Semi.x <= 20)
	{
		Semi.x = 20;
		isStop = true;
		StopTimer = 0.0f;
		//i = 1;
	}
}

void SemiDraw(void)
{

	DrawCircle(Semi.x, Semi.y, 20, GetColor(0, 0, 255), TRUE);
	DrawFormatString(200, 100, GetColor(255, 255, 255), "%f", time3);
}