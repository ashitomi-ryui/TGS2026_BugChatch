#include"InGameScene.h"
#include"../Utilitys/Input.h"
#include"../Object/Batta.h"
#include"../Object/player.h"
#include<DxLib.h>
#include"../Object/Tonbo.h"
#include"../Object/Bug.h"
#include"../Object/Semi.h"
#include"../Object/Tree.h"

Tree tree;
Player player;

int InGameInit(void)//ŠeƒvƒƒOƒ‰ƒ€‚Ì‰Šú‰»
{
	BattaInit();
	SemiInit();
	return TRUE;
}

eSceneType InGameUpdate(float delta_second)
{
	player.Update();
	SemiUpdate(delta_second);
	BattaUpdate(delta_second);
	BugUpdate();
	return eInGame;
}

void InGameDraw(void)
{
	player.Draw();
	BattaDraw();
	TonboDraw();
	SemiDraw();
	tree.TreeDraw();
}

Vector2D GetRingLocation()
{
	return player.GetRingLocation();
}

Vector2D GetNetLocation()
{
	return player.GetNetLocation();
}