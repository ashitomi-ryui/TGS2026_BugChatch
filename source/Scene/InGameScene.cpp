#include"InGameScene.h"
#include"SceneManager.h"
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
Bug bug;
float seigenjikann;

int InGameInit(void)//各プログラムの初期化
{
	seigenjikann = 0;
	BattaInit();
	SemiInit();
	bug.SetPlayer(&player);
	SetBatta(&bug);
	SetSemi(&bug);
	SetTonbo(&bug);
	return TRUE;
}

eSceneType InGameUpdate(float delta_second)
{
	seigenjikann += delta_second;
	if (seigenjikann > 60)
	{
		return eTitle;//ゲーム終了時にタイトルに戻る（仮）
	}
	player.Update();
	SemiUpdate(delta_second);
	BattaUpdate(delta_second);
	TonboUpdate(delta_second);
	bug.BugUpdate();
	return eInGame;
}

void InGameDraw(void)
{
	player.Draw();
	bug.BugDraw();
	BattaDraw();
	TonboDraw();
	SemiDraw();
	
	tree.TreeDraw();
}

Vector2D GetRingLocation()
{
	return player.GetRingLocation();
}

float GetPlayerMaxSpeed()
{
	return player.GetMaxSpeed();
}