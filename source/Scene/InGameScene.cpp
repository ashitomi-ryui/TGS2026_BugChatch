#include"InGameScene.h"
#include"SceneManager.h"
#include"../Utilitys/Input.h"
#include"../Utilitys/Camera.h"
#include"../Object/Batta.h"
#include"../Object/player.h"
#include<DxLib.h>
#include"../Object/Tonbo.h"
#include"../Object/Bug.h"
#include"../Object/Semi.h"
#include"../Object/Tree.h"

Tree tree;
Batta batta;
Tonbo tonbo;
Player player;
Bug bug;
float seigenjikann;
Camera camera(player.GetPlayerLocation());

int InGameInit(void)//各プログラムの初期化
{
	seigenjikann = 0;
	batta.BattaInit();
	SemiInit();
	bug.SetPlayer(&player);
	bug.SetBatta(&batta);
	batta.SetBatta(&bug);
	bug.SetTonbo(&tonbo);
	SetSemi(&bug);
	tonbo.SetTonbo(&bug);
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
	batta.BattaUpdate(delta_second);
	tonbo.TonboUpdate(delta_second);
	bug.BugUpdate();
	camera.Update(player.GetPlayerLocation());
	return eInGame;
}

void InGameDraw(void)
{
	player.Draw();
	bug.BugDraw();
	batta.BattaDraw();
	tonbo.TonboDraw();
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