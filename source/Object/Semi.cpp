#include"../Utilitys/Math.h"
#include"Semi.h"
#include "Bug.h"
#include "Math.h"
#include "DxLib.h" 

Vector2D Semi;
float time3 = 0;
float time4 = 0.0f;
int count2 = 1;
int Respawn = 0;
int fukkatu = 0;
bool SemiDestroy;
static int semicount = 0;
int now_semi = 0;
int old_semi = 0;

void SemiInit(void)
{
	Semi.x = 20.0f;
	Semi.y = 500.0f;
	SemiDestroy = TRUE;
}

void SemiUpdate(float delta_second)
{
	static int i = 1;
	static int j = 1;
	static int Reverse = 1;
	static bool isStop = false;    // ¡Ž~‚Ü‚Á‚Ä‚¢‚é‚©
	static float StopTimer = 0.0f; // Ž~‚Ü‚Á‚Ä‚¢‚éŽžŠÔ
	const float speed = 1000.0f; //‘¬“x
	
	semicount = GetSemiScore() % 2;
	//time3 += delta_second;
	//time4 += delta_second;

	now_semi = GetSemiScore();


	/*switch (semicount)
	{
	case 0:
		if (Respawn == 0)
		{
			Semi = { 20.0f,500.0f };
			Respawn = 1;
		}
		Semi.x += Reverse * speed * delta_second;
		if (Semi.x >= 677)
		{
			Semi.x = 677;
			isStop = true;
			StopTimer = 0.0f;
		}

		if (Semi.x <= 20)
		{
			Semi.x = 20;
			isStop = true;
			StopTimer = 0.0f;
			i = 1;
		}
		
		break;
	case 1:
		if (Respawn == 1)
		{
			Semi = { 600.0f,200.0f };
			Respawn = 0;
		}
		Semi.x += Reverse * speed * delta_second;
		if (Semi.x >= 1200)
		{
			Semi.x = 1200;
			isStop = true;
			StopTimer = 0.0f;
		}

		if (Semi.x <= 600)
		{
			Semi.x = 600;
			isStop = true;
			StopTimer = 0.0f;
			i = 1;
		}
		
		break;
	}*/
	
	if (now_semi-old_semi>0)
	{
		Semi = { -100.0f,100.0f };
		if (fukkatu == 0)
		{
			SemiDestroy = FALSE;
			time3 = 0;
			fukkatu = 1;
		}

		time3 += delta_second;
		if (time3 >= 1.0f)
		{
			SemiDestroy = TRUE;
			old_semi = now_semi;
			fukkatu = 0;
		}
	}
	else
	{
		switch (semicount)
		{
		case 0:
			if (Respawn == 0)
			{
				Semi = { 20.0f,500.0f };
				Respawn = 1;
			}
			Semi.x += Reverse * speed * delta_second;
			if (Semi.x >= 677)
			{
				Semi.x = 677;
				isStop = true;
				StopTimer = 0.0f;
			}

			if (Semi.x <= 20)
			{
				Semi.x = 20;
				isStop = true;
				StopTimer = 0.0f;
				i = 1;
			}

			break;
		case 1:
			if (Respawn == 1)
			{
				Semi = { 600.0f,200.0f };
				Respawn = 0;
			}
			Semi.x += Reverse * speed * delta_second;
			if (Semi.x >= 1200)
			{
				Semi.x = 1200;
				isStop = true;
				StopTimer = 0.0f;
			}

			if (Semi.x <= 600)
			{
				Semi.x = 600;
				isStop = true;
				StopTimer = 0.0f;
				i = 1;
			}

			break;
		}
	}
	

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

	
	

	
}

void SemiDraw(void)
{
	if (SemiDestroy == TRUE)
	{
		DrawCircle(Semi.x, Semi.y, 20, GetColor(0, 0, 255), TRUE);
	}
	
	DrawFormatString(200, 700, GetColor(255, 255, 255), "%f", time3);
	DrawFormatString(700, 100, GetColor(255, 255, 255), "%d", Respawn);
	DrawFormatString(200, 400, GetColor(255, 255, 255), "%f,%f", Semi.x,Semi.y);
}

Vector2D* SemiLocation(void)
{
	return &Semi;
}

void SemiRespawn(float delta_second)
{
	
}