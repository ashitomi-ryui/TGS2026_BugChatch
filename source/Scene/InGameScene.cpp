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
float seigenjikann;

int InGameInit(void)//ŠeƒvƒƒOƒ‰ƒ€‚Ì‰Šú‰»
{
	BattaInit();
	SemiInit();
	SetPlayer(&player);
	return TRUE;
}

eSceneType InGameUpdate(float delta_second)
{
	seigenjikann += delta_second;
	if (seigenjikann > 60)
	{
		return eResult;
	}
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
	BugDraw();
	tree.TreeDraw();
}

Vector2D GetRingLocation()
{
	return player.GetRingLocation();
}