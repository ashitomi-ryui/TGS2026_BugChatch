#pragma once

#include "Bug.h"

#include "../../Utilitys/Math.h"
#define D_CICADA_MAX	(10)

class Cicada : public Bug
{
private:

public:
	Cicada();
	~Cicada();

public:
	virtual void Update(float delta) override;
	virtual void Draw() const override;

	/// <summary>
	/// 出現
	/// </summary>
	virtual void Spawn() override;

	/// <summary>
	/// 再出現
	/// </summary>
	virtual void ReSpawn() override;

	/// <summary>
	/// 逃げる処理
	/// </summary>
	virtual void Escape(float delta) override;

	/// <summary>
	/// 目的地の設定
	/// </summary>
	/// <param name="location">移動したい場所</param>
	virtual void SetDestination(Vector2D location) override;

	/// <summary>
	/// 巡回
	/// </summary>
	virtual void Patrol(float delta) override;


};
