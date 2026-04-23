#include "DxLib.h"
#include <math.h>
#include <stdlib.h>

#include "Player.h"

Player::Player()
{
	score = 0;	// スコア
	// 座標
	// プレイヤーキャラ
	m_location = { 640.0f, 360.0f };	// プレイヤーの座標
	m_moveSpeed = { 0.0f, 0.0f };	// 動く速度
	m_maxSpeed = 3.0f;

	// 虫網
	m_stickLength = 150.0f;	// 虫網（棒）の長さ
	m_netLength = 40.0f;		// 網の終点までの長さ

	m_ringVector = { 0.0f, 0.0f };	// プレイヤーを基準とした虫網（リング）の中心の座標
	m_netLocation = { 640.0f, 360.0f + m_netLength};	// 虫網（リング）を基準とした網の終点（膨らんでいる部分）

	m_ringRadius = 40.0f;// リングの半径

	// 虫網（リング）の3D座標
	m_ringThickness = m_ringRadius;

	m_stickAngle = 1.0f;	// 棒の角度

	// スティックの倒しこみ（ 1 ～ -1 ）
	m_tiltStick = 0.0f;
	m_oldTiltStick;
	// スティックの角度（90°= 1）
	m_rotateStick = 0.0f;
	m_oldRotateStick;
}

Player::Player::~Player()
{
}

void Player::Update()
{
	float acceleration = 0.5f;
	float deceleration = 0.2f;

	Vector2D leftStick = GetLeftStick();
	Vector2D rightStick = GetRightStick();

	leftStick.y *= -1;
	rightStick.y *= -1;

	// 加速
	// スティック
	m_moveSpeed = Vec2Add(m_moveSpeed, Vec2Mult(leftStick, acceleration));

	// 減速
	if (m_moveSpeed.x > deceleration)
	{
		m_moveSpeed.x -= deceleration;
	}
	else if (m_moveSpeed.x < -deceleration)
	{
		m_moveSpeed.x += deceleration;
	}
	else
	{
		m_moveSpeed.x = 0;
	}
	if (m_moveSpeed.y > deceleration)
	{
		m_moveSpeed.y -= deceleration;
	}
	else if (m_moveSpeed.y < -deceleration)
	{
		m_moveSpeed.y += deceleration;
	}
	else
	{
		m_moveSpeed.y = 0;
	}

	// 最大速度調整
	if (m_moveSpeed.x > m_maxSpeed)
	{
		m_moveSpeed.x = m_maxSpeed;
	}
	if (m_moveSpeed.x < -m_maxSpeed)
	{
		m_moveSpeed.x = -m_maxSpeed;
	}
	if (m_moveSpeed.y > m_maxSpeed)
	{
		m_moveSpeed.y = m_maxSpeed;
	}
	if (m_moveSpeed.y < -m_maxSpeed)
	{
		m_moveSpeed.y = -m_maxSpeed;
	}


	m_location = Vec2Add(m_location, m_moveSpeed);

	if (m_location.x < 25.0f)
	{
		m_location.x = 25.0f;
		m_moveSpeed.x = 0.0f;
	}
	else if (m_location.x > 1280.0f - 25.0f)
	{
		m_location.x = 1280.0f - 25.0f;
		m_moveSpeed.x = 0.0f;
	}
	if (m_location.y < 25.0f)
	{
		m_location.y = 25.0f;
		m_moveSpeed.y = 0.0f;
	}
	else if (m_location.y > 720.0f - 25.0f)
	{
		m_location.y = 720.0f - 25.0f;
		m_moveSpeed.y = 0.0f;
	}

	// 虫網
	m_ringVector = Vec2Mult(rightStick, m_stickLength);
	
	m_oldTiltStick = m_tiltStick;
	m_oldRotateStick = m_rotateStick;
	m_tiltStick = sqrtf(LengthSq(Vec2Sub({ 0.0f, 0.0f }, rightStick)));
	m_rotateStick = FindTheAngle({ 0.0f, 0.0f }, rightStick);
	if (m_tiltStick == 0.0f)
	{
		m_rotateStick = m_oldRotateStick;
		m_ringThickness = m_ringRadius;
	}
	else
	{
		// リングの太さ
		m_ringThickness += fabs(m_tiltStick - m_oldTiltStick) * m_ringRadius;
		m_ringThickness -= fabs(m_rotateStick - m_oldRotateStick) * m_ringRadius;

		// 虫網を回す最小値、最大値を設定
		if (m_ringThickness < 0.0f)
		{
			m_ringThickness = 0.0f;
		}
		else if (m_ringThickness > m_ringRadius)
		{
			m_ringThickness = m_ringRadius;
		}
	}
	
	Vector2D ringLocation = Vec2Add(m_location, m_ringVector);	// リングの位置
	float netDistance;	// リングと網の距離
	float netAngle;
	netDistance = sqrtf(LengthSq(Vec2Sub(m_netLocation, ringLocation)));
	if (netDistance > m_netLength)
	{
		netAngle = FindTheAngle(m_netLocation, ringLocation);

		m_netLocation.x += sinf(netAngle) * (netDistance - m_netLength);
		m_netLocation.y += cosf(netAngle) * (netDistance - m_netLength);
	}
}

