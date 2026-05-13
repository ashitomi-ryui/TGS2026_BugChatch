#pragma once

#include "Bug.h"

#include "../../Utilitys/Math.h"
#define D_CICADA_MAX	(10)

class Cicada
{
private:
	Bug cicada;

public:
	Cicada();
	~Cicada();

public:
	void Update(float delta);
	void Draw();

	/// <summary>
	/// 出現
	/// </summary>
	void Spawn();

	/// <summary>
	/// 再出現
	/// </summary>
	void ReSpawn();

	/// <summary>
	/// 逃げる処理
	/// </summary>
	void Escape(float delta);

	/// <summary>
	/// 目的地の設定
	/// </summary>
	/// <param name="location">移動したい場所</param>
	void SetDestination(Vector2D location);

	/// <summary>
	/// 巡回
	/// </summary>
	void Patrol(float delta);


};
