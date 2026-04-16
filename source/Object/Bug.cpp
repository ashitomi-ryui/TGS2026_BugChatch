#include "Bug.h"

#include "Batta.h"
#include "Semi.h"
#include "Tonbo.h"

#include "player.h"

#include "DxLib.h"

Vector2D NetLocation;
Player* target_player;
Vector2D BugLocation[3];   //虫座標受け取る用
int getcount[3];

void BugInit(void)
{
	NetLocation = { 0,0 };
}

void BugUpdate(void)
{
	NetLocation = target_player->GetNetLocation();
	BugHitCheck(target_player->GetNetLocation());
}

void BugDraw(void)
{

	DrawFormatString(500, 600, GetColor(255, 255, 255), "%f,%f", NetLocation.x, NetLocation.y);
	DrawFormatString(800, 300, GetColor(255, 255, 255), "%d", getcount[0]);
	DrawFormatString(800, 350, GetColor(255, 255, 255), "%d", getcount[1]);
}

void BugGet(void)
{

}

//プレイヤー情報受けとり
void SetPlayer(Player* p)
{
	target_player = p;
}

//虫全体の当たり判定
void BugHitCheck(Vector2D NetLocation)
{
	BugLocation[0] = *BattaLocation();
	BugLocation[1] = *SemiLocation();
	for (int i = 0; i < 2; i++)
	{
		if (NetLocation.x < BugLocation[i].x + 20 && NetLocation.x>BugLocation[i].x - 20 &&
			NetLocation.y<BugLocation[i].y + 20 && NetLocation.y>BugLocation[i].y - 20)
		{
			getcount[i] = 1;
		}
		else
		{
			getcount[i] = 0;
		}
	}
}

int GetBattaScore(void)
{
	return getcount[0];
}

int GetSemiScore(void)
{
	return getcount[1];
}