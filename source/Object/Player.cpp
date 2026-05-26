#include "DxLib.h"

#include "Player.h"
#include "../Utilitys/Camera.h"
#include "../Utilitys/Random.h"

int Player::m_headImage[3] = {};
int Player::m_bodyImage = -1;
int Player::m_legImage[4] = {};
int Player::m_armImage = -1;

Player::Player()
{
	score = 0;
	m_location = { 640.0f, 360.0f };
	m_moveSpeed = {};

	m_maxSpeed = 500.0f * D_OBJECT_SIZE_RATIO;	// 最大速度
	m_radius = 45.0f * D_OBJECT_SIZE_RATIO;	// 半径

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
	m_walkingFlag = false;	// 歩くフラグ
	m_holdingFlag = false;	// 虫網を持つフラグ
	m_reverseFlag = false;	// 反転フラグ

	m_blinkTime = 0.0f;		// 瞬き時間
	m_headAnimTime = 0.0f;	// 頭の時間
	m_headAnimCount = 0;	// 頭のカウント
	m_headSubscript = 0;	// 頭の添え字
	m_legAnimTime = 0.0f;	// 脚の時間
	m_legAnimCount = 0;		// 脚のカウント
	m_legSubscript = 0;		// 脚の添え字
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
	m_walkingFlag = false;	// 歩くフラグ
	m_holdingFlag = false;	// 虫網を持つフラグ
	m_reverseFlag = false;	// 反転フラグ

	m_blinkTime = 0.0f;		// 瞬き時間
	m_headAnimTime = 0.0f;	// 頭の時間
	m_headAnimCount = 0;	// 頭のカウント
	m_headSubscript = 0;	// 頭の添え字
	m_legAnimTime = 0.0f;	// 脚の時間
	m_legAnimCount = 0;		// 脚のカウント
	m_legSubscript = 0;		// 脚の添え字

	// 画像情報
	m_headImage[0] = LoadGraph("assets/images/Player/Head1.PNG");
	m_headImage[1] = LoadGraph("assets/images/Player/Head2.PNG");
	m_headImage[2] = LoadGraph("assets/images/Player/Head3.PNG");

	m_bodyImage = LoadGraph("assets/images/Player/Body.PNG");

	m_legImage[0] = LoadGraph("assets/images/Player/Leg1.PNG");
	m_legImage[1] = LoadGraph("assets/images/Player/Leg2.PNG");
	m_legImage[2] = LoadGraph("assets/images/Player/Leg3.PNG");
	m_legImage[3] = LoadGraph("assets/images/Player/Leg4.PNG");

	m_armImage = LoadGraph("assets/images/Player/Arm.PNG");
}

void Player::Update(float delta)
{
	Animation(delta);

	Move(delta);
	Net(delta);
}

void Player::Draw() const
{
	Vector2D backArmLocation = m_location;
	Vector2D frontArmLocation = m_location;
	bool isBackHolding = false;	// 後ろで持つ
	Vector2D ringLocation = Vec2Add(m_location, m_ringVector);
	float stickRotate;

	// 持ち手の設定
	if (m_ringVector.y < 0)
	{
		isBackHolding = true;
	}

	// 腕の位置をずらす
	if (m_reverseFlag)
	{
		backArmLocation.x += 8.0f;
		frontArmLocation.x -= 8.0f;
	}
	else
	{
		backArmLocation.x -= 8.0f;
		frontArmLocation.x += 8.0f;
	}
	backArmLocation.y += 2.0f;
	frontArmLocation.y += 2.0f;

	// 後ろの腕表示
	// 虫網を持っているなら
	if(m_holdingFlag)
	{
		// 虫網を持つ手が後ろなら
		if (isBackHolding)
		{
			// 棒の向きを設定
			stickRotate = VecATan2(backArmLocation, ringLocation);
			// 棒を表示
			Camera::DrawLineW(backArmLocation, ringLocation, 0x007700, 4);
			Camera::DrawLineW(backArmLocation, ringLocation, 0x00ff00, 3);
			// 網を表示
			DrawNet(ringLocation, stickRotate);
			// 腕を表示
			Camera::DrawGraphW(backArmLocation, 3.0f * D_OBJECT_SIZE_RATIO, stickRotate + 1.0f * DX_PI_F, m_armImage);
		}
		// 虫網を持つ手が前なら
		else
		{
			// 腕を表示
			Camera::DrawGraphW(backArmLocation, 3.0f * D_OBJECT_SIZE_RATIO, 0.0f, m_armImage);
		}
	}
	// 虫網を持っていないなら
	else
	{
		// 腕を表示
		Camera::DrawGraphW(backArmLocation, 3.0f * D_OBJECT_SIZE_RATIO, 0.0f, m_armImage);
	}

	// 半径表示
	Camera::DrawCircleW(m_location, m_radius, 0x777777, false);

	// 脚表示
	Camera::DrawGraphW(m_location, 3.0f * D_OBJECT_SIZE_RATIO, 0.0f, m_legImage[m_legSubscript], m_reverseFlag);
	// 体表示
	Camera::DrawGraphW(m_location, 3.0f * D_OBJECT_SIZE_RATIO, 0.0f, m_bodyImage, m_reverseFlag);
	// 顔表示
	Camera::DrawGraphW(m_location, 3.0f * D_OBJECT_SIZE_RATIO, 0.0f, m_headImage[m_headSubscript], m_reverseFlag);

	// 前の腕表示
	// 虫網を持っているなら
	if(m_holdingFlag)
	{
		// 虫網を持つ手が後ろなら
		if(isBackHolding)
		{
			Camera::DrawGraphW(frontArmLocation, 3.0f * D_OBJECT_SIZE_RATIO, 0.0f, m_armImage);
		}
		// 虫網を持つ手が前なら
		else
		{
			// 棒の向きを設定
			stickRotate = VecATan2(frontArmLocation, ringLocation);
			// 棒を表示
			Camera::DrawLineW(frontArmLocation, ringLocation, 0x007700, 4);
			Camera::DrawLineW(frontArmLocation, ringLocation, 0x00ff00, 3);
			// 腕を表示
			Camera::DrawGraphW(frontArmLocation, 3.0f * D_OBJECT_SIZE_RATIO, stickRotate + 1.0f * DX_PI_F, m_armImage);
			// 網を表示
			DrawNet(ringLocation, stickRotate);
		}
	}
	// 虫網を持っていないなら
	else
	{
		// 腕を表示
		Camera::DrawGraphW(frontArmLocation, 3.0f * D_OBJECT_SIZE_RATIO, 0.0f, m_armImage);
	}
}

