#include "DxLib.h"

#include "Player.h"
#include "../Utilitys/Camera.h"

Player::Player()
{
	score = 0;
	m_location = { 640.0f, 360.0f };
	m_moveSpeed = {};

	m_maxSpeed = 500.0f * D_OBJECT_SIZE_RATIO;	// 最大速度
	m_radius = 25.0f * D_OBJECT_SIZE_RATIO;	// 半径

	// 虫網
	m_stickLength = 150.0f * D_OBJECT_SIZE_RATIO;	// 虫網（棒）の長さ
	m_netLength = 60.0f * D_OBJECT_SIZE_RATIO;		// 網の終点までの長さ

	m_ringVector = { 0.0f, 0.0f };	// プレイヤーを基準とした虫網（リング）の中心の座標
	m_netLocation = Vec2Mult(m_location, m_netLength);	// 虫網（リング）を基準とした網の終点（膨らんでいる部分）

	m_ringRadius = 40.0f * D_OBJECT_SIZE_RATIO;// リングの半径

	// 虫網（リング）の太さ
	m_ringThickness = m_ringRadius;

	m_stickAngle = 0.0f;	// 棒の角度

	// スティックの倒しこみ（ 1 ～ -1 ）
	m_tiltStick = 0.0f;
	m_oldTiltStick = 0.0f;
	// スティックの角度（90°= 1）
	m_rotateStick = 0.0f;
	m_oldRotateStick = 0.0f;

	// アニメーション
	m_animTime = 0.0f;	// アニメーション時間
	m_animCount = 0;	// アニメーションカウント
}

Player::~Player()
{
}

void Player::Init()
{
	score = 0;	// スコア
	// 座標
	// プレイヤーキャラ
	m_location = { 640.0f, 360.0f };	// プレイヤーの座標
	m_moveSpeed = { 0.0f, 0.0f };	// 動く速度

	// 虫網
	m_ringVector = { 0.0f, 0.0f };	// プレイヤーを基準とした虫網（リング）の中心の座標
	m_netLocation = Vec2Mult(m_location, m_netLength);	// 虫網（リング）を基準とした網の終点（膨らんでいる部分）

	// 虫網（リング）の太さ
	m_ringThickness = m_ringRadius;

	m_stickAngle = 0.0f;	// 棒の角度

	// スティックの倒しこみ（ 1 ～ -1 ）
	m_tiltStick = 0.0f;
	m_oldTiltStick = 0.0f;
	// スティックの角度（90°= 1）
	m_rotateStick = 0.0f;
	m_oldRotateStick = 0.0f;

	// アニメーション
	m_animTime = 0.0f;	// アニメーション時間
	m_animCount = 0;	// アニメーションカウント
}

void Player::Update(float delta)
{
	float acceleration = 4000.0f * delta * D_OBJECT_SIZE_RATIO;
	float deceleration = 2000.0f * delta * D_OBJECT_SIZE_RATIO;

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


	m_location = Vec2Add(m_location, Vec2Mult(m_moveSpeed, delta));

	// 移動の限界
	if (m_location.x < m_radius)
	{
		m_location.x = m_radius;
		m_moveSpeed.x = 0.0f;
	}
	else if (m_location.x > D_STAGE_WIDTH - m_radius)
	{
		m_location.x = D_STAGE_WIDTH - m_radius;
		m_moveSpeed.x = 0.0f;
	}
	if (m_location.y < m_radius)
	{
		m_location.y = m_radius;
		m_moveSpeed.y = 0.0f;
	}
	else if (m_location.y > D_STAGE_HEIGHT - m_radius)
	{
		m_location.y = D_STAGE_HEIGHT - m_radius;
		m_moveSpeed.y = 0.0f;
	}

	// 虫網
	m_ringVector = Vec2Mult(rightStick, m_stickLength);
	
	m_oldTiltStick = m_tiltStick;
	m_oldRotateStick = m_rotateStick;
	m_tiltStick = Length(Vec2Sub({ 0.0f, 0.0f }, rightStick));
	m_rotateStick = VecATan2({ 0.0f, 0.0f }, rightStick);
	if (m_tiltStick == 0.0f)
	{
		m_rotateStick = m_oldRotateStick;
		m_ringThickness = m_ringRadius;
	}
	else
	{
		// リングの太さ
		m_ringThickness += fabsf(m_tiltStick - m_oldTiltStick) * m_ringRadius;
		m_ringThickness -= fabsf(m_rotateStick - m_oldRotateStick) * m_ringRadius;

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
	netDistance = Length(Vec2Sub(m_netLocation, ringLocation));
	if (netDistance > m_netLength)
	{
		netAngle = VecATan2(m_netLocation, ringLocation);

		m_netLocation.x += sinf(netAngle) * (netDistance - m_netLength);
		m_netLocation.y -= cosf(netAngle) * (netDistance - m_netLength);
	}
}

void Player::Draw() const
{
	Camera::DrawCircleW(m_location, m_radius, 0x00ffff);
	
	Vector2D point[4];
	Vector2D ringLocation = Vec2Add(m_location, m_ringVector);

	Camera::DrawLineW(m_location, ringLocation, 0x00ff00, 5);

	point[0].x = ringLocation.x + sinf(m_rotateStick) * (m_tiltStick * m_ringRadius + 10.0f * D_OBJECT_SIZE_RATIO);
	point[0].y = ringLocation.y - cosf(m_rotateStick) * (m_tiltStick * m_ringRadius + 10.0f * D_OBJECT_SIZE_RATIO);
	
	point[1].x = ringLocation.x - sinf(m_rotateStick) * (m_tiltStick * m_ringRadius + 10.0f * D_OBJECT_SIZE_RATIO);
	point[1].y = ringLocation.y + cosf(m_rotateStick) * (m_tiltStick * m_ringRadius + 10.0f * D_OBJECT_SIZE_RATIO);

	point[2].x = ringLocation.x + sinf(m_rotateStick + 0.5f * DX_PI_F) * (m_ringThickness + 10.0f * D_OBJECT_SIZE_RATIO);
	point[2].y = ringLocation.y - cosf(m_rotateStick + 0.5f * DX_PI_F) * (m_ringThickness + 10.0f * D_OBJECT_SIZE_RATIO);

	point[3].x = ringLocation.x - sinf(m_rotateStick + 0.5f * DX_PI_F) * (m_ringThickness + 10.0f * D_OBJECT_SIZE_RATIO);
	point[3].y = ringLocation.y + cosf(m_rotateStick + 0.5f * DX_PI_F) * (m_ringThickness + 10.0f * D_OBJECT_SIZE_RATIO);

	Camera::DrawTriangleW(point[0], point[2], m_netLocation, 0xffffff);
	Camera::DrawTriangleW(point[1], point[3], m_netLocation, 0xffffff);
	Camera::DrawTriangleW(point[2], point[1], m_netLocation, 0xffffff);
	Camera::DrawTriangleW(point[3], point[0], m_netLocation, 0xffffff);
}

Vector2D Player::GetRingLocation() const
{
	Vector2D ringLocation = Vec2Add(m_location, m_ringVector);
	return ringLocation;
}

float Player::GetRingRadius() const
{
	return m_ringRadius;
}

float Player::GetMaxSpeed() const
{
	return m_maxSpeed;
}

Vector2D Player::GetPlayerLocation() const
{
	return m_location;
}

float Player::GetPlayerRadius() const
{
	return m_radius;
}

void Player::PlayerLocationMove(Vector2D vector)
{
	m_location = Vec2Add(m_location, vector);
}
