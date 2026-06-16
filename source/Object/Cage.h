#pragma once

#include"../Utilitys/Math.h"

#define D_CAGE_MAX		(999)	// かごの最大容量
#define D_CAGE_WIDTH	(50.0f)	// かごの横幅
#define D_CAGE_HEIGHT	(50.0f)	// かごの高さ

class Cage
{
private:
	/// <summary>
	/// 種類
	/// </summary>
	enum Type
	{
		eCicada,		// セミ
		eDragonfly,		// トンボ
		eGrasshopper,	// バッタ
	};
	static int oldCicada;		// 前のセミの数
	static int oldDragonfly;	// 前のトンボの数
	static int oldGrasshopper;	// 前のバッタの数
	static Vector2D location;	// かごの座標
	
	Type m_type;			// 種類
	bool m_display;			// 表示
	Vector2D m_location;	// 座標
	Vector2D m_moveSpeed;	// 移動量
	float m_angle;			// 向き

	enum State
	{
		eJoin,
		eStand,
		eMove,
	};
	State m_state;

	float m_time;		// 時間
	float m_animTime;	// アニメーション時間
	int m_animCount;	// アニメーションカウント

	static int cicadaImage[2];		// セミ画像
	static int dragonflyImage[2];	// トンボ画像
	static int grasshopperImage[4];	// バッタ画像
	static int cageImage;			// かご画像

public:
	Cage();
	~Cage();

public:
	static void Init();
	static void Update(float delta);
	static void Draw();

	void BugInit();
	void BugUpdate(float delta);
	void BugDraw() const;

	/// <summary>
	/// 虫を追加する
	/// </summary>
	/// <param name="type">虫の種類</param>
	/// <param name="id">ID</param>
	void Add(Type type);

	/// <summary>
	/// 入る
	/// </summary>
	/// <param name="delta"></param>
	void Join(float delta);

	/// <summary>
	/// 停止
	/// </summary>
	/// <param name="delta"></param>
	void Stand(float delta);

	/// <summary>
	/// 移動
	/// </summary>
	/// <param name="delta"></param>
	void Move(float delta);

	/// <summary>
	/// 表示の有無を取得
	/// </summary>
	bool GetDisplay() const;
};