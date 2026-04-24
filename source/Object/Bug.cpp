#include "Bug.h"

#include "Batta.h"
#include "Semi.h"
#include "Tonbo.h"

#include "player.h"

#include "DxLib.h"

Vector2D NetLocation;      //ネットの座標受け取り
Vector2D player;
Player* target_player;     //プレイヤー情報受け取り
Vector2D BugLocation[3];   //虫座標受け取る用
int getcount[3] = { 0,0,0 }; //各虫の座標

void Bug::BugInit(void)
{
	NetLocation = { 0,0 };
	player = { 0,0 };
}


void Bug::BugUpdate(void)
{
	//ネットの位置を取得
	NetLocation = target_player->GetRingLocation();
	
	Bug::BugHitCheck(NetLocation);

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
	DrawFormatString(500, 600, GetColor(255, 255, 255), "%f,%f", NetLocation.x, NetLocation.y);
	DrawFormatString(800, 300, GetColor(255, 255, 255), "トンボ捕獲:%d", getcount[2]);
	DrawFormatString(800, 350, GetColor(255, 255, 255), "セミ捕獲:%d", getcount[1]);
	DrawFormatString(800, 400, GetColor(255, 255, 255), "バッタ捕獲:%d", getcount[0]);
}

//プレイヤー情報受けとり
void Bug::SetPlayer(Player* p)
{
	target_player = p;
}

//虫全体の当たり判定
void Bug::BugHitCheck(Vector2D NetLocation)
{
	BugLocation[0] = *BattaLocation();
	BugLocation[1] = *SemiLocation();
	BugLocation[2] = *TonboLocation();
	for (int i = 0; i < 3; i++)
	{
		if (NetLocation.x < BugLocation[i].x + 20 && NetLocation.x>BugLocation[i].x - 20 &&
			NetLocation.y<BugLocation[i].y + 20 && NetLocation.y>BugLocation[i].y - 20)
		{
			getcount[i] += 1;
			
		}
		/*else
		{
			getcount[i] = 0;
		}*/
	}
}

int Bug::GetBugScore(void)
{
	return *getcount;
}

int Bug::GetBattaScore(void)
{
	return getcount[0];
}

int Bug::GetSemiScore(void)
{
	return getcount[1];
}

int Bug::GetTonboScore(void)
{
	return getcount[2];
}
