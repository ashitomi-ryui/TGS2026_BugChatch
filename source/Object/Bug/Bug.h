#pragma once
#include"../../Utilitys/Math.h"
#include "../Player.h"

#define D_GRASSHOPPER_MAX	(20)	// バッタの数
#define D_CICADA_MAX		(20)	// セミの数
#define D_DRAGONFLY_MAX		(5)	// トンボの数

class Bug
{
protected:
	static Player* targetPlayer;	// プレイヤー情報

	static int cicadaGetCount;
	static int dragonflyGetCount;
	static int grasshopperGetCount;
	static int HitSE;

	bool m_isAppearance;	// 出現しているか
	bool m_isEscape;		// 逃げているか

	enum State
	{
		eStand,		// 待機状態
		eMove,		// 移動状態
		ePanic,		// パニック状態
	};

	State m_state;

	bool m_isBack;			// 背面に描画するか

	Vector2D m_location;	// 座標
	float m_radius;			// 半径
	float m_direction;		// 移動方向
	float m_Angle;			// 画像の向き
	Vector2D m_moveSpeed;	// 動き
	Vector2D m_destination;	// 目的地
	float m_height;			// 高さ

	float m_detectionRange;	// 察知範囲（半径）

	float m_detectionTime;	// 察知時間
	float m_transitionTime;	// 遷移時間

	float m_animTime;	// アニメーション時間
	int m_animCount;	// アニメーションカウント

public:
	Bug();
	~Bug();

public:
	static void Init();
	virtual void Set(Vector2D location);	// 初期化
	virtual void Update(float delta);		// 更新
	virtual void Draw() const;				// 描画
	virtual void DrawOnTheBack() const;		// 背面に描画
	virtual void DrawOnTheFront() const;	// 前面に描画

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
	/// 加速
	/// </summary>
	/// <param name="acceleration">加速度</param>
	/// <param name="maxSpeed">最大速度</param>
	/// <param name="direction">角度</param>
	/// <param name="delta"></param>
	void Acceleration(float acceleration, float maxSpeed, float direction, float delta);

	/// <summary>
	/// 減速
	/// </summary>
	/// <param name="deceleration">減速度</param>
	/// <param name="delta"></param>
	void Deceleration(float deceleration, float delta);

protected:
	/// <summary>
	/// アニメーション
	/// </summary>
	/// <param name="delta"></param>
	virtual void Animation(float delta);

	/// <summary>
	/// 当たり判定
	/// </summary>
	/// <returns>当たったならtrue</returns>
	virtual bool HitCheck();

public:
	Vector2D GetLocation() const;
	float GetHeight() const;
	bool GetIsAppearance() const;

	int GetCicadaCount() const;
	int GetDragonflyCount() const;
	int GetGrasshopperCount() const;
};




