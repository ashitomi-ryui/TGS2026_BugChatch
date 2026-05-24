#pragma once

#include"../Utilitys/Math.h"

#include "Player.h"

#define D_LEAF_WIDTH	(90.0f * D_OBJECT_SIZE_RATIO)
#define D_LEAF_HEIGHT	(140.0f * D_OBJECT_SIZE_RATIO)
#define D_LEAF_MAX		(10)

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
	void Draw(int id)const;

public:
	/// <summary>
	/// プレイヤーの情報受取
	/// </summary>
	/// <param name="p">ポインタ</param>
	static void SetPlayer(Player* p);

	Vector2D GetLocation() const;
};
