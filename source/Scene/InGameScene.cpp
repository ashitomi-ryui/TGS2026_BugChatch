#include"InGameScene.h"
#include"../Utilitys/Input.h"
#include"../Object/Batta.h"
#include<DxLib.h>
#include"../Object/Tonbo.h"

int InGameInit(void)//ŠeƒvƒƒOƒ‰ƒ€‚Ì‰Šú‰»
{
	BattaInit();
	return TRUE;
}

eSceneType InGameUpdate(float delta_second)
{
	BattaUpdate();
	return eInGame;
}

void InGameDraw(void)
{
	BattaDraw();
	TonboDraw();
	
}