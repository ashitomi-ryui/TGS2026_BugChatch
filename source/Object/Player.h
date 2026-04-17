#pragma once
#include "../Utilitys/Input.h"
#include "../Utilitys/Math.h"

class Player
{
private:

	int score;	// スコア
	// 座標
	// プレイヤーキャラ
	Vector2D location;	// プレイヤーの座標
	Vector2D moveSpeed;	// 動く速度

	// 虫網
	float stickLength;	// 虫網（棒）の長さ
	float netLength;	// 網の終点までの長さ

	Vector2D ringVector;	// プレイヤーを基準とした虫網（リング）の中心の座標
	Vector2D netLocation;	// 虫網（リング）を基準とした網の終点（膨らんでいる部分）
	Vector2D netMoveSpeed;	// 網の動く速さ

	float ringThickness;	// 虫網（リング）の太さ

	float ringRadius;	// リングの大きさ最大値
	float stickAngle;	// 棒の角度

	// 右スティック
	Vector2D rightStick;
	Vector2D oldRightStick;
	// スティックの倒しこみ（ 1 ～ -1 ）
	float tiltStick;
	float oldTiltStick;
	// スティックの回転（90°= 1）
	float rotateStick;
	float oldRotateStick;
public:
	Player();
	~Player();

public:
	void Update();
	void Draw() const;

public:
	Vector2D GetRingLocation();
	Vector2D GetNetLocation();
};
