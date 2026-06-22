#pragma once

#include "../Utilitys/Math.h"

#include"../Object/player.h"

#include"../Object/Bug/Cicada.h"
#include"../Object/Bug/Dragonfly.h"
#include"../Object/Bug/Grasshopper.h"
#include"../Object/Bug/Bug.h"

#include"../Object/Tree.h"
#include"../Object/Leaf.h"

#include"../Object/Effect.h"
#include"../Object/Shadow.h"

class ObjectManager
{
private:
	static Player player;

	static Cicada cicada[D_CICADA_MAX];
	static Dragonfly dragonfly[D_DRAGONFLY_MAX];
	static Grasshopper grasshopper[D_GRASSHOPPER_MAX];

	static Tree tree[D_TREE_MAX];
	static Leaf leaf[D_LEAF_MAX];

	static Effect effect[D_EFFECT_MAX];
	struct ObjectShadow
	{
		Shadow player;
		Shadow cicada[D_CICADA_MAX];
		Shadow dragonfly[D_DRAGONFLY_MAX];
		Shadow grasshopper[D_GRASSHOPPER_MAX];
	};
	static ObjectShadow shadow;

public:
	ObjectManager();
	~ObjectManager();

public:
	static void Init();
	static void Update(int changeProduction, float delta);
	static void Draw();

public:
	/// <summary>
	/// 円と円の当たり判定
	/// </summary>
	/// <param name="location1">座標1</param>
	/// <param name="location2">座標2</param>
	/// <param name="radius1">半径1</param>
	/// <param name="radius2">半径2</param>
	/// <returns>当たっているならtrue</returns>
	static bool CircleHitCheck(Vector2D location1, Vector2D location2, float radius1, float radius2 = 0.0f);

	/// <summary>
	/// 円と円の押し返し
	/// </summary>
	/// <param name="location1">座標1</param>
	/// <param name="location2">座標2</param>
	/// <param name="radius1">半径1</param>
	/// <param name="radius2">半径2</param>
	/// <returns>押し返すベクトル</returns>
	static Vector2D CirclePushBack(Vector2D location1, Vector2D location2, float radius1, float radius2 = 0.0f);

	/// <summary>
	/// 円と四角形の当たり判定
	/// </summary>
	/// <param name="locationC">円の座標</param>
	/// <param name="locationB">四角形の座標</param>
	/// <param name="radius">円の半径</param>
	/// <param name="width">四角形の横幅</param>
	/// <param name="height">四角形の高さ</param>
	/// <returns>当たっているならtrue</returns>
	static bool BoxHitCheck(Vector2D locationC, Vector2D locationB, float radius, float width, float height);

	/// <summary>
	/// 円と四角形の押し返し
	/// </summary>
	/// <param name="locationC">円の座標</param>
	/// <param name="locationB">四角形の座標</param>
	/// <param name="radius">円の半径</param>
	/// <param name="width">四角形の横幅</param>
	/// <param name="height">四角形の高さ</param>
	/// <returns>押し返すベクトル</returns>
	static Vector2D BoxPushBack(Vector2D locationC, Vector2D locationB, float radius, float width, float height);

	/// <summary>
	/// 虫網との当たり判定
	/// </summary>
	/// <param name="location">座標</param>
	/// <param name="radius">半径</param>
	/// <returns>当たっているならtrue</returns>
	static bool NetHitCheck(Vector2D location, float radius = 0.0f);

	/// <summary>
	/// 木との当たり判定
	/// </summary>
	/// <param name="location">座標</param>
	/// <param name="radius">半径</param>
	/// <param name="isCircle">丸かどうか</param>
	/// <param name="id">木だった時のID</param>
	/// <returns>押し返すベクトル</returns>
	static Vector2D TreeHitCheck(Vector2D location, float radius = 0.0f, bool isCircle = true, int id = -1);

	/// <summary>
	/// 草との当たり判定
	/// </summary>
	/// <param name="location">座標</param>
	/// <param name="radius">半径</param>
	/// <param name="isCircle">丸かどうか</param>
	/// <param name="id">草だった時のID</param>
	/// <returns>押し返すベクトル</returns>
	static Vector2D LeafHitCheck(Vector2D location, float radius = 0.0f, bool isCircle = true, int id = -1);

	/// <summary>
	/// セミとの当たり判定
	/// </summary>
	/// <param name="location">座標</param>
	/// <param name="radius">半径</param>
	/// <param name="id">セミだった時のID</param>
	/// <returns>押し返すベクトル</returns>
	static Vector2D CicadaHitCheck(Vector2D location, float radius = 0.0f, int id = -1);

	/// <summary>
	/// トンボとの当たり判定
	/// </summary>
	/// <param name="location">座標</param>
	/// <param name="radius">半径</param>
	/// <param name="id">トンボだった時のID</param>
	/// <returns>押し返すベクトル</returns>
	static Vector2D DragonflyHitCheck(Vector2D location, float radius = 0.0f, int id = -1);

	/// <summary>
	/// バッタとの当たり判定
	/// </summary>
	/// <param name="location">座標</param>
	/// <param name="radius">半径</param>
	/// <param name="id">バッタだった時のID</param>
	/// <returns>押し返すベクトル</returns>
	static Vector2D GrasshopperHitCheck(Vector2D location, float radius = 0.0f, int id = -1);

	/// <summary>
	/// 最も近い木の座標を取得する
	/// </summary>
	/// <param name="location">座標</param>
	/// <returns>最も近い木の座標</returns>
	static Vector2D FindNearestTree(Vector2D location);
	/// <summary>
	/// 最も近い草の座標を取得する
	/// </summary>
	/// <param name="location">座標</param>
	/// <returns>最も近い草の座標</returns>
	static Vector2D FindNearestLeaf(Vector2D location);

	/// <summary>
	/// エフェクトを生成
	/// </summary>
	/// <param name="location">座標</param>
	/// <param name="color">色</param>
	static void SetEffect(Vector2D location, unsigned int color);
public:
	static Vector2D RandomLocation(float radius);
	static Vector2D GetPlayerLocation();

	/// <summary>
	/// UIのプレイヤーや虫との重なりチェック
	/// </summary>
	/// <param name="width">横幅</param>
	/// <param name="height">高さ</param>
	/// <param name="location">左上の座標</param>
	/// <returns>重なっているならtrue</returns>
	static bool CheckUIOverlapping(float width, float height, Vector2D location = { 0.0f, 0.0f });
};