#pragma once

#include"../Utilitys/Math.h"

#include "Player.h"

#define D_TREE_WIDTH	(90.0f * D_OBJECT_SIZE_RATIO)
#define D_TREE_HEIGHT	(140.0f * D_OBJECT_SIZE_RATIO)
#define D_TREE_MAX		(20)

class Tree
{
private:
	Vector2D m_location;
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

	Vector2D GetLocation() const;
};