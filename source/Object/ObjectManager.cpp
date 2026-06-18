#include "ObjectManager.h"
#include"../Utilitys/Camera.h"
#include"../Utilitys/Random.h"

Player ObjectManager::player;

Cicada ObjectManager::cicada[D_CICADA_MAX];
Dragonfly ObjectManager::dragonfly[D_DRAGONFLY_MAX];
Grasshopper ObjectManager::grasshopper[D_GRASSHOPPER_MAX];

Tree ObjectManager::tree[D_TREE_MAX];
Leaf ObjectManager::leaf[D_LEAF_MAX];

Effect ObjectManager::effect[D_EFFECT_MAX];
ObjectManager::ObjectShadow ObjectManager::shadow;

ObjectManager::ObjectManager()
{
}

ObjectManager::~ObjectManager()
{
}

void ObjectManager::Init()
{
	// プレイヤーの情報を渡す
	Bug::SetPlayer(&player);
	Tree::SetPlayer(&player);
	Leaf::SetPlayer(&player);

	// オブジェクトクラスの初期化
	Bug::Init();
	Cicada::Init();
	Grasshopper::Init();
	Dragonfly::Init();

	Tree::Init();
	Leaf::Init();

	Effect::Init();
	Shadow::Init();

	// プレイヤーの初期化
	player.Init();

	// 木の配置
	float playerRadius = player.GetPlayerRadius();
	float treeRadius;	// 木の中心から一番離れた長さ
	treeRadius = Length(Vec2Sub({ 0.0f, 0.0f }, { D_TREE_WIDTH, D_TREE_HEIGHT }));
	for (int id = 0; id < D_TREE_MAX; id++)
	{
		Vector2D location = { 0.0f, 0.0f };		// スポーン座標
		Vector2D nearestTree = { 0.0f, 0.0f };	// 最も近い木
		
		// ランダムな位置に配置
		tree[id].Set(RandomLocation(100.0f));
	}
	// 草の配置
	float leafRadius;	// 草の中心から一番離れた長さ
	leafRadius = Length(Vec2Sub({ 0.0f, 0.0f }, { D_TREE_WIDTH, D_TREE_HEIGHT }));
	for (int id = 0; id < D_LEAF_MAX; id++)
	{
		Vector2D location = { 0.0f, 0.0f };		// スポーン座標
		Vector2D nearestTree = { 0.0f, 0.0f };	// 最も近い木
		Vector2D nearestLeaf = { 0.0f, 0.0f };	// 最も近い草

		// ランダムな位置に配置
		leaf[id].Set(RandomLocation(100.0f));
	}

	for (int i = 0;i < 1000;i++)
	{
		// 木が重ならないように
		for (int id = 0;id < D_TREE_MAX;id++)
		{
			tree[id].EliminateOverlap(id);
		}
		// 草が重ならないように
		for (int id = 0;id < D_TREE_MAX;id++)
		{
			leaf[id].EliminateOverlap(id);
		}
	}

	// プレイヤーの初期化
	player.Init();

	// セミの配置
	for (int id = 0; id < D_CICADA_MAX; id++)
	{
		// スポーン
		cicada[id].Spawn();
	}
	// トンボの配置
	for (int id = 0; id < D_DRAGONFLY_MAX; id++)
	{
		dragonfly[id].Spawn();
	}
	// バッタの配置
	for (int id = 0; id < D_GRASSHOPPER_MAX; id++)
	{
		grasshopper[id].Spawn();
	}

	// エフェクトを非表示
	for (int id = 0; id < D_EFFECT_MAX; id++)
	{
		effect[id].SetHidden();
	}

}

