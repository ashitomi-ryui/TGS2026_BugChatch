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

int InGameInit(void)//ŠeƒvƒƒOƒ‰ƒ€‚Ì‰Šú‰»
{
	BattaInit();
	SemiInit();
	return TRUE;
}

eSceneType InGameUpdate(float delta_second)
{
	SemiUpdate(delta_second);
	BattaUpdate(delta_second);
	BugUpdate();
	return eInGame;
}

void InGameDraw(void)
{

	BattaDraw();
	TonboDraw();
	SemiDraw();
	tree.TreeDraw();
}