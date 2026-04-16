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
	Vector2D ringLocation;	// 虫網（リング）の座標（一番端）
	Vector2D netLocation;	// 網の終点（膨らんでいる部分）
	Vector2D netMoveSpeed;	// 網の動く速さ

	float stickLength;	// 虫網（棒）の長さ
	float netLength;	// 網の終点までの長さ

	float ringMaxSize;	// リングの見た目の大きさ最大値
	float ringMinSize;	// リングの見た目の大きさ最小値（変動値）
	float ringAngle;	// リングの大きさ最大値の角度
	float stickAngle;	// 棒の角度

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