void ObjectManager::Update(int changeProduction, float delta)
{
	Camera::Update(player.GetPlayerLocation());	// カメラの更新

	switch (changeProduction)
	{
	case 0:

		break;
	case 4:

		player.Update(delta);	// プレイヤーの更新

		for (int id = 0;id < D_CICADA_MAX;id++)
		{
			cicada[id].Update(id, delta);	// セミの更新
		}
		for (int id = 0;id < D_DRAGONFLY_MAX;id++)
		{
			dragonfly[id].Update(id, delta);	// トンボの更新
		}
		for (int id = 0; id < D_GRASSHOPPER_MAX; id++)
		{
			grasshopper[id].Update(id, delta);	// バッタの更新
		}

		for (int id = 0; id < D_EFFECT_MAX; id++)
		{
			effect[id].Update(delta);	// エフェクトの更新
		}

		for (int id = 0;id < D_TREE_MAX;id++)
		{
			tree[id].Update(delta);	// 木の更新
		}
		for (int id = 0; id < D_LEAF_MAX; id++)
		{
			leaf[id].Update(delta);	// 草の更新
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
}

void ObjectManager::Draw()
{
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
}

bool ObjectManager::CircleHitCheck(Vector2D location1, Vector2D location2, float radius1, float radius2)
{
	float len = Length(Vec2Sub(location1, location2));
	if (len < radius1 + radius2)
	{
		return true;
	}

	return false;
}

Vector2D ObjectManager::CirclePushBack(Vector2D location1, Vector2D location2, float radius1, float radius2)
{
	float len = Length(Vec2Sub(location1, location2));
	if (len < radius1 + radius2)
	{
		Vector2D vec = {};

		float angle = VecATan2(location2, location1);

		vec.x = sinf(angle) * ((radius1 + radius2) - len);
		vec.y = -cosf(angle) * ((radius1 + radius2) - len);

		return vec;
	}

	return { 0.0f, 0.0f };
}

bool ObjectManager::BoxHitCheck(Vector2D locationC, Vector2D locationB, float radius, float width, float height)
{
	// X座標の最も近い点を求める
	if (locationC.x - radius < locationB.x + width / 2.0f &&
		locationC.x + radius > locationB.x - width / 2.0f)
	{
		// Y座標の最も近い点を求める
		if (locationC.y - radius < locationB.y + height / 2.0f &&
			locationC.y + radius > locationB.y - height / 2.0f)
		{
			return true;
		}
	}

	return false;
}

Vector2D ObjectManager::BoxPushBack(Vector2D locationC, Vector2D locationB, float radius, float width, float height)
{
	// 円に最も近い点
	Vector2D closest = {};

	// X座標の最も近い点を求める
	if (locationC.x > locationB.x + width / 2.0f)
	{
		closest.x = locationB.x + width / 2.0f;
	}
	else if (locationC.x < locationB.x - width / 2.0f)
	{
		closest.x = locationB.x - width / 2.0f;
	}
	else
	{
		closest.x = locationC.x;
	}

	// Y座標の最も近い点を求める
	if (locationC.y > locationB.y + height / 2.0f)
	{
		closest.y = locationB.y + height / 2.0f;
	}
	else if (locationC.y < locationB.y - height / 2.0f)
	{
		closest.y = locationB.y - height / 2.0f;
	}
	else
	{
		closest.y = locationC.y;
	}

	float len = Length(Vec2Sub(closest, locationC));
	if (len < radius)
	{
		Vector2D vec = {};

		float angle = VecATan2(closest, locationC);

		vec.x = sinf(angle) * (radius - len);
		vec.y = -cosf(angle) * (radius - len);

		return vec;
	}
	return { 0.0f, 0.0f };
}

bool ObjectManager::NetHitCheak(Vector2D location, float radius)
{
	//ネットの位置を取得
	Vector2D netLocation = player.GetRingLocation();
	float netRadius = player.GetRingRadius();

	return CircleHitCheck(netLocation, location, netRadius, radius);
}

Vector2D ObjectManager::TreeHitCheak(Vector2D location, float radius, bool isCircle, int id)
{
	// 移動量
	Vector2D move = { 0.0f, 0.0f };

	// 木の半径
	float treeRadius = Length(Vec2Sub({ 0.0f, 0.0f }, { D_TREE_WIDTH / 2.0f, D_TREE_HEIGHT / 2.0f }));

	// 木の数分繰り返す
	for (int i = 0;i < D_TREE_MAX;i++)
	{
		Vector2D treeLocation = tree[i].GetLocation();
		
		// 同じオブジェクトでないなら
		if (id != i)
		{
			if (isCircle)
			{
				// 重なっている分加算する
				move = Vec2Add(move, CirclePushBack(location, treeLocation, radius, treeRadius));
			}
			else
			{
				// 重なっている分加算する
				move = Vec2Add(move, BoxPushBack(location, treeLocation, radius, D_TREE_WIDTH, D_TREE_HEIGHT));
			}
		}
	}

	// 移動量を返す
	return move;
}

Vector2D ObjectManager::LeafHitCheak(Vector2D location, float radius, bool isCircle, int id)
{
	// 移動量
	Vector2D move = { 0.0f, 0.0f };

	// 草の半径
	float leafRadius = Length(Vec2Sub({ 0.0f, 0.0f }, { D_TREE_WIDTH / 2.0f, D_TREE_HEIGHT / 2.0f }));

	// 木の数分繰り返す
	for (int i = 0;i < D_LEAF_MAX;i++)
	{
		Vector2D leafLocation = leaf[i].GetLocation();

		// 同じオブジェクトでないなら
		if (id != i)
		{
			if (isCircle)
			{
				// 重なっている分加算する
				move = Vec2Add(move, CirclePushBack(location, leafLocation, radius, leafRadius));
			}
			else
			{
				// 重なっている分加算する
				move = Vec2Add(move, BoxPushBack(location, leafLocation, radius, D_LEAF_WIDTH, D_LEAF_HEIGHT));
			}
		}
	}

	// 移動量を返す
	return move;
}

Vector2D ObjectManager::CicadaHitCheak(Vector2D location, float radius, int id)
{
	// 移動量
	Vector2D move = { 0.0f, 0.0f };

	// 木の数分繰り返す
	for (int i = 0;i < D_LEAF_MAX;i++)
	{
		Vector2D cicadaLocation = cicada[i].GetLocation();
		float cicadaRadius = cicada[i].GetRadius();

		// 同じオブジェクトでないなら
		if (id != i)
		{
			// 重なっている分加算する
			move = Vec2Add(move, CirclePushBack(location, cicadaLocation, radius, cicadaRadius));
		}
	}

	// 移動量を返す
	return move;
}

Vector2D ObjectManager::DragonflyHitCheak(Vector2D location, float radius, int id)
{
	// 移動量
	Vector2D move = { 0.0f, 0.0f };

	// 木の数分繰り返す
	for (int i = 0;i < D_LEAF_MAX;i++)
	{
		Vector2D dragonflyLocation = dragonfly[i].GetLocation();
		float dragonflyRadius = dragonfly[i].GetRadius();

		// 同じオブジェクトでないなら
		if (id != i)
		{
			// 重なっている分加算する
			move = Vec2Add(move, CirclePushBack(location, dragonflyLocation, radius, dragonflyRadius));
		}
	}

	// 移動量を返す
	return move;
}

Vector2D ObjectManager::GrasshopperHitCheak(Vector2D location, float radius, int id)
{
	// 移動量
	Vector2D move = { 0.0f, 0.0f };

	// 木の数分繰り返す
	for (int i = 0;i < D_LEAF_MAX;i++)
	{
		Vector2D grasshopperLocation = grasshopper[i].GetLocation();
		float grasshopperRadius = grasshopper[i].GetRadius();

		// 同じオブジェクトでないなら
		if (id != i)
		{
			// 重なっている分加算する
			move = Vec2Add(move, CirclePushBack(location, grasshopperLocation, radius, grasshopperRadius));
		}
	}

	// 移動量を返す
	return move;
}

Vector2D ObjectManager::FindNearestTree(Vector2D location)
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

Vector2D ObjectManager::FindNearestLeaf(Vector2D location)
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

void ObjectManager::SetEffect(Vector2D location, unsigned int color)
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

Vector2D ObjectManager::RandomLocation(float radius)
{
	Vector2D location = {};

	Vector2D playerLocation = player.GetPlayerLocation();

	 // ランダム
	int r = (int)Random::GetRand();
	// 座標を画面内のランダムに
	location.x = D_LEAF_WIDTH + (float)(r % (int)(D_STAGE_WIDTH - D_LEAF_WIDTH * 2.0f));
	location.y = D_LEAF_HEIGHT + (float)(r % (int)(D_STAGE_HEIGHT - D_LEAF_HEIGHT * 2.0f));
	
	location = Vec2Add(location, CirclePushBack(location, playerLocation, radius));

	return location;
}

Vector2D ObjectManager::GetPlayerLocation()
{
	return player.GetPlayerLocation();
}
