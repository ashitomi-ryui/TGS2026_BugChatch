#include "Batta.h"
#include "bug.h"
#include "../Utilitys/Camera.h"
#include "DxLib.h" 


Vector2D Batta::batta = { 100.0f,580.0f };
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

void Batta::BattaInit(void)
{
	
}

void Batta::BattaUpdate(float delta_second)
{
	BattaDestroy = TRUE;

	static float vx = 0.0f;
	static float vy = 0.0f;
	static float Watitime = 0.0f;

	static bool Groundy = TRUE;
	static bool UpMove = FALSE;      // 上昇中かどうか
	static float JumpTopY = 0.0f;    // 今回のジャンプで止まるY座標

	static bool TopStop = FALSE;     // 頂点で停止中
	static float TopStopTimer = 0.0f;

	time += delta_second;

	battacount = battascore->GetBattaScore() % 2;
	now_batta = battascore->GetBattaScore();

	if (now_batta - old_batta > 0)
	{
		batta = { -100.0f, 100.0f };

		vx = 0.0f;
		vy = 0.0f;
		Watitime = 0.0f;
		Groundy = TRUE;
		UpMove = FALSE;
		TopStop = FALSE;
		TopStopTimer = 0.0f;

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
				batta = { 100.0f, 580.0f };
				battaspawn = 1;
			}

			if (Groundy == TRUE)
			{
				batta.y = groundyY;
				vy = 0.0f;
				vx = 0.0f;

				Watitime += delta_second;

				//1.5秒おきに動く
				if (Watitime > 1.5f)
				{
					Watitime = 0.0f;
					Groundy = FALSE;
					UpMove = TRUE;
					TopStop = FALSE;
					TopStopTimer = 0.0f;

					//50％の確率で左右のどちらかに行く
					if (rand() % 2 == 0)
					{
						vx = 10.0f;
					}
					else
					{
						vx = -10.0f;
					}

					// 下の段用のランダムな頂点
					JumpTopY = (float)(500 + rand() % 120);   // 500～619
					vy = -8.0f;
				}
			}
			else
			{
				// 上昇中
				if (UpMove == TRUE)
				{
					batta.x += vx;
					batta.y += vy;

					// 上に向かっている時
					if (vy < 0.0f)
					{
						if (batta.y <= JumpTopY)
						{
							batta.y = JumpTopY;
							UpMove = FALSE;
							TopStop = TRUE;
							TopStopTimer = 0.0f;
							vx = 0.0f;
							vy = 0.0f;
						}
					}
					// 下に向かっている時
					else if (vy > 0.0f)
					{
						if (batta.y >= JumpTopY)
						{
							batta.y = JumpTopY;
							UpMove = FALSE;
							TopStop = TRUE;
							TopStopTimer = 0.0f;
							vx = 0.0f;
							vy = 0.0f;
						}
					}
				}
				// 頂点で停止中
				else if (TopStop == TRUE)
				{
						vx = 0.0f;
						vy = 0.0f;
					TopStopTimer += delta_second;

					
					batta.y = JumpTopY;   // 固定

					if (TopStopTimer >= 1.5f)
					{
						TopStop = FALSE;
						TopStopTimer = 0.0f;   
						// 次のジャンプ
						UpMove = TRUE;

						if (rand() % 2 == 0)
						{
							vx = 10.0f;
						}
						else
						{
							vx = -10.0f;
						}
						// たまに下がる
						if (rand() % 2 == 0)   // 2回に1回くらい下がる
						{
							JumpTopY = batta.y + (70 + rand() % 90);   // 70～159下がる
						}
						else
						{
							JumpTopY = batta.y - (70 + rand() % 90);   // 70～159上がる
						}

						// 上に行きすぎ防止
						if (JumpTopY < 50.0f)
						{
							JumpTopY = 50.0f;
						}

						// 下に行きすぎ防止
						if (JumpTopY > 650.0f)
						{
							JumpTopY = 650.0f;
						}
						// 目標が今より下なら落ちる、上ならジャンプ
						if (JumpTopY > batta.y)
						{
							vy = 15.0f;    // 下へ
						}
						else
						{
							vy = -17.0f;   // 上へ
						}
					}
				}
				vx *= 0.995f;
			}

			if (batta.x < 20.0f)
			{
				batta.x = 20.0f;
			}
			if (batta.x > 650.0f)
			{
				batta.x = 650.0f;
			}
			break;

		case 1:
			groundyY = 200.0f;

			if (battaspawn == 1)
			{
				batta = { 350.0f, 200.0f };
				battaspawn = 0;
			}

			if (Groundy == TRUE)
			{
				batta.y = groundyY;
				vy = 0.0f;
				vx = 0.0f;

				Watitime += delta_second;

				//1.5秒おきに動く
				if (Watitime > 1.5f)
				{
					Watitime = 0.0f;
					Groundy = FALSE;
					UpMove = TRUE;
					TopStop = FALSE;
					TopStopTimer = 0.0f;
					//50%の確率で左右のどちらかに行くに行く
					if (rand() % 2 == 0)
					{
						vx = 5.0f;
					}
					else
					{
						vx = -5.0f;
					}

					// 上の段用のランダムな頂点
					JumpTopY = (float)(50 + rand() % 100);   // 50～149
					vy = -8.0f;
				}
			}
			else
			{
				/*Batta.x += vx;*/

				// 上昇中
				if (UpMove == TRUE)
				{
					batta.x += vx;
					batta.y += vy;

					// 上に向かっている時
					if (vy < 0.0f)
					{
						if (batta.y <= JumpTopY)
						{
							batta.y = JumpTopY;
							UpMove = FALSE;
							TopStop = TRUE;
							TopStopTimer = 0.0f;
							vx = 0.0f;
							vy = 0.0f;
						}
					}
					// 下に向かっている時
					else if (vy > 0.0f)
					{
						if (batta.y >= JumpTopY)
						{
							batta.y = JumpTopY;
							UpMove = FALSE;
							TopStop = TRUE;
							TopStopTimer = 0.0f;
							vx = 0.0f;
							vy = 0.0f;
						}
					}
				}
				// 頂点で停止中
				else if (TopStop == TRUE)
				{
					vx = 0.0f;
					TopStopTimer += delta_second;

					batta.y = JumpTopY;   // その場で固定
					if (TopStopTimer >= 1.3f)
					{
						TopStop = FALSE;
						TopStopTimer = 0.0f;
						UpMove = TRUE;

						if (rand() % 2 == 0)
						{
							vx = 5.0f;
						}
						else
						{
							vx = -5.0f;
						}
						
						// たまに下がる
						if (rand() % 3 == 0)   // 3回に1回くらい下がる
						{
							JumpTopY = batta.y + ( 100+ rand() % 40);   // 100～139下がる
						}
						else
						{
							JumpTopY = batta.y - (40 + rand() % 40);   // 40～79上がる
						}

						// 上に行きすぎ防止
						if (JumpTopY < 30.0f)
						{
							JumpTopY = 30.0f;
						}

						// 下に行きすぎ防止
						if (JumpTopY > 650.0f)
						{
							JumpTopY = 650.0f;
						}
						// 目標が今より下なら落ちる、上ならジャンプ
						if (JumpTopY > batta.y)
						{
							vy = 15.0f;    // 下へ
						}
						else
						{
							vy = -17.0f;   // 上へ
						}

						if (JumpTopY < 30.0f)
						{
							JumpTopY = 30.0f;
						}
							// 今いる位置から少しだけ上へジャンプ
							//JumpTopY = Batta.y - (20.0f + rand() % 30);  // 20～49 上へ
		
					}
				}
				

				vx *= 0.995f;

			}

			if (batta.x < 330.0f)
			{
				batta.x = 330.0f;
			}
			if (batta.x > 1200.0f)
			{
				batta.x = 1200.0f;
			}
			break;
		}
	}
}

void Batta::BattaDraw(void)
{
	if (BattaDestroy == TRUE)
	{
		Camera::DrawCircleW(batta, 20, GetColor(255, 0, 255));
		DrawFormatString(100, 100, GetColor(255, 255, 255), "%f", time);
	}
}

Vector2D* Batta::BattaLocation(void)
{
	return &batta;
}

void Batta::SetBatta(class Bug* p)
{
	battascore = p;
}