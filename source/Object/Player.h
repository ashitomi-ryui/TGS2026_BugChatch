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
	Vector2D maxSpeed;	// 最大速度

	// 虫網
	Vector2D stickLocation;		// 虫網（棒）の終点座標（一番端）
	Vector2D netLocation;	// 虫網（網）の終点（膨らんでいる部分）
	Vector2D netMoveSpeed;	// 網の動く速さ

public:
	Player();
	~Player();

public:
	void Update();
	void Draw() const;

public:

};
