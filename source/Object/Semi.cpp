#include"../Utilitys/Math.h"
#include"Semi.h"
#include "Bug.h"
#include "Math.h"
#include "../Utilitys/Camera.h"
#include "DxLib.h" 

Vector2D semi;
Bug* semiscore;
float time3 = 0;
float time4 = 0.0f;
int count2 = 1;
int Respawn = 0;
int fukkatu = 0;
bool SemiDestroy;
static int semicount;
int now_semi[10];
int old_semi[10];

void Semi::SemiInit(void)
{
	semi.x = 20.0f;
	semi.y = 500.0f;
	SemiDestroy = TRUE;
}

void Semi::SemiUpdate(float delta_second)
{
	static int Reverse = 1;
	static bool isStop = false;    // 今止まっているか
	static float StopTimer = 0.0f; // 止まっている時間
	const float speed = 1000.0f; //速度

	//セミのスコアを2で余り算する


	//現在のセミのスコアをいれる
	for (int i = 0; i < 10; i++)
	{
		semicount = semiscore->GetSemiScore(i) % 2;
		now_semi[i] = semiscore->GetSemiScore(i);





		//今のスコアと昔のスコアの差が0より大きかったら入る
		if (now_semi - old_semi > 0)
		{
			//座標を画面外へ移動
			semi = { -100.0f,100.0f };
			if (fukkatu == 0)
			{
				//セミの描画を停止
				SemiDestroy = FALSE;
				time3 = 0;  //リスポーン時間のカウントの数値を初期化
				fukkatu = 1;
			}
			//リスポーン時間加算
			time3 += delta_second;
			//一秒立ったら再描画
			if (time3 >= 1.0f)
			{
				SemiDestroy = TRUE;
				old_semi[i] = now_semi[i];   //昔のスコアに現在スコアを代入
				fukkatu = 0;
			}
		}
		else
		{
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
			switch (semicount)
			{
			case 0:
				if (Respawn == 0)
				{
					//リスポーン座標設定
					semi = { 20.0f,500.0f };
					Respawn = 1;
				}
				semi.x += Reverse * speed * delta_second;
				if (semi.x >= 677)
				{
					semi.x = 677;
					isStop = true;
					StopTimer = 0.0f;
				}

				if (semi.x <= 20)
				{
					semi.x = 20;
					isStop = true;
					StopTimer = 0.0f;
				}
				break;
			case 1:
				if (Respawn == 1)
				{
					//リスポーン座標設定
					semi = { 600.0f,200.0f };
					Respawn = 0;
				}
				semi.x += Reverse * speed * delta_second;
				if (semi.x >= 1200)
				{
					semi.x = 1200;
					isStop = true;
					StopTimer = 0.0f;
				}

				if (semi.x <= 600)
				{
					semi.x = 600;
					isStop = true;
					StopTimer = 0.0f;
				}
				break;
			}
		}
	}

}

void Semi::SemiDraw(void)
{
	if (SemiDestroy == TRUE)
	{
		Camera::DrawCircleW(semi, 20, GetColor(0, 0, 255));
	}

	/*DrawFormatString(200, 700, GetColor(255, 255, 255), "%f", time3);
	DrawFormatString(700, 100, GetColor(255, 255, 255), "%d", now_semi);
	DrawFormatString(800, 100, GetColor(255, 255, 255), "%d", old_semi);
	DrawFormatString(200, 400, GetColor(255, 255, 255), "%f,%f", Semi.x,Semi.y);*/
}

Vector2D* Semi::SemiLocation(void)
{
	return &semi;
}

void Semi::SetSemi(class Bug* p)
{
	semiscore = p;
}