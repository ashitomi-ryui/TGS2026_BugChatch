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
#include"../Object/Bug/Bug.h"
#include"../Object/Effect.h"
#include"../Object/Shadow.h"
#include"../Object/Cage.h"

#include"../Object/Tree.h"
#include"../Object/Leaf.h"

Tree tree[D_TREE_MAX];
Leaf leaf[D_LEAF_MAX];
Player player;
Cicada cicada[D_CICADA_MAX];
Dragonfly dragonfly[D_DRAGONFLY_MAX];
Grasshopper grasshopper[D_GRASSHOPPER_MAX];
Effect effect[D_EFFECT_MAX];

struct ObjectShadow
{
	Shadow player;
	Shadow cicada[D_CICADA_MAX];
	Shadow dragonfly[D_DRAGONFLY_MAX];
	Shadow grasshopper[D_GRASSHOPPER_MAX];
};
ObjectShadow shadow;

Icon icon;
int get[3] = {};
float timer;
int BGM;
int groundImage = -1;

int changeProduction;	// シーン切替演出
float shiita;

int InGameInit(void)//各プログラムの初期化
{
	Bug::SetPlayer(&player);
	Tree::SetPlayer(&player);
	Bug::Init();
	Effect::Init();
	Shadow::Init();
	Tree::Init();
	Leaf::Init();
	Cicada::Init();
	Grasshopper::Init();
	Dragonfly::Init();
	Cage::Init();

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
			int r = (int)Random::GetRand();
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
		do
		{
			// ランダム
			int r = (int)Random::GetRand();
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

	for (int id = 0; id < D_EFFECT_MAX; id++)
	{
		effect[id].SetHidden();
	}

	icon.cicada = LoadGraph("assets/images/UI/CicadaIcon.PNG");
	icon.dragonfly = LoadGraph("assets/images/UI/DragonflyIcon.PNG");
	icon.grasshopper = LoadGraph("assets/images/UI/GrasshopperIcon.PNG");
	
	for (int i = 0; i < 3; i++)
	{
		get[i] = 0;
	}
	groundImage = LoadGraph("assets/images/OtherObjects/Ground.PNG");

	ChangeVolumeSoundMem(230, BGM);
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
			Cicada::StopAudio();
			
			// 次の演出
			changeProduction = 5;

			break;
		}
#endif
		// 画面内にいるかの初期化
		Cicada::WithinTheScreenInit();

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

		for (int id = 0; id < D_EFFECT_MAX; id++)
		{
			effect[id].Update(delta_second);	// エフェクトの更新
		}

		for (int id = 0;id < D_TREE_MAX;id++)
		{
			tree[id].Update(delta_second);
		}
		for (int id = 0; id < D_LEAF_MAX; id++)
		{
			leaf[id].Update(delta_second);
		}

		for (int i = 0; i < 3; i++)
		{
			switch (i)
			{
			case 0:
				get[i] = Bug::GetCicadaCount();
				break;
			case 1:
				get[i] = Bug::GetDragonflyCount();
				break;
			case 2:
				get[i] = Bug::GetGrasshopperCount();
				break;
			}
		}

		// 音再生・停止
		Cicada::PlayAudio();

		break;
	case 5:// ==============================================ゲーム終了
		timer += delta_second;

		if (timer > 2.0f)
		{
			timer = 0.0;
			changeProduction = 6;
		}

		break;
	case 6:	
		timer += delta_second;

		if (timer > 0.0f)
		{
			changeProduction = 7;
			shiita = 0.0f;
		}
		break;
	case 7:
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
	
	// 影の更新
	shadow.player.Set(player.GetPlayerLocation(), player.GetPlayerRadius(), true, false);
	for (int id = 0; id < D_CICADA_MAX; id++)
	{
		shadow.cicada[id].Set(cicada[id].GetLocation(), cicada[id].GetHeight(), cicada[id].GetIsAppearance(), cicada[id].GetIsBack());
	}
	for (int id = 0; id < D_GRASSHOPPER_MAX; id++)
	{
		shadow.grasshopper[id].Set(grasshopper[id].GetLocation(), grasshopper[id].GetHeight(), grasshopper[id].GetIsAppearance(), grasshopper[id].GetIsBack());
	}
	for (int id = 0; id < D_DRAGONFLY_MAX; id++)
	{
		shadow.dragonfly[id].Set(dragonfly[id].GetLocation(), dragonfly[id].GetHeight(), dragonfly[id].GetIsAppearance(), dragonfly[id].GetIsBack());
	}

	Cage::Update(delta_second);

	Camera::Update(player.GetPlayerLocation());	// カメラの更新

	return eInGame;
}

