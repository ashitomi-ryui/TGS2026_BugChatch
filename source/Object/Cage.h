#pragma once

#include "Player.h"
#include "../Utilitys/Math.h"
#include "../Scene/SceneType.h"

#define D_CAGE_MAX		(999)	// かごの最大容量
#define D_CAGE_RATIO	(1.5f)	// かごの比率	
#define D_CAGE_WIDTH	(35.0f * D_CAGE_RATIO)	// かご内の横幅
#define D_CAGE_HEIGHT	(15.0f * D_CAGE_RATIO)	// かご内の高さ

class Cage
{
public:
	/// <summary>
	/// 種類
	/// </summary>
	enum Type
	{
		eCicada,		// セミ
		eDragonfly,		// トンボ
		eGrasshopper,	// バッタ
	};
private:
	/// <summary>
	/// 状態
	/// </summary>
	enum State
	{
		eJoin,	// 入る
		eStand,	// 待機
		eMove,	// 動く
	};

	// かごの変数
	static Player* targetPlayer;	// プレイヤー情報
	static int oldCicada;		// 前のセミの数
	static int oldDragonfly;	// 前のトンボの数
	static int oldGrasshopper;	// 前のバッタの数

	static Vector2D location;	// かごの座標

	static int bugId;	// IDの始まり
	static bool isRemovedAll;	// 虫を全て出した

	static float time;		// 時間
	static float animTime;	// アニメーション時間
	static int animCount;	// アニメーションカウント

	static int cicadaImage;		// セミ画像
	static int dragonflyImage[2];	// トンボ画像
	static int grasshopperImage[4];	// バッタ画像
	static int cageImage[2][4];		// かご画像

private:
	// 虫の変数
	Type m_type;			// 種類
	State m_state;			// 状態
	bool m_display;			// 表示
	Vector2D m_location;	// 座標
	Vector2D m_moveSpeed;	// 移動量
	float m_angle;			// 向き
	float m_theta;			// θ

	float m_time;		// 時間
	float m_animTime;	// アニメーション時間
	int m_animCount;	// アニメーションカウント

public:
	Cage();
	~Cage();

public:
	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="sceneType">シーン情報</param>
	static void Init(eSceneType sceneType);
	/// <summary>
	/// 更新
	/// </summary>
	/// <param name="sceneType">シーン情報</param>
	/// <param name="delta">フレーム秒</param>
	static void Update(eSceneType sceneType, float delta);
	/// <summary>
	/// 描画
	/// </summary>
	/// <param name="sceneType">シーン情報</param>
	/// <param name="color">色</param>
	static void Draw(eSceneType sceneType, unsigned int color = 0xffffff);

private:
	/// <summary>
	/// かごの中の虫の初期化
	/// </summary>
	/// <param name="sceneType">シーン情報</param>
	void BugInit(eSceneType sceneType);
	/// <summary>
	/// かごの中の虫の更新
	/// </summary>
	/// <param name="sceneType">シーン情報</param>
	/// <param name="delta">フレーム秒</param>
	void BugUpdate(eSceneType sceneType, float delta);
	/// <summary>
	/// かごの中の虫の描画
	/// </summary>
	/// <param name="sceneType">シーン情報</param>
	/// <param name="color">色</param>
	void BugDraw(eSceneType sceneType, unsigned int color = 0xffffff) const;

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
	/// <returns></returns>
	bool GetDisplay() const;

public:
	/// <summary>
	/// 虫を全て出した
	/// </summary>
	/// <returns></returns>
	static bool GetRemovedAll();
};