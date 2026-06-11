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

Tree tree[D_TREE_MAX];
Leaf leaf[D_LEAF_MAX];
Player player;
Cicada cicada[D_CICADA_MAX];
Dragonfly dragonfly[D_DRAGONFLY_MAX];
Grasshopper grasshopper[D_GRASSHOPPER_MAX];
float timer;
int BGM;
int flowerImage[2] = { -1, -1 };
int groundImage = -1;

int changeProduction;	// シーン切替演出
float shiita;

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
	
	BGM = LoadSoundMem("assets/Audio/AS_1468345_Main.wav");
	if (BGM == -1)
	{
		return FALSE;
	}

	// 木の初期化
	float playerRadius = player.GetPlayerRadius();
	float treeRadius;	// 木の中心から一番離れた長さ
	treeRadius = Length(Vec2Sub({ 0.0f, 0.0f }, { D_TREE_WIDTH, D_TREE_HEIGHT }));
	for (int id = 0; id < D_TREE_MAX; id++)
	{
		Vector2D location = { 0.0f, 0.0f };		// スポーン座標
		Vector2D nearestTree = { 0.0f, 0.0f };	// 最も近い木
		float installationRadius;
		do
		{
			// ランダム
			int r = Random::GetRand();
			// 座標を画面内のランダムに
			location.x = D_TREE_WIDTH + (float)(r % (int)(D_STAGE_WIDTH - D_TREE_WIDTH * 2.0f));
			location.y = D_TREE_HEIGHT + (float)(r % (int)(D_STAGE_HEIGHT - D_TREE_HEIGHT * 2.0f));

			// 最も近い木の座標を取得
			nearestTree = FindNearestTree(location);

			// 設置半径
			installationRadius = treeRadius + playerRadius * 2.0f;
			// 近くに何もなくなるまでループ
		} while (Length(Vec2Sub(location, nearestTree)) < installationRadius + treeRadius);

		tree[id].Set(location);
	}
	// 草の初期化
	float leafRadius;	// 草の中心から一番離れた長さ
	leafRadius = Length(Vec2Sub({ 0.0f, 0.0f }, { D_TREE_WIDTH, D_TREE_HEIGHT }));
	for (int id = 0; id < D_LEAF_MAX; id++)
	{
		Vector2D location = { 0.0f, 0.0f };		// スポーン座標
		Vector2D nearestTree = { 0.0f, 0.0f };	// 最も近い木
		Vector2D nearestLeaf = { 0.0f, 0.0f };	// 最も近い草
		float installationRadius;
		do
		{
			// ランダム
			int r = Random::GetRand();
			// 座標を画面内のランダムに
			location.x = D_LEAF_WIDTH + (float)(r % (int)(D_STAGE_WIDTH - D_LEAF_WIDTH * 2.0f));
			location.y = D_LEAF_HEIGHT + (float)(r % (int)(D_STAGE_HEIGHT - D_LEAF_HEIGHT * 2.0f));
			
			// 最も近い木の座標を取得
			nearestTree = FindNearestTree(location);
			// 最も近い草の座標を取得
			nearestLeaf = FindNearestLeaf(location);
			
			// 近くに何もなくなるまでループ
		} while (Length(Vec2Sub(location, nearestTree)) < leafRadius + treeRadius
			|| Length(Vec2Sub(location, nearestLeaf)) < leafRadius * 2.0f);

		leaf[id].Set(location);
		
	}

	timer = 0.0f;
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

	groundImage = LoadGraph("assets/images/OtherObjects/Ground.PNG");

	ChangeVolumeSoundMem(100, BGM);
	PlaySoundMem(BGM, DX_PLAYTYPE_BACK);

	changeProduction = 0;
	shiita = 0.0f;

	Camera::SetScreenLocation({ -D_WIN_WIDTH / 4.0f, D_WIN_HEIGHT / 4.0f });
	Camera::SetScreenRatioSize(0.2f);

	return TRUE;
}

