#pragma once

#include"../Utilitys/Math.h"

#include "Player.h"

#define D_LEAF_WIDTH	(60.0f)
#define D_LEAF_HEIGHT	(190.0f)
#define D_LEAF_MAX		(40)

class Leaf
{
private:
	Vector2D m_location;
	static int images[4];

	float m_animTime;
	int m_animCount;

public:
	Leaf();
	~Leaf();
public:
	static void Init();
	void Set(Vector2D location);
	void Update(float delta);
	void Draw()const;

public:
	/// <summary>
	/// プレイヤーの情報受取
	/// </summary>
	/// <param name="p">ポインタ</param>
	static void SetPlayer(Player* p);

	/// <summary>
	/// 重なりをなくす
	/// </summary>
	/// <param name="id">ID</param>
	void EliminateOverlap(int id);

	Vector2D GetLocation() const;
};
