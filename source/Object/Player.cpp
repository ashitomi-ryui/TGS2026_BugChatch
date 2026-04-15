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

}