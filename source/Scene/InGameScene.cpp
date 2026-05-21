#include"InGameScene.h"
#include"SceneManager.h"
#include"../Utilitys/Input.h"
#include"../Utilitys/Camera.h"
#include"../Utilitys/Random.h"
#include<DxLib.h>

#include"../Object/player.h"

#include"../Object/Bug/Cicada.h"
//#include"../Object/Bug/Dragonfly.h"
//#include"../Object/Bug/Grasshopper.h"

#include"../Object/Tree.h"

Tree tree[D_TREE_MAX];
Player player;
Cicada cicada[D_CICADA_MAX];
//Dragonfly dragonfly[D_DRAGONFLY_MAX];
//Grasshopper grasshopper[D_GRASSHOPPER_MAX];
float timer;
Camera camera(player.GetPlayerLocation());

int num = 0;

int InGameInit(void)//各プログラムの初期化
{
	Bug::SetPlayer(&player);
	Tree::SetPlayer(&player);

	Tree::Init();
	Cicada::Init();

	for (int id = 0; id < D_TREE_MAX; id++)
	{
		tree[id].Set({ 100.0f + id * 200.0f, 100.0f + (float)(id % 3) * 400.0f });
	}

	timer = 0;
	for (int id = 0; id < D_CICADA_MAX; id++)
	{
		// スポーン
		cicada[id].Spawn();
	}
	//for (int id = 0; id < D_DRAGONFLY_MAX; id++)
	//{
	//	dragonfly[id].Spawn();
	//}
	//for (int id = 0; id < D_GRASSHOPPER_MAX; id++)
	//{
	//	grasshopper[id].Spawn();
	//}

	return TRUE;
}

eSceneType InGameUpdate(float delta_second)
{
	timer += delta_second;
	if (timer > 60.0f * 3.0f)
	{
		return eResult;//ゲーム終了時にタイトルに戻る（仮）
	}

	player.Update(delta_second);	// プレイヤーの更新

	for (int id = 0;id < D_CICADA_MAX;id++)
	{
		cicada[id].Update(delta_second);	// セミの更新
	}
	//for (int id = 0;id < D_DRAGONFLY_MAX;id++)
	//{
	//	dragonfly[id].Uptate(delta_second);	// トンボの更新
	//}
	//for (int id = 0; id < 10; id++)
	//{
	//	grasshopper[id].Update(delta_second);	// バッタの更新
	//}

	camera.Update(player.GetPlayerLocation());	// 
	for (int id = 0;id < D_TREE_MAX;id++)
	{
		tree[id].Update(delta_second);
	}

	if (GetButtonState(XINPUT_BUTTON_A) == ePressed)
	{
		num = Random::GetRand() % 10;
	}

	return eInGame;
}

void InGameDraw(void)
{
	for (int id = 0; id < D_CICADA_MAX; id++)
	{
		cicada[id].DrawOnTheBack();
	}

	for (int id = 0;id < D_TREE_MAX;id++)
	{
		tree[id].Draw(id);
	}

	player.Draw();

	for (int id = 0; id < D_CICADA_MAX; id++)
	{
		cicada[id].DrawOnTheFront();
	}
	
	DrawFormatString(10, 10, 0xffffff, "%d", num);
}

Vector2D GetRingLocation()
{
	return player.GetRingLocation();
}

float GetPlayerMaxSpeed()
{
	return player.GetMaxSpeed();
}

Vector2D GetPlayerLocation()
{
	return player.GetPlayerLocation();
}

void PlayerLocationMove(Vector2D vector)
{
	player.PlayerLocationMove(vector);
}

Vector2D FindNearestTree(Vector2D location)
{
	int nearestId = -1;	// 最も近い木のID
	float nearestLen;	// 最も近い木の距離
	Vector2D treeLocation;	// 木の座標
	float len;	// 距離

	for (int id = 0;id < D_TREE_MAX;id++)
	{
		treeLocation = tree[id].GetLocation();
		len = Length(Vec2Sub(location, treeLocation));

		if (nearestId == -1 || len < nearestLen)
		{
			nearestId = id;
			nearestLen = len;
		}
	}

	return tree[nearestId].GetLocation();
}
