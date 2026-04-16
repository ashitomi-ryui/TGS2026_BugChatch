#include "Batta.h"
#include "player.h"
#include "DxLib.h"
#include "Bug.h"

Vector2D NetLocation;
Player* target_player;

void BugInit(void)
{
	NetLocation = { 0,0 };
}

void BugUpdate(void)
{
	NetLocation = target_player->GetNetLocation();
}

void BugDraw(void)
{

	DrawFormatString(500, 600, GetColor(255, 255, 255), "%f,%f", NetLocation.x, NetLocation.y);
}

void BugGet(void)
{

}

void SetPlayer(Player* p)
{
	target_player = p;
}
