#pragma once
#include "math.h"
#include "Bug.h"

#include "../../Utilitys/Math.h"

class Dragonfly : public Bug
{
private:
	Vector2D m_destinations[5];
	bool m_isDestinations[5];

	static int images[4];
	float count;
	bool flag;
bool flag2;
int abura;
int hanten = FALSE;
int i=0;
public:
	Dragonfly();
	~Dragonfly();

public:
	static void Init();
	virtual void Update(float delta) override;
	virtual void Draw() const override;
	virtual void DrawOnTheBack() const override;
	virtual void DrawOnTheFront() const override;

	/// <summary>
	/// 出現
	/// </summary>
	void Spawn();

	/// <summary>
	/// 再出現
	/// </summary>
	void ReSpawn(float delta);

	/// <summary>
	/// 目的地の設定
	/// </summary>
	/// <param name="location">移動したい場所</param>
	void SetDestination(Vector2D location);


	/// <summary>
	/// アニメーション
	/// </summary>
	/// <param name="delta"></param>
	virtual void Animation(float delta) override;

	/// <summary>
	/// 逃げる処理
	/// </summary>
	void Escape(float delta);

	/// <summary>
	/// 待機
	/// </summary>
	/// <param name="delta"></param>
	void Stand(float delta);

	/// <summary>
	/// 移動
	/// </summary>
	void Move(float delta);

	/// <summary>
	/// パニック
	/// </summary>
	/// <param name="delta"></param>
	void Panic(float delta);

	/// <summary>
	/// 察知判定
	/// </summary>
	/// <param name="delta"></param>
	void PerceptionJudgment();

	/// <summary>
	/// 逃げ状態への遷移
	/// </summary>
	void TransitionToEscape();

	/// <summary>
	/// 前面に置く
	/// </summary>
	void PutInFront();
};
