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
	stickLength = 100.0f;	// 虫網（棒）の長さ
	netLength = 30.0f;		// 網の終点までの長さ

	ringLocation = location;	// 虫網（リング）の座標（一番端）
	netLocation = location;	// 網の終点（膨らんでいる部分）
	netMoveSpeed = { 0.0f, 0.0f };	// 網の動く速さ

	ringMaxSize = 30.0f;// リングの見た目の大きさ最大値
	ringMinSize = 0.0f;	// リングの見た目の大きさ最小値（変動値）
	ringAngle = 0.0f;	// リングの大きさ最大値の角度
	stickAngle = 1.0f;	// 棒の角度
}

Player::Player::~Player()
{
}

void Player::Update()
{
	float acceleration = 0.5f;
	float deceleration = 0.2f;
	float maxSpeed = 3.0f;

	Vector2D leftStick = GetLeftStick();
	Vector2D rightStick = GetRightStick();

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
	Vector2D ringNextLocation = Vec2Add(location, Vec2Mult(rightStick, stickLength));	// 次のリング位置
	float ringMove = sqrtf(LengthSq(Vec2Sub(ringLocation, ringNextLocation)));		// リングの移動距離
	float ringDistance = sqrtf(LengthSq(Vec2Sub(location, ringLocation)));			// リング位置とプレイヤー位置間の距離
	float ringNextDistance = sqrtf(LengthSq(Vec2Sub(location, ringNextLocation)));	// 次のリング位置とプレイヤー位置間の距離
	float ringAwayDistance = ringNextDistance - ringDistance;	// リングを遠ざける距離
	ringMove -= fabsf(ringAwayDistance);

	if (LengthSq(Vec2Sub(location, ringLocation)) != 0)
	{	// リング位置がデフォルトではないなら

		// 棒の角度を変更
		stickAngle = FindTheAngle(location, ringLocation);
		
		if (LengthSq(Vec2Sub(ringLocation, ringNextLocation)) != 0)
		{	// リング位置が移動しているなら

			// リングのサイズ最大値の角度を変更
			if (ringAngle < 1.0f && ringAngle>-1.0f)
			{
				ringAngle += 1.0f * ringAwayDistance / ringMaxSize;
			}
			else
			{
				ringAngle -= 1.0f * ringAwayDistance / ringMaxSize;
			}
			if ((ringAngle < 2.0f || ringAngle>-2.0) && ringAngle > 0.0f)
			{
				ringAngle += ringMove * ringMaxSize/ 1.0f;
			}
			else
			{
				ringAngle -= ringMove * ringMaxSize / 1.0f;
			}

			// スティックを倒す・戻してリング最小値を変動させる
			ringMinSize += ringMaxSize * ringAwayDistance / stickLength;

			// スティックを回してリング最小値を減らす
			ringMinSize -= ringMaxSize * ringMove / stickLength;
		}
	}
	else
	{
		ringAngle = 0.0f;
	}

	if (stickAngle > 2.0f)
	{
		stickAngle -= 4.0f;
	}
	if (stickAngle < -2.0f)
	{
		stickAngle += 4.0f;
	}
	if (ringAngle > 2.0f)
	{
		ringAngle -= 4.0f;
	}
	if (ringAngle < -2.0f)
	{
		ringAngle += 4.0f;
	}
	if (ringMinSize > ringMaxSize)
	{	// 最大値を越えないようにする
		ringMinSize = ringMaxSize;
	}
	if (ringMinSize < 0)
	{	// 最小値を0未満にしないようにする
		ringMinSize = 0;
	}

	// リングを移動
	ringLocation = ringNextLocation;

	float netDistance;	// リングと網の距離
	float netAngle;
	netDistance = sqrtf(LengthSq(Vec2Sub(netLocation, ringLocation)));
	if (netDistance > netLength)
	{
		netAngle = FindTheAngle(netLocation, ringLocation);

		netLocation.x += sinf(netAngle) * (netDistance - netLength);
		netLocation.y += cosf(netAngle) * (netDistance - netLength);
	}
}

void Player::Draw() const
{
	DrawCircle(location.x, location.y, 25, 0x00ffff, true);

	Vector2D min1, min2, max1, max2;

	

	min1.x = ringLocation.x + sinf(ringAngle + 1) * ringMinSize;
	min1.y = ringLocation.y + cosf(ringAngle + 1) * ringMinSize;
	
	min2.x = ringLocation.x - sinf(ringAngle + 1) * ringMinSize;
	min2.y = ringLocation.y - cosf(ringAngle + 1) * ringMinSize;

	max1.x = ringLocation.x + sinf(ringAngle) * ringMaxSize;
	max1.y = ringLocation.y + cosf(ringAngle) * ringMaxSize;

	max2.x = ringLocation.x - sinf(ringAngle) * ringMaxSize;
	max2.y = ringLocation.y - cosf(ringAngle) * ringMaxSize;

	DrawTriangle(min1.x, min1.y, min2.x, min2.y, max1.x, max1.y, 0x00ff00, true);
	DrawTriangle(min1.x, min1.y, min2.x, min2.y, max2.x, max2.y, 0x00ff00, true);
	DrawCircle(netLocation.x, netLocation.y, 10, 0xffffff, true);
	DrawFormatString(100, 10, 0xffffff, "%.2f", FindTheAngle(netLocation, ringLocation));
}

Vector2D Player::GetRingLocation()
{
	return ringLocation;
}

Vector2D Player::GetNetLocation()
{
	return netLocation;
}
