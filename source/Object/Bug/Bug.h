#pragma once
#include"../../Utilitys/Math.h"
#include "../Player.h"

#define D_GRASSHOPPER_MAX	(10)
#define D_CICADA_MAX		(10)
#define D_DRAGONFLY_MAX		(10)

class Bug
{
protected:
	static Player* targetPlayer;	// プレイヤー情報

	static int getCount;

	bool m_isAppearance;	// 出現しているか
	bool m_isEscape;		// 逃げているか
	bool m_isPerched;		// 止まっているか
	bool m_isBack;			// 裏側に表示するか

	Vector2D m_location;	// 座標
	float m_direction;	// 向き
	Vector2D m_moveSpeed;	// 動き
	float m_maxSpeed;	// 最大速度
	Vector2D m_destination;	// 目的地（NULLは{ 0.0f, 0.0f }）

	float m_detectionRange;	// 察知範囲（半径）

public:
	Bug();
	~Bug();

public:
	virtual void Set(Vector2D location);
	virtual void Update(float delta);
	virtual void Draw() const;

public:
	/// <summary>
	/// プレイヤーの情報受取
	/// </summary>
	/// <param name="p">ポインタ</param>
	static void SetPlayer(class Player* p);

protected:
	/// <summary>
	/// 画面内のランダムな位置
	/// </summary>
	/// <returns>座標</returns>
	static Vector2D RandomLocationOnTheScreen();

	/// <summary>
	/// 当たり判定
	/// </summary>
	/// <param name="netLocation">虫網の座標</param>
	/// <param name="netRadius">虫網の半径</param>
	void HitCheck(Vector2D netLocation, float netRadius);

	/// <summary>
	/// 減速
	/// </summary>
	/// <param name="deceleration">減速度</param>
	/// <param name="delta"></param>
	void Deceleration(float deceleration, float delta);

protected:
	/// <summary>
	/// 出現
	/// </summary>
	virtual void Spawn();

	/// <summary>
	/// 再出現
	/// </summary>
	virtual void ReSpawn();

	/// <summary>
	/// 逃げる処理
	/// </summary>
	virtual void Escape(float delta);

	/// <summary>
	/// 目的地の設定
	/// </summary>
	/// <param name="location">移動したい場所</param>
	virtual void SetDestination(Vector2D location);

	/// <summary>
	/// 巡回
	/// </summary>
	virtual void Patrol(float delta);
};




