#pragma once
#include "../Utilitys/Input.h"
#include "../Utilitys/Math.h"

class Player
{
private:

	int score;	// スコア
	// 座標
	// プレイヤーキャラ
	Vector2D m_location;	// プレイヤーの座標
	Vector2D m_moveSpeed;	// 動く速度
	float m_maxSpeed;		// 最大速度
	float m_radius;			// 半径

	// 虫網
	float m_stickLength;	// 虫網（棒）の長さ
	float m_netLength;		// 網の終点までの長さ

	Vector2D m_ringVector;	// プレイヤーを基準とした虫網（リング）の中心の座標
	Vector2D m_netLocation;	// 網の終点座標（膨らんでいる部分）

	float m_ringThickness;	// 虫網（リング）の太さ（0.0fが太く、0.0fから離れるほど細い）

	float m_ringRadius;		// リングの大きさ最大値
	float m_stickAngle;		// 棒の角度

	float m_netRadius;	// 網の終点の半径

	float m_tiltStick;		// スティックの倒しこみ（ 1 ～ -1 ）
	float m_oldTiltStick;	// 前のスティックの倒しこみ（ 0 ～ 1 ）

	float m_rotateStick;	// スティックの角度（90°= 1）
	float m_oldRotateStick;	// 前のスティックの角度（90°= 1）
	float m_valueRotateStick;	// スティックの角度に足す値

	bool m_walkingFlag;	// 歩くフラグ
	bool m_holdingFlag;	// 虫網を持つフラグ
	bool m_oldHoldingFlag;	// 前フレームの虫網を持つフラグ
	bool m_reverseFlag;	// 反転フラグ
	bool m_pullTheNetFlag;	// 虫網を引くフラグ
	bool m_rotatingThrustFlag;	// 回転させながら出すフラグ
	bool m_isSneak;	// 忍び足

	// アニメーション
	float m_blinkTime;		// 瞬き時間
	float m_headAnimTime;	// 頭の時間
	int m_headAnimCount;	// 頭のカウント
	int m_headSubscript;	// 頭の添え字
	float m_legAnimTime;	// 脚の時間
	int m_legAnimCount;		// 脚のカウント
	int m_legSubscript;		// 脚の添え字

	// 画像情報
	static int m_headImage[4];
	static int m_bodyImage;
	static int m_legImage[4];
	static int m_armImage;
	static int m_netImage;

public:
	Player();
	~Player();

public:
	void Init();
	void Update(float delta);
	void Draw() const;

private:
	void DrawNet(Vector2D ringLocation) const;
	void Animation(float delta);
	void Move(float delta);
	void Net(float delta);


public:
	/// <summary>
	/// 虫網のリングの座標を取得する
	/// </summary>
	/// <returns></returns>
	Vector2D GetRingLocation() const;
	/// <summary>
	/// 虫網のリングの半径を取得する
	/// </summary>
	/// <returns></returns>
	float GetRingRadius() const;
	/// <summary>
	/// プレイヤーの最大速度を取得する
	/// </summary>
	/// <returns></returns>
	float GetMaxSpeed() const;
	/// <summary>
	/// プレイヤーの座標を取得する
	/// </summary>
	/// <returns></returns>
	Vector2D GetLocation() const;
	/// <summary>
	/// プレイヤーの半径を取得する
	/// </summary>
	/// <returns></returns>
	float GetRadius() const;
	/// <summary>
	/// 虫網の棒の長さを取得する
	/// </summary>
	/// <returns></returns>
	float GetStickmLength() const;

	/// <summary>
	/// 虫網を持っているか取得する
	/// </summary>
	/// <returns>持っているならtrue</returns>
	bool GetNetHolding() const;
	/// <summary>
	/// 忍び足か取得する
	/// </summary>
	/// <returns>忍び足ならtrue</returns>
	bool GetSneak() const;

	/// <summary>
	/// プレイヤーを移動させる
	/// </summary>
	/// <param name="vector"></param>
	void MoveLocation(Vector2D vector);
};
