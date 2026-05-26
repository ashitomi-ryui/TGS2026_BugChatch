#include"InGameScene.h"
#include"SceneManager.h"
#include"../Utilitys/Input.h"
#include"../Utilitys/Camera.h"
#include"../Utilitys/Random.h"
#include<DxLib.h>

#include"../Object/player.h"

#include"../Object/Bug/Cicada.h"
#include"../Object/Bug/Dragonfly.h"
#include"../Object/Bug/Grasshopper.h"

#include"../Object/Tree.h"
#include"../Object/Leaf.h"
#include"../Object/Ground.h"

Tree tree[D_TREE_MAX];
Leaf leaf[D_LEAF_MAX];
Ground ground[D_GROUND_MAX];
Player player;
Cicada cicada[D_CICADA_MAX];
Dragonfly dragonfly[D_DRAGONFLY_MAX];
Grasshopper grasshopper[D_GRASSHOPPER_MAX];
float timer;
Camera camera(player.GetPlayerLocation());

float num = 0.0f;

int flowerImage[2] = { -1, -1 };

int InGameInit(void)//各プログラムの初期化
{
	Bug::SetPlayer(&player);
	Tree::SetPlayer(&player);

	Tree::Init();
	Leaf::Init();
	Cicada::Init();
	Grasshopper::Init();
	Dragonfly::Init();
	player.Init();

	for (int id = 0; id < D_TREE_MAX; id++)
	{
		int n = 0x7a23;
		n += 0x8e3 * id;
		n *= 0xfa2b;
		n = abs(n);

		tree[id].Set({ D_TREE_WIDTH + (float)(n % (int)(D_STAGE_WIDTH - D_TREE_WIDTH * 2.0f)),
			D_TREE_HEIGHT + (float)(n % (int)(D_STAGE_HEIGHT - D_TREE_HEIGHT * 2.0f)) });
	}
	for (int id = 0; id < D_LEAF_MAX; id++)
	{
		int n = 0x7a23;
		n += 0x8e4 * id;
		n *= 0xfa2b;
		n = abs(n);
		leaf[id].Set({D_LEAF_WIDTH + (float)(n % (int)(D_STAGE_WIDTH - D_LEAF_WIDTH * 2.0f)),
			D_LEAF_HEIGHT + (float)(n % (int)(D_STAGE_HEIGHT - D_LEAF_HEIGHT * 2.0f))
	});
	}
	for (int id = 0; id < D_GROUND_MAX; id++)
	{
		ground[id].Set({ 300.0f + id * 200.0f,300.0f + (float)(id % 3) * 400.0f });
	}

	timer = 0;
	for (int id = 0; id < D_CICADA_MAX; id++)
	{
		// スポーン
		cicada[id].Spawn();
	}
	for (int id = 0; id < D_DRAGONFLY_MAX; id++)
	{
		dragonfly[id].Spawn();
	}
	for (int id = 0; id < D_GRASSHOPPER_MAX; id++)
	{
		grasshopper[id].Spawn();
	}

	flowerImage[0] = LoadGraph("assets/images/OtherObjects/Flower1");
	flowerImage[1] = LoadGraph("assets/images/OtherObjects/Flower2");

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
	for (int id = 0;id < D_DRAGONFLY_MAX;id++)
	{
		dragonfly[id].Update(delta_second);	// トンボの更新
	}
	for (int id = 0; id < D_GRASSHOPPER_MAX; id++)
	{
		grasshopper[id].Update(delta_second);	// バッタの更新
	}

	camera.Update(player.GetPlayerLocation());	// 
	for (int id = 0;id < D_TREE_MAX;id++)
	{
		tree[id].Update(delta_second);
	}
	for (int id = 0; id < D_LEAF_MAX; id++)
	{
		leaf[id].Update(delta_second);
	}
	for (int id = 0; id < D_GROUND_MAX; id++)
	{
		ground[id].Update(delta_second);
	}

	if (GetButtonState(XINPUT_BUTTON_A) == ePressed)
	{
		num = Random::GetRand(-10.0f, 10.0f, 0.5f);
	}

	return eInGame;
}

void InGameDraw(void)
{
	DrawBox(0, 0, (int)D_WIN_WIDTH, (int)D_WIN_HEIGHT, 0x008800, true);

	for (int id = 0; id < D_CICADA_MAX; id++)
	{
		cicada[id].DrawOnTheBack();
	}

	for (int id = 0; id < D_DRAGONFLY_MAX; id++)
	{
		dragonfly[id].DrawOnTheBack();
	}

	for (int id = 0; id < D_GRASSHOPPER_MAX; id++)
	{
		grasshopper[id].DrawOnTheBack();
	}

	for (int id = 0; id < D_LEAF_MAX; id++)
	{
		leaf[id].Draw(id);
	}
<<<<<<< HEAD
	for (int id = 0; id < D_GROUND_MAX; id++)
	{
		ground[id].Draw(id);
=======
	for (int id = 0;id < D_TREE_MAX;id++)
	{
		tree[id].Draw(id);
>>>>>>> c98a86f822b0df1f500d872aa751d466f27c4474
	}

	player.Draw();

	for (int id = 0; id < D_CICADA_MAX; id++)
	{
		cicada[id].DrawOnTheFront();
	}

	for (int id = 0; id < D_DRAGONFLY_MAX; id++)
	{
		dragonfly[id].DrawOnTheFront();
	}

	for (int id = 0; id < D_GRASSHOPPER_MAX; id++)
	{
		grasshopper[id].DrawOnTheFront();
	}
	
	DrawFormatString(10, 10, 0xffffff, "%f", num);

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

Vector2D FindNearestLeaf(Vector2D location)
{
	int nearestId = -1;	// 最も近い木のID
	float nearestLen;	// 最も近い木の距離
	Vector2D leafLocation;	// 木の座標
	float len;	// 距離

	for (int id = 0; id < D_TREE_MAX; id++)
	{
		leafLocation = tree[id].GetLocation();
		len = Length(Vec2Sub(location, leafLocation));

		if (nearestId == -1 || len < nearestLen)
		{
			nearestId = id;
			nearestLen = len;
		}
	}

	return leaf[nearestId].GetLocation();
}

Vector2D FindNearestGround(Vector2D location)
{
	int nearestId = -1;
	float nearestLen;
	Vector2D groundLocation;
	float len;

	for (int id = 0; id < D_GROUND_MAX; id++)
	{
		groundLocation = ground[id].GetLocation();
		len = Length(Vec2Sub(location, groundLocation));

		if (nearestId == -1 || len < nearestLen)
		{
			nearestId = id;
			nearestLen = len;
		}
	}

	return ground[nearestId].GetLocation();
}