void Player::DrawNet(Vector2D ringLocation, float stickRotate) const
{
	Vector2D point[4];

	point[0].x = ringLocation.x + sinf(stickRotate) * (m_tiltStick * m_ringRadius + 5.0f * D_OBJECT_SIZE_RATIO);
	point[0].y = ringLocation.y - cosf(stickRotate) * (m_tiltStick * m_ringRadius + 5.0f * D_OBJECT_SIZE_RATIO);

	point[1].x = ringLocation.x - sinf(stickRotate) * (m_tiltStick * m_ringRadius + 5.0f * D_OBJECT_SIZE_RATIO);
	point[1].y = ringLocation.y + cosf(stickRotate) * (m_tiltStick * m_ringRadius + 5.0f * D_OBJECT_SIZE_RATIO);

	point[2].x = ringLocation.x + sinf(stickRotate + 0.5f * DX_PI_F) * (m_ringThickness + 5.0f * D_OBJECT_SIZE_RATIO);
	point[2].y = ringLocation.y - cosf(stickRotate + 0.5f * DX_PI_F) * (m_ringThickness + 5.0f * D_OBJECT_SIZE_RATIO);

	point[3].x = ringLocation.x - sinf(stickRotate + 0.5f * DX_PI_F) * (m_ringThickness + 5.0f * D_OBJECT_SIZE_RATIO);
	point[3].y = ringLocation.y + cosf(stickRotate + 0.5f * DX_PI_F) * (m_ringThickness + 5.0f * D_OBJECT_SIZE_RATIO);

	Camera::DrawTriangleW(point[0], point[2], m_netLocation, 0xffffff);
	Camera::DrawTriangleW(point[1], point[3], m_netLocation, 0xffffff);
	Camera::DrawTriangleW(point[2], point[1], m_netLocation, 0xffffff);
	Camera::DrawTriangleW(point[3], point[0], m_netLocation, 0xffffff);
}

void Player::Animation(float delta)
{
	// 瞬きのアニメーション
	if (m_blinkTime > 0.0f)
	{
		m_blinkTime -= delta;
	}
	// 瞬き時間が0以下なら瞬き
	else
	{
		m_headAnimTime += delta;

		if (m_headAnimTime >= 0.1f)
		{
			m_headAnimCount++;

			if (m_headAnimCount <= 2)
			{
				m_headSubscript = m_headAnimCount;
			}
			else if (m_headAnimCount == 3)
			{
				m_headSubscript = 1;
			}
			else
			{
				m_headSubscript = 0;
				m_headAnimCount = 0;
				// 瞬き時間をランダムにする
				m_blinkTime = Random::GetRand(10.0f, 0.5f, 0.5f);
			}

			m_headAnimTime = 0.0f;
		}
	}

	// 歩くアニメーション
	if (m_walkingFlag)
	{
		m_legAnimTime += delta;

		if (m_legAnimTime >= 0.2f)
		{
			m_legAnimCount++;

			if (m_legAnimCount <= 2)
			{
				m_legSubscript = m_legAnimCount + 1;
			}
			else if (m_legAnimCount == 3)
			{
				m_legSubscript = 2;
			}
			else
			{
				m_legSubscript = 1;
				m_legAnimCount = 0;
			}

			m_legAnimTime = 0.0f;
		}
	}
	else
	{
		m_legSubscript = 0;
		m_legAnimCount = 0;
		m_legAnimTime = 0.0f;
	}
}

void Player::Move(float delta)
{
	Vector2D leftStick = GetLeftStick();
	leftStick.y *= -1;

	float acceleration = 4000.0f * delta * D_OBJECT_SIZE_RATIO;
	float deceleration = 2000.0f * delta * D_OBJECT_SIZE_RATIO;

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

	// 歩くアニメーション
	if (m_moveSpeed.x != 0 || m_moveSpeed.y != 0)
	{
		m_walkingFlag = true;

		// 画像反転
		if (m_moveSpeed.x < 0)
		{
			m_reverseFlag = false;
		}
		else if (m_moveSpeed.x > 0)
		{
			m_reverseFlag = true;
		}
	}
	else
	{
		m_walkingFlag = false;
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

}

void Player::Net(float delta)
{
	Vector2D rightStick = GetRightStick();
	rightStick.y *= -1;

	// 虫網を構えるアニメーション
	if (rightStick.x != 0 || rightStick.y != 0)
	{
		m_holdingFlag = true;
	}
	else
	{
		m_holdingFlag = false;
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
