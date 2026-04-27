#include "Bug.h"

#include "Batta.h"
#include "Semi.h"
#include "Tonbo.h"

#include "player.h"

#include "DxLib.h"

Vector2D player;
Player* target_player;     //プレイヤー情報受け取り
Batta* battango;
Semi* semingo;
Tonbo* tongo;
Vector2D BugLocation[3][10];   //虫座標受け取る用

void Bug::BugInit(void)
{
	player = { 0,0 };
}


void Bug::BugUpdate(void)
{
	//ネットの位置を取得
	Vector2D NetLocation = target_player->GetRingLocation();
	float NetRadius = target_player->GetRingRadius();

	Bug::BugHitCheck(NetLocation, NetRadius);

	/*for (int i = 0; i < 2; i++)
	{
		if (getcount[i] == 1)
		{
			BugRespawn(delta_second,i);
		}
	}*/
}

//スコア表記予定
void Bug::BugDraw(void)
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			switch (i)
			{
			case 0:
				DrawFormatString(500, 200 + j * 50, GetColor(255, 255, 255), "%d", getcount[i][j]);
				break;
			case 1:
				DrawFormatString(700, 200 + j * 50, GetColor(255, 255, 255), "%d", getcount[i][j]);
				break;
			case 2:
				DrawFormatString(800, 200 + j * 50, GetColor(255, 255, 255), "%d", getcount[i][j]);
				break;
			}
		}

	}
}

//プレイヤー情報受けとり
void Bug::SetPlayer(Player* p)
{
	target_player = p;
}

void Bug::SetBatta(Batta* p)
{
	battango = p;
}

void Bug::SetSemi(Semi* p)
{
	semingo = p;
}

void Bug::SetTonbo(Tonbo* p)
{
	tongo = p;
}

//虫全体の当たり判定
void Bug::BugHitCheck(Vector2D NetLocation, float NetRadius)
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			switch (i)
			{
			case 0:
				BugLocation[i][j] = *battango->BattaLocation();
				break;
			case 1:
				BugLocation[i][j] = *semingo->SemiLocation();
				break;
			case 2:
				BugLocation[i][j] = *tongo->TonboLocation();
				break;
			}
			float len = Length(Vec2Sub(BugLocation[i][j], NetLocation));
			if (len < NetRadius)
			{
				getcount[i][j] += 1;
			}
		}

	}



	for (int i = 0; i < 3; i++)
	{

		/*else
		{
			getcount[i] = 0;
		}*/
	}
}

//int Bug::GetBugScore(void)
//{
//	return *getcount;
//}
int Bug::GetBattaScore(int index)
{
	return getcount[0][index];
}

int Bug::GetSemiScore(int index)
{
	return getcount[1][index];
}

int Bug::GetTonboScore(int index)
{
	return getcount[2][index];
}
