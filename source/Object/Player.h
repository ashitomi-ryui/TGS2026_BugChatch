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
	Vector2D m_netLocation;	// 虫網（リング）を基準とした網の終点（膨らんでいる部分）

	float m_ringThickness;	// 虫網（リング）の太さ

	float m_ringRadius;		// リングの大きさ最大値
	float m_stickAngle;		// 棒の角度

	float m_tiltStick;		// スティックの倒しこみ（ 1 ～ -1 ）
	float m_oldTiltStick;	// 前のスティックの倒しこみ（ 1 ～ -1 ）

	float m_rotateStick;	// スティックの角度（90°= 1）
	float m_oldRotateStick;	// 前のスティックの角度（90°= 1）

	// アニメーション
	bool m_walkingFlag;	// 歩くフラグ
	bool m_holdingFlag;	// 虫網を持つフラグ
	bool m_reverseFlag;	// 反転フラグ

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

public:
	Player();
	~Player();

public:
	void Init();
	void Update(float delta);
	void Draw() const;

private:
	void DrawNet(Vector2D ringLocation, float stickRotate) const;
	void Animation(float delta);
	void Move(float delta);
	void Net(float delta);


public:
	Vector2D GetRingLocation() const;
	float GetRingRadius() const;
	float GetMaxSpeed() const;
	Vector2D GetPlayerLocation() const;
	float GetPlayerRadius() const;

	/// <summary>
	/// プレイヤーを移動させる
	/// </summary>
	/// <param name="vector"></param>
	void PlayerLocationMove(Vector2D vector);
};