void InGameDraw(void)
{
	// 背景の表示
	for (float i = 0;i < D_STAGE_WIDTH;i += 30.0f * 3.0f * D_OBJECT_SIZE_RATIO)
	{
		for (float j = 0;j < D_STAGE_HEIGHT;j += 30.0f * 3.0f * D_OBJECT_SIZE_RATIO)
		{
			Camera::DrawGraphW({ i, j }, 3.0f * D_OBJECT_SIZE_RATIO, 3.0f * D_OBJECT_SIZE_RATIO, 0.0f, groundImage);
		}
	}

	// 後ろに影を表示
	for (int id = 0; id < D_GRASSHOPPER_MAX; id++)
	{
		shadow.grasshopper[id].DrawOnTheBack();
	}
	for (int id = 0; id < D_CICADA_MAX; id++)
	{
		shadow.cicada[id].DrawOnTheBack();
	}
	for (int id = 0; id < D_DRAGONFLY_MAX; id++)
	{
		shadow.dragonfly[id].DrawOnTheBack();
	}

	// 後ろに虫を表示
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

	// 草の表示
	for (int id = 0; id < D_LEAF_MAX; id++)
	{
		leaf[id].Draw();
	}
	// 木の表示
	for (int id = 0;id < D_TREE_MAX;id++)
	{
		tree[id].Draw(id);
	}

	// 影の表示
	shadow.player.Draw();
	for (int id = 0; id < D_GRASSHOPPER_MAX; id++)
	{
		shadow.grasshopper[id].Draw();
	}
	for (int id = 0; id < D_CICADA_MAX; id++)
	{
		shadow.cicada[id].Draw();
	}
	for (int id = 0; id < D_DRAGONFLY_MAX; id++)
	{
		shadow.dragonfly[id].Draw();
	}

	// プレイヤーの表示
	player.Draw();

	// バッタの表示
	for (int id = 0; id < D_GRASSHOPPER_MAX; id++)
	{
		grasshopper[id].DrawOnTheFront();
	}
	// セミの表示
	for (int id = 0; id < D_CICADA_MAX; id++)
	{
		cicada[id].DrawOnTheFront();
	}
	// トンボの表示
	for (int id = 0; id < D_DRAGONFLY_MAX; id++)
	{
		dragonfly[id].DrawOnTheFront();
	}

	// エフェクトの表示
	for (int id = 0; id < D_EFFECT_MAX; id++)
	{
		effect[id].Draw();
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

		// スコアの表示
		Camera::DrawString({ 25,25 }, 40, GetColor(255, 255, 255), "のこり%d秒", 60 - (int)timer);
		Camera::DrawString({ 75,75 }, 40, GetColor(255, 255, 255), "%d匹", get[0]);
		Camera::DrawString({ 75,135 }, 40, GetColor(255, 255, 255), "%d匹", get[1]);
		Camera::DrawString({ 75,195 }, 40, GetColor(255, 255, 255), "%d匹", get[2]);

		Camera::DrawGraph({ 25,75 }, 1.7, 1.7, 0.0, icon.cicada);
		Camera::DrawGraph({ 25,135 }, 1.7, 1.7, 0.0, icon.dragonfly);
		Camera::DrawGraph({ 25,195 }, 1.7, 1.7, 0.0, icon.grasshopper);
		break;
	case 5:
		Camera::DrawString({ 465,260 }, 100, GetColor(255, 255, 255), "そこまで！");
		break;
	}

	Cage::Draw();

	Camera::Draw();
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

void SetEffect(Vector2D location, unsigned int color)
{
	for (int id = 0; id < D_EFFECT_MAX; id++)
	{
		if (!effect[id].GetIsDisplay())
		{
			effect[id].Set(location, color);
			break;
		}
	}

}