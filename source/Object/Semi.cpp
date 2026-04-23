#include"../Utilitys/Math.h"
#include"Semi.h"
#include "Bug.h"
#include "Math.h"
#include "DxLib.h" 

Vector2D Semi;
Bug* semiscore;
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
	static bool isStop = false;    // 今止まっているか
	static float StopTimer = 0.0f; // 止まっている時間
	const float speed = 1000.0f; //速度
	
	//セミのスコアを2で余り算する
	semicount = semiscore->GetSemiScore() % 2;

	//現在のセミのスコアをいれる
	now_semi = semiscore->GetSemiScore();

	

	//今のスコアと昔のスコアの差が0より大きかったら入る
	if (now_semi - old_semi > 0)
	{
		//座標を画面外へ移動
		Semi = { -100.0f,100.0f };
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
			old_semi = now_semi;   //昔のスコアに現在スコアを代入
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
				//リスポーン座標設定
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
	
}

void SemiDraw(void)
{
	if (SemiDestroy == TRUE)
	{
		DrawCircle(Semi.x, Semi.y, 20, GetColor(0, 0, 255), TRUE);
	}
	
	/*DrawFormatString(200, 700, GetColor(255, 255, 255), "%f", time3);
	DrawFormatString(700, 100, GetColor(255, 255, 255), "%d", now_semi);
	DrawFormatString(800, 100, GetColor(255, 255, 255), "%d", old_semi);
	DrawFormatString(200, 400, GetColor(255, 255, 255), "%f,%f", Semi.x,Semi.y);*/
}

Vector2D* SemiLocation(void)
{
	return &Semi;
}

void SetSemi(class Bug* p)
{
	semiscore = p;
}