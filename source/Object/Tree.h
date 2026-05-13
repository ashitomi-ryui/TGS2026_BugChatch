#pragma once

#include"../Utilitys/Math.h"

#include "Player.h"

#define D_TREE_WIDTH	(70)
#define D_TREE_HEIGHT	(150)
#define D_TREE_MAX		(10)

class Tree
{
private:
	Vector2D m_location;
	int image;
public:
	Tree();
	~Tree();
public:
	void Set(Vector2D location);
	void Update();
	void Draw(int id)const;

public:
	/// <summary>
	/// プレイヤーの情報受取
	/// </summary>
	/// <param name="p">ポインタ</param>
	static void SetPlayer(Player* p);

	Vector2D GetLocation() const;
};