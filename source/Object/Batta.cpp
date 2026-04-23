#include "Batta.h"
#include "bug.h"
#include "Math.h"
#include "DxLib.h" 

Vector2D Batta;
Bug* battascore;
float time = 0;
float time1 = 0;

int count = 0;
bool BattaDestroy;

int now_batta;
int old_batta;
int battacount = 0;
int battaspawn = 0;
float groundyY = 0;

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

	static bool Groundy = TRUE;

	time += delta_second;

	battacount = battascore->GetBattaScore() % 2;
	now_batta = battascore->GetBattaScore();

	if (now_batta - old_batta > 0)
	{
		Batta = { -100.0f,100.0f };
		if (count == 0)
		{
			BattaDestroy = FALSE;
			time1 = 0;
			count = 1;
		}

		time1 += delta_second;
		if (time1 >= 1.0f)
		{
			BattaDestroy = TRUE;
			old_batta = now_batta;
			count = 0;
		}
	}
	else
	{
		switch (battacount)
		{
		case 0:
			groundyY = 690.0f;
			if (battaspawn == 0)
			{
				Batta = { 100.0f,580.0f };
				battaspawn = 1;
			}
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
			break;
		case 1:
			groundyY = 200.0f;
			if (battaspawn == 1)
			{
				Batta = { 300.0f,200.0f };
				battaspawn = 0;
			}
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
			if (Batta.x < 300.0f)
			{
				Batta.x = 300.0f;
			}
			if (Batta.x > 1200.0f)
			{
				Batta.x = 1200.0f;
			}
			break;
		}
	}
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

void SetBatta(class Bug* p)
{
	battascore = p;
}