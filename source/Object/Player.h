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
	float m_maxSpeed;

	// 虫網
	float m_stickLength;	// 虫網（棒）の長さ
	float m_netLength;	// 網の終点までの長さ

	Vector2D m_ringVector;	// プレイヤーを基準とした虫網（リング）の中心の座標
	Vector2D m_netLocation;	// 虫網（リング）を基準とした網の終点（膨らんでいる部分）

	float m_ringThickness;	// 虫網（リング）の太さ

	float m_ringRadius;	// リングの大きさ最大値
	float m_stickAngle;	// 棒の角度
	
	float m_tiltStick;		// スティックの倒しこみ（ 1 ～ -1 ）
	float m_oldTiltStick;	// 前のスティックの倒しこみ（ 1 ～ -1 ）
	
	float m_rotateStick;	// スティックの角度（90°= 1）
	float m_oldRotateStick;	// 前のスティックの角度（90°= 1）
public:
	Player();
	~Player();

public:
	void Update();
	void Draw() const;

public:
	Vector2D GetRingLocation() const;
	float GetMaxSpeed() const;
};
