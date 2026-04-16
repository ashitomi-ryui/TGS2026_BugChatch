#include "Player.h"
#include "DxLib.h"

Player::Player()
{
	score = 0;	// スコア
	// 座標
	// プレイヤーキャラ
	location = { 0.0,0.0 };	// プレイヤーの座標
	moveSpeed = { 0.0,0.0 };	// 動く速度

	// 虫網
	ringLocation = { 0.0,0.0 };		// 虫網（棒）の終点座標（一番端）
	netLocation = { 0.0,0.0 };	// 虫網（網）の終点（膨らんでいる部分）
	netMoveSpeed = { 0.0,0.0 };
}

Player::Player::~Player()
{
}

void Player::Update()
{
	float acceleration = 0.5f;
	float deceleration = 0.2f;
	float maxSpeed = 3.0f;

	// スティックの値( -32768 ～ 32767 )
	Vector2D leftStick = GetLeftStick();
	Vector2D rightStick = GetRightStick();

	// 加速
	// スティック
	moveSpeed.x += leftStick.x * acceleration;
	moveSpeed.y += leftStick.y * acceleration;

	// キーボード（後で消す）
	if (GetKeyInputState(KEY_INPUT_RIGHT) == eHeld)
	{
		moveSpeed.x += acceleration;
	}
	if (GetKeyInputState(KEY_INPUT_LEFT) == eHeld)
	{
		moveSpeed.x -= acceleration;
	}
	if (GetKeyInputState(KEY_INPUT_DOWN) == eHeld)
	{
		moveSpeed.y += acceleration;
	}
	if (GetKeyInputState(KEY_INPUT_UP) == eHeld)
	{
		moveSpeed.y -= acceleration;
	}

	// 減速
	if (moveSpeed.x > deceleration)
	{
		moveSpeed.x -= deceleration;
	}
	else if (moveSpeed.x < -deceleration)
	{
		moveSpeed.x += deceleration;
	}
	else
	{
		moveSpeed.x = 0;
	}
	if (moveSpeed.y > deceleration)
	{
		moveSpeed.y -= deceleration;
	}
	else if (moveSpeed.y < -deceleration)
	{
		moveSpeed.y += deceleration;
	}
	else
	{
		moveSpeed.y = 0;
	}

	// 最大速度調整
	if (moveSpeed.x > maxSpeed)
	{
		moveSpeed.x = maxSpeed;
	}
	if (moveSpeed.x < -maxSpeed)
	{
		moveSpeed.x = -maxSpeed;
	}
	if (moveSpeed.y > maxSpeed)
	{
		moveSpeed.y = maxSpeed;
	}
	if (moveSpeed.y < -maxSpeed)
	{
		moveSpeed.y = -maxSpeed;
	}

	//Filter2D(moveSpeed.x, moveSpeed.y);

	location.x += moveSpeed.x;
	location.y += moveSpeed.y;

	ringLocation = location;
	netLocation = location;
}

void Player::Draw() const
{
	float x1, y1, x2, y2, x3, y3, x4, y4;
	x1 = ringLocation.x - 10;
	y1 = ringLocation.y;
	
	x2 = ringLocation.x;
	y2 = ringLocation.y + 10;

	x3 = ringLocation.x + 10;
	y3 = ringLocation.y;

	x4 = ringLocation.x;
	y4 = ringLocation.y - 10;

	DrawTriangle(x1, y1, x2, y2, x3, y3, 0xffffff, true);
	DrawTriangle(x1, y1, x4, y4, x3, y3, 0xffffff, true);


	DrawCircle(location.x, location.y, 10, 0x00ffff, true);
}

Vector2D Player::GetRingLocation()
{
	return ringLocation;
}

Vector2D Player::GetNetLocation()
{
	return netLocation;
}