eSceneType InGameUpdate(float delta_second)
{
	switch (changeProduction)
	{
	case 0:	// ==============================================ゲームスタート
		shiita -= 2.0f * delta_second;

		Vector2D loc = Camera::GetScreenLocation();

		loc.x += D_WIN_WIDTH * 1.5f * delta_second;
		loc.y = D_WIN_HEIGHT / 4.0f + sinf(shiita * DX_PI_F) * D_WIN_HEIGHT * 0.1f;

		if (loc.x >= D_WIN_WIDTH / 2.0f)
		{
			loc.x = D_WIN_WIDTH / 2.0f;
			// 次の演出
			changeProduction = 1;
		}

		Camera::SetScreenLocation(loc);

		// 木とプレイヤーが重ならないように
		for (int id = 0;id < D_TREE_MAX;id++)
		{
			tree[id].Update(delta_second);
		}

		break;
	case 1:
		shiita -= 2.0f * delta_second;

		if (shiita < -1.0f)
		{
			shiita = -1.0f; // 行き過ぎ防止

			// 次の演出
			changeProduction = 2;
			shiita = 0.0f;
		}

		Camera::SetScreenLocation({ D_WIN_WIDTH / 2.0f,
			D_WIN_HEIGHT / 4.0f + sinf(shiita * DX_PI_F) * D_WIN_HEIGHT * 0.1f });

		break;
	case 2:
		shiita -= 2.0f * delta_second;

		{
			float ratio = Camera::GetScreenRatioSize();
			ratio += ratio * 3.2f * delta_second;
			if (ratio > 1.0f)
			{
				ratio = 1.0f;
			}

			if (shiita < -1.0f)
			{
				shiita = -1.0f; // 行き過ぎ防止

				// 次の演出
				changeProduction = 3;
				timer = 0.0f;
				ratio = 1.0f;
			}

			//ジャンプの移動処理
			float height = sinf(shiita * DX_PI_F) * (D_WIN_HEIGHT / 2.0f);
			Camera::SetScreenLocation({ D_WIN_WIDTH / 2.0f,
				D_WIN_HEIGHT / 4.0f + (D_WIN_HEIGHT / -4.0f) * shiita - height });

			Camera::SetScreenRatioSize(ratio);
		}

		break;
	case 3:
		timer += delta_second;

		if (timer >= 3.0f)
		{
			// 次の演出
			changeProduction = 4;
			timer = 0.0f;
		}

		break;

	case 4:	// ==============================================ゲームプレイ
		timer += delta_second;
#ifndef _DEBUG
		if (timer > 60.0f)
		{
			timer = 0.0f;

			// 音を止める
			StopSoundMem(BGM);

			Grasshopper::StopAudio();
			
			// 次の演出
			changeProduction = 5;
		}
#endif

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

		for (int id = 0;id < D_TREE_MAX;id++)
		{
			tree[id].Update(delta_second);
		}
		for (int id = 0; id < D_LEAF_MAX; id++)
		{
			leaf[id].Update(delta_second);
		}

		break;
	case 5:	// ==============================================ゲーム終了
		timer += delta_second;

		if (timer > 0.0f)
		{
			changeProduction = 6;
			shiita = 0.0f;
		}
		break;
	case 6:
		shiita -= 2.0f * delta_second;

		{
			float ratio = Camera::GetScreenRatioSize();
			ratio -= ratio * 3.2f * delta_second;
			if (ratio > 1.0f)
			{
				ratio = 1.0f;
			}

			if (shiita < -1.5f)
			{
				return eResult;	//ゲーム終了時にリザルトに遷移
				timer = 0.0f;
			}

			//ジャンプの移動処理
			float height = cosf(shiita * DX_PI_F) * (D_WIN_HEIGHT);
			Camera::SetScreenLocation({ D_WIN_WIDTH / 2.0f,
				D_WIN_HEIGHT * 3.0f / 2.0f + (D_WIN_HEIGHT * 3.0f / 2.0f) * shiita - height });

			Camera::SetScreenRatioSize(ratio);
		}
		break;
	}

	Camera::Update(player.GetPlayerLocation());	// カメラの更新

	return eInGame;
}

void InGameDraw(void)
{
	for (float i = 0;i < D_STAGE_WIDTH;i += 30.0f * 3.0f * D_OBJECT_SIZE_RATIO)
	{
		for (float j = 0;j < D_STAGE_HEIGHT;j += 30.0f * 3.0f * D_OBJECT_SIZE_RATIO)
		{
			Camera::DrawGraphW({ i, j }, 3.0f * D_OBJECT_SIZE_RATIO, 0.0f, groundImage);
		}
	}

	for (int id = 0; id < D_GRASSHOPPER_MAX; id++)
	{
		grasshopper[id].DrawOnTheBack();
	}

	for (int id = 0; id < D_CICADA_MAX; id++)
	{
		cicada[id].DrawOnTheBack();
	}

	for (int id = 0; id < D_DRAGONFLY_MAX; id++)
	{
		dragonfly[id].DrawOnTheBack();
	}

	for (int id = 0; id < D_LEAF_MAX; id++)
	{
		leaf[id].Draw(id);
	}
	for (int id = 0;id < D_TREE_MAX;id++)
	{
		tree[id].Draw(id);
	}

	player.Draw();

	for (int id = 0; id < D_GRASSHOPPER_MAX; id++)
	{
		grasshopper[id].DrawOnTheFront();
	}

	for (int id = 0; id < D_CICADA_MAX; id++)
	{
		cicada[id].DrawOnTheFront();
	}

	for (int id = 0; id < D_DRAGONFLY_MAX; id++)
	{
		dragonfly[id].DrawOnTheFront();
	}

	switch(changeProduction)
	{
	case 3:
		Camera::DrawString({ D_WIN_WIDTH / 2.0f, D_WIN_HEIGHT / 2.0f - 100.0f }, 75, 0xffffff, "%d", 3 - (int)timer);
		break;
	case 4:
		if (timer <= 1.0f)
		{
			Camera::DrawString({ D_WIN_WIDTH / 2.0f - 120.0f, D_WIN_HEIGHT / 2.0f - 100.0f }, 75, 0xffffff, "スタート！");
		}
		break;
	}
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

		if (treeLocation.x != 0.0f &&
			treeLocation.y != 0.0f)
		{
			len = Length(Vec2Sub(location, treeLocation));

			if (nearestId == -1 || len < nearestLen)
			{
				nearestId = id;
				nearestLen = len;
			}
		}
	}

	if (nearestId == -1)
		return { -100.0f,-100.0f };

	return tree[nearestId].GetLocation();
}

Vector2D FindNearestLeaf(Vector2D location)
{
	int nearestId = -1;	// 最も近い木のID
	float nearestLen;	// 最も近い木の距離
	Vector2D leafLocation;	// 木の座標
	float len;	// 距離

	for (int id = 0; id < D_LEAF_MAX; id++)
	{
		leafLocation = leaf[id].GetLocation();

		if (leafLocation.x != 0.0f &&
			leafLocation.y != 0.0f)
		{
			len = Length(Vec2Sub(location, leafLocation));

			if (nearestId == -1 || len < nearestLen)
			{
				nearestId = id;
				nearestLen = len;
			}
		}
	}

	if (nearestId == -1)
		return { -100.0f,-100.0f };

	return leaf[nearestId].GetLocation();
}