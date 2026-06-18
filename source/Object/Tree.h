#pragma once

#include"../Utilitys/Math.h"

#include "Player.h"

#define D_TREE_WIDTH	(120.0f)
#define D_TREE_HEIGHT	(190.0f)
#define D_TREE_MAX		(40)

class Tree
{
private:
	Vector2D m_location;
	Vector2D m_vector;
	static int images[4];

	float m_animTime;
	int m_animCount;

public:
	Tree();
	~Tree();
public:
	static void Init();
	void Set(Vector2D location);
	void Update(float delta);
	void Draw(int id)const;

public:
	/// <summary>
	/// プレイヤーの情報受取
	/// </summary>
	/// <param name="p">ポインタ</param>
	static void SetPlayer(Player* p);

	/// <summary>
	/// 重なりをなくすための
	/// 押し出しベクトルを決める
	/// </summary>
	/// <param name="id">ID</param>
	/// <returns>重なっていたらtrue</returns>
	bool DetermineTheExtrusionVector(int id);

	/// <summary>
	/// 重なりをなくす
	/// </summary>
	void EliminateOverlap();

	Vector2D GetLocation() const;
};