void Player::Draw() const
{
	DrawCircle(m_location.x, m_location.y, 25, 0x00ffff, true);
	
	Vector2D point[4];
	Vector2D ringLocation = Vec2Add(m_location, m_ringVector);

	DrawLine(m_location.x, m_location.y, ringLocation.x, ringLocation.y, 0x00ff00, 5);

	point[0].x = ringLocation.x + sinf(m_rotateStick) * (m_tiltStick * m_ringRadius + 10.0f);
	point[0].y = ringLocation.y + cosf(m_rotateStick) * (m_tiltStick * m_ringRadius + 10.0f);
	
	point[1].x = ringLocation.x - sinf(m_rotateStick) * (m_tiltStick * m_ringRadius + 10.0f);
	point[1].y = ringLocation.y - cosf(m_rotateStick) * (m_tiltStick * m_ringRadius + 10.0f);

	point[2].x = ringLocation.x + sinf(m_rotateStick + 1.0f) * (m_ringThickness + 10.0f);
	point[2].y = ringLocation.y + cosf(m_rotateStick + 1.0f) * (m_ringThickness + 10.0f);

	point[3].x = ringLocation.x - sinf(m_rotateStick + 1.0f) * (m_ringThickness + 10.0f);
	point[3].y = ringLocation.y - cosf(m_rotateStick + 1.0f) * (m_ringThickness + 10.0f);

	DrawTriangle(point[0].x, point[0].y, point[2].x, point[2].y, m_netLocation.x, m_netLocation.y, 0xffffff, true);
	DrawTriangle(point[1].x, point[1].y, point[3].x, point[3].y, m_netLocation.x, m_netLocation.y, 0xffffff, true);
	DrawTriangle(point[2].x, point[2].y, point[1].x, point[1].y, m_netLocation.x, m_netLocation.y, 0xffffff, true);
	DrawTriangle(point[3].x, point[3].y, point[0].x, point[0].y, m_netLocation.x, m_netLocation.y, 0xffffff, true);
	//DrawCircle(point[0].x, point[0].y, 5, 0xffffff, true);
	//DrawCircle(point[1].x, point[1].y, 5, 0xffffff, true);
	//DrawCircle(point[2].x, point[2].y, 5, 0xffffff, true);
	//DrawCircle(point[3].x, point[3].y, 5, 0xffffff, true);
	//DrawFormatString(100, 400, 0xffffff, "%.2f %.2f ", tiltStick, rotateStick);
	//DrawFormatString(100, 450, 0xffffff, "%.2f %.2f ", tiltStick, rotateStick);
	//DrawFormatString(100, 500, 0xffffff, "%.2f", ringThickness);
}

Vector2D Player::GetRingLocation() const
{
	Vector2D ringLocation = Vec2Add(m_location, m_ringVector);
	return ringLocation;
}

float Player::GetMaxSpeed() const
{
	return m_maxSpeed;
}