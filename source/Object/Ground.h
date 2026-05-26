#pragma once

#include"../Utilitys/Math.h"

#include "Player.h"

#define D_GROUND_WIDTH	(90.0f * D_OBJECT_SIZE_RATIO)
#define D_GROUND_HEIGHT	(140.0f * D_OBJECT_SIZE_RATIO)
#define D_GROUND_MAX		(5)

class Ground
{
private:
	Vector2D m_location;
	

public:
	Ground();
	~Ground();
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
