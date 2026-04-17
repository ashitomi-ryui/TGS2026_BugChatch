#include "DxLib.h"
#include <math.h>
#include <stdlib.h>

#include "Player.h"

Player::Player()
{
	score = 0;	// スコア
	// 座標
	// プレイヤーキャラ
	location = { 640.0f, 360.0f };	// プレイヤーの座標
	moveSpeed = { 0.0f, 0.0f };	// 動く速度

	// 虫網
	stickLength = 150.0f;	// 虫網（棒）の長さ
	netLength = 40.0f;		// 網の終点までの長さ

	ringVector = { 0.0f, 0.0f };	// プレイヤーを基準とした虫網（リング）の中心の座標
	netLocation = { 640.0f, 360.0f + netLength};	// 虫網（リング）を基準とした網の終点（膨らんでいる部分）
	netMoveSpeed = { 0.0f, 0.0f };	// 網の動く速さ

	ringRadius = 40.0f;// リングの半径

	// 虫網（リング）の3D座標
	ringThickness = ringRadius;

	stickAngle = 1.0f;	// 棒の角度

	// 右スティック
	rightStick = { 0.0f, 0.0f };
	oldRightStick;
	// スティックの倒しこみ（ 1 ～ -1 ）
	tiltStick = 0.0f;
	oldTiltStick;
	// スティックの回転（90°= 1）
	rotateStick = 0.0f;
	oldRotateStick;
}

Player::Player::~Player()
{
}

void Player::Update()
{
	float acceleration = 0.5f;
	float deceleration = 0.2f;
	float maxSpeed = 3.0f;

	oldRightStick = rightStick;
	Vector2D leftStick = GetLeftStick();
	rightStick = GetRightStick();

	leftStick.y *= -1;
	rightStick.y *= -1;

	// 加速
	// スティック
	moveSpeed = Vec2Add(moveSpeed, Vec2Mult(leftStick, acceleration));

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

	location = Vec2Add(location, moveSpeed);

	// 虫網
	ringVector = Vec2Mult(rightStick, stickLength);
	
	oldTiltStick = tiltStick;
	oldRotateStick = rotateStick;
	tiltStick = sqrtf(LengthSq(Vec2Sub({ 0.0f, 0.0f }, rightStick)));
	rotateStick = FindTheAngle({ 0.0f, 0.0f }, rightStick);
	if (tiltStick == 0.0f)
	{
		rotateStick = oldRotateStick;
		ringThickness = ringRadius;
	}
	else
	{
		// リングの太さ
		ringThickness += fabs(tiltStick - oldTiltStick) * ringRadius;
		ringThickness -= fabs(rotateStick - oldRotateStick) * ringRadius;

		// 虫網を回す最小値、最大値を設定
		if (ringThickness < 0.0f)
		{
			ringThickness = 0.0f;
		}
		else if (ringThickness > ringRadius)
		{
			ringThickness = ringRadius;
		}
	}
	
	Vector2D ringLocation = Vec2Add(location, ringVector);	// リングの位置
	float netDistance;	// リングと網の距離
	float netAngle;
	netDistance = sqrtf(LengthSq(Vec2Sub(netLocation, ringLocation)));
	if (netDistance > netLength)
	{
		netAngle = FindTheAngle(netLocation, ringLocation);

		netLocation.x += sinf(netAngle) * (netDistance - netLength);
		netLocation.y += cosf(netAngle) * (netDistance - netLength);
	}

	oldRightStick = rightStick;
}

void Player::Draw() const
{
	DrawCircle(location.x, location.y, 25, 0x00ffff, true);
	
	Vector2D point[4];
	Vector2D ringLocation = Vec2Add(location, ringVector);

	DrawLine(location.x, location.y, ringLocation.x, ringLocation.y, 0x00ff00, 5);

	point[0].x = ringLocation.x + sinf(rotateStick) * (tiltStick * ringRadius + 10.0f);
	point[0].y = ringLocation.y + cosf(rotateStick) * (tiltStick * ringRadius + 10.0f);
	
	point[1].x = ringLocation.x - sinf(rotateStick) * (tiltStick * ringRadius + 10.0f);
	point[1].y = ringLocation.y - cosf(rotateStick) * (tiltStick * ringRadius + 10.0f);

	point[2].x = ringLocation.x + sinf(rotateStick + 1.0f) * (ringThickness + 10.0f);
	point[2].y = ringLocation.y + cosf(rotateStick + 1.0f) * (ringThickness + 10.0f);

	point[3].x = ringLocation.x - sinf(rotateStick + 1.0f) * (ringThickness + 10.0f);
	point[3].y = ringLocation.y - cosf(rotateStick + 1.0f) * (ringThickness + 10.0f);

	DrawTriangle(point[0].x, point[0].y, point[2].x, point[2].y, netLocation.x, netLocation.y, 0xffffff, true);
	DrawTriangle(point[1].x, point[1].y, point[3].x, point[3].y, netLocation.x, netLocation.y, 0xffffff, true);
	DrawTriangle(point[2].x, point[2].y, point[1].x, point[1].y, netLocation.x, netLocation.y, 0xffffff, true);
	DrawTriangle(point[3].x, point[3].y, point[0].x, point[0].y, netLocation.x, netLocation.y, 0xffffff, true);
	//DrawCircle(point[0].x, point[0].y, 5, 0xffffff, true);
	//DrawCircle(point[1].x, point[1].y, 5, 0xffffff, true);
	//DrawCircle(point[2].x, point[2].y, 5, 0xffffff, true);
	//DrawCircle(point[3].x, point[3].y, 5, 0xffffff, true);
	//DrawFormatString(100, 400, 0xffffff, "%.2f %.2f ", tiltStick, rotateStick);
	//DrawFormatString(100, 450, 0xffffff, "%.2f %.2f ", tiltStick, rotateStick);
	//DrawFormatString(100, 500, 0xffffff, "%.2f", ringThickness);
}

Vector2D Player::GetRingLocation()
{
	return ringVector;
}

Vector2D Player::GetNetLocation()
{
	return netLocation;
}
