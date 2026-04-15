#include "Player.h"
#include "DxLib.h"

Player::Player()
{
	score = 0;	// スコア
	// 座標
	// プレイヤーキャラ
	location = { 0.0,0.0 };	// プレイヤーの座標
	moveSpeed = { 0.0,0.0 };	// 動く速度
	maxSpeed = { 0.0,0.0 };	// 最大速度

	// 虫網
	stickLocation = { 0.0,0.0 };		// 虫網（棒）の終点座標（一番端）
	netLocation = { 0.0,0.0 };	// 虫網（網）の終点（膨らんでいる部分）
	netMoveSpeed = { 0.0,0.0 };
}

Player::Player::~Player()
{
}

void Player::Update()
{
	Vector2D leftStick = GetLeftStick();
	Vector2D rightStick = GetRightStick();


}

void Player::Draw() const
{
	float x1, y1, x2, y2, x3, y3, x4, y4;
	x1 = stickLocation.x - 10;
	y1 = stickLocation.y;
	
	x2 = stickLocation.x;
	y2 = stickLocation.y + 10;

	x3 = stickLocation.x + 10;
	y3 = stickLocation.y;

	x4 = stickLocation.x;
	y4 = stickLocation.y - 10;

	DrawTriangle(x1, y1, x2, y2, x3, y3, 0xffffff, true);
	DrawTriangle(x1, y1, x4, y4, x3, y3, 0xffffff, true);

}

Vector2D Player::GetNetLocation()
{
	return stickLocation;
}
