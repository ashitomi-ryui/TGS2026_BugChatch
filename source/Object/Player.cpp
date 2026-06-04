#include "DxLib.h"

#include "Player.h"
#include "../Utilitys/Camera.h"
#include "../Utilitys/Random.h"

int Player::m_headImage[4] = {};
int Player::m_bodyImage = -1;
int Player::m_legImage[4] = {};
int Player::m_armImage = -1;
int Player::m_netImage = -1;

Player::Player()
{
	score = 0;
	m_location = { 640.0f, 360.0f };
	m_moveSpeed = {};

	m_maxSpeed = 500.0f * D_OBJECT_SIZE_RATIO;	// 最大速度
	m_radius = 45.0f * D_OBJECT_SIZE_RATIO;	// 半径

	// 虫網
	m_stickLength = 150.0f * D_OBJECT_SIZE_RATIO;	// 虫網（棒）の長さ
	m_netLength = 80.0f * D_OBJECT_SIZE_RATIO;		// 網の終点までの長さ

	m_ringVector = { 0.0f, 0.0f };	// プレイヤーを基準とした虫網（リング）の中心の座標
	m_netLocation = Vec2Mult(m_location, m_netLength);	// 網の終点座標（膨らんでいる部分）

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

	m_ringSpeed = 0.0f;	// リングの速度

	m_walkingFlag = false;	// 歩くフラグ
	m_holdingFlag = false;	// 虫網を持つフラグ
	m_reverseFlag = false;	// 反転フラグ
	m_pullTheNetFlag = false;	// 虫網を引くフラグ

	// アニメーション
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
	m_netLocation = Vec2Mult(m_location, m_netLength);	// 網の終点座標（膨らんでいる部分）

	// 虫網（リング）の太さ
	m_ringThickness = m_ringRadius;

	m_stickAngle = 0.0f;	// 棒の角度

	// スティックの倒しこみ（ 1 ～ -1 ）
	m_tiltStick = 0.0f;
	m_oldTiltStick = 0.0f;
	// スティックの角度（90°= 1）
	m_rotateStick = 0.0f;
	m_oldRotateStick = 0.0f;

	m_ringSpeed = 0.0f;	// リングの速度

	m_walkingFlag = false;	// 歩くフラグ
	m_holdingFlag = false;	// 虫網を持つフラグ
	m_reverseFlag = false;	// 反転フラグ
	m_pullTheNetFlag = false;	// 虫網を引くフラグ

	// アニメーション
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
	m_headImage[3] = LoadGraph("assets/images/Player/Head4.PNG");

	m_bodyImage = LoadGraph("assets/images/Player/Body.PNG");

	m_legImage[0] = LoadGraph("assets/images/Player/Leg1.PNG");
	m_legImage[1] = LoadGraph("assets/images/Player/Leg2.PNG");
	m_legImage[2] = LoadGraph("assets/images/Player/Leg3.PNG");
	m_legImage[3] = LoadGraph("assets/images/Player/Leg4.PNG");

	m_armImage = LoadGraph("assets/images/Player/Arm.PNG");

	m_netImage = LoadGraph("assets/images/Player/BugNet.PNG");
}

void Player::Update(float delta)
{
	Animation(delta);

	Move(delta);
	Net(delta);
}

void Player::Draw() const
{
	// 後ろの腕のずらす位置
	Vector2D backArmLocation = m_location;
	// 前の腕のずらす位置
	Vector2D frontArmLocation = m_location;
	// 後ろで持つかどうか
	bool isBackHolding = false;
	// 虫網の座標
	Vector2D ringLocation = Vec2Add(m_location, m_ringVector);
	// 虫網の向き
	float stickRotate;
	// 虫網の棒の太さ
	float stickThickness = 8.0f * D_OBJECT_SIZE_RATIO;

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
	if (m_holdingFlag)
	{
		// 虫網を持つ手が後ろなら
		if (isBackHolding)
		{
			// 棒の向きを設定
			stickRotate = VecATan2(backArmLocation, ringLocation);
			// 棒を表示
			Camera::DrawLineW(backArmLocation, ringLocation, 0x007700, stickThickness);
			Camera::DrawLineW(backArmLocation, ringLocation, 0x00ff00, stickThickness - 2.0f);
			// 網を表示
			DrawNet(ringLocation);
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
		// 構えていない虫網を表示
		Camera::DrawGraphW(frontArmLocation, 3.0f * D_OBJECT_SIZE_RATIO, (0.2f - 0.4f * (int)m_reverseFlag) * DX_PI_F, m_netImage, m_reverseFlag);

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
	// 虫網を持っているかつ、虫網を持つ手が後ろなら
	if(m_holdingFlag && isBackHolding)
	{
		// 後ろ向きの顔を表示
		Camera::DrawGraphW(m_location, 3.0f * D_OBJECT_SIZE_RATIO, 0.0f, m_headImage[3], m_reverseFlag);
	}
	else
	{
		// 前向きの顔を表示
		Camera::DrawGraphW(m_location, 3.0f * D_OBJECT_SIZE_RATIO, 0.0f, m_headImage[m_headSubscript], m_reverseFlag);
	}

	// 前の腕表示
	// 虫網を持っているなら
	if (m_holdingFlag)
	{
		// 虫網を持つ手が後ろなら
		if (isBackHolding)
		{
			Camera::DrawGraphW(frontArmLocation, 3.0f * D_OBJECT_SIZE_RATIO, 0.0f, m_armImage);
		}
		// 虫網を持つ手が前なら
		else
		{
			// 棒の向きを設定
			stickRotate = VecATan2(frontArmLocation, ringLocation);
			// 棒を表示
			Camera::DrawLineW(frontArmLocation, ringLocation, 0x007700, stickThickness);
			Camera::DrawLineW(frontArmLocation, ringLocation, 0x00ff00, stickThickness - 2.0f);
			// 腕を表示
			Camera::DrawGraphW(frontArmLocation, 3.0f * D_OBJECT_SIZE_RATIO, stickRotate + 1.0f * DX_PI_F, m_armImage);
			// 網を表示
			DrawNet(ringLocation);
		}
	}
	// 虫網を持っていないなら
	else
	{
		// 腕を表示
		Camera::DrawGraphW(frontArmLocation, 3.0f * D_OBJECT_SIZE_RATIO, 0.0f, m_armImage);
	}
}

void Player::DrawNet(Vector2D ringLocation) const
{
	Vector2D point[4];
	// 虫網のリング（緑の部分）の太さ
	float ringThickness = 8.0f * D_OBJECT_SIZE_RATIO;

	point[0].x = ringLocation.x + sinf(m_rotateStick) * (m_tiltStick * m_ringRadius + 5.0f * D_OBJECT_SIZE_RATIO);
	point[0].y = ringLocation.y - cosf(m_rotateStick) * (m_tiltStick * m_ringRadius + 5.0f * D_OBJECT_SIZE_RATIO);

	point[1].x = ringLocation.x - sinf(m_rotateStick) * (m_tiltStick * m_ringRadius + 5.0f * D_OBJECT_SIZE_RATIO);
	point[1].y = ringLocation.y + cosf(m_rotateStick) * (m_tiltStick * m_ringRadius + 5.0f * D_OBJECT_SIZE_RATIO);

	point[2].x = ringLocation.x + sinf(m_rotateStick + 0.5f * DX_PI_F) * (m_ringRadius - fabsf(m_ringThickness) + 5.0f * D_OBJECT_SIZE_RATIO);
	point[2].y = ringLocation.y - cosf(m_rotateStick + 0.5f * DX_PI_F) * (m_ringRadius - fabsf(m_ringThickness) + 5.0f * D_OBJECT_SIZE_RATIO);

	point[3].x = ringLocation.x - sinf(m_rotateStick + 0.5f * DX_PI_F) * (m_ringRadius - fabsf(m_ringThickness) + 5.0f * D_OBJECT_SIZE_RATIO);
	point[3].y = ringLocation.y + cosf(m_rotateStick + 0.5f * DX_PI_F) * (m_ringRadius - fabsf(m_ringThickness) + 5.0f * D_OBJECT_SIZE_RATIO);

	// リングの表示
	Camera::DrawLineW(point[0], point[2], 0x00ff00, ringThickness - 2.0f);
	Camera::DrawLineW(point[0], point[3], 0x00ff00, ringThickness - 2.0f);
	Camera::DrawLineW(point[1], point[2], 0x00ff00, ringThickness - 2.0f);
	Camera::DrawLineW(point[1], point[3], 0x00ff00, ringThickness - 2.0f);

	// 網の表示
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
			// 左向き
			m_reverseFlag = false;
		}
		else if (m_moveSpeed.x > 0)
		{
			// 右向き
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

	m_oldTiltStick = m_tiltStick;
	m_oldRotateStick = m_rotateStick;
	m_tiltStick = Length(Vec2Sub({ 0.0f, 0.0f }, rightStick));
	m_rotateStick = VecATan2({ 0.0f, 0.0f }, rightStick);
	
	// 前の倒しこみより今の倒しこみが大きければ
	if (m_tiltStick > m_oldTiltStick)
	{
		// 虫網を引いていない
		m_pullTheNetFlag = false;
	}
	// 前の倒しこみより今の倒しこみが小されば
	else if (m_tiltStick < m_oldTiltStick)
	{
		// 虫網を引いている
		m_pullTheNetFlag = true;
	}

	float multiplier = 1.0f;	// 掛ける値
	// 右を向いているとき
	if (m_reverseFlag)
	{
		// 掛ける値を反転
		multiplier *= -1.0f;
	}
	// スティックを右側に倒したとき
	if (rightStick.x > 0.0f)
	{
		// 掛ける値を反転
		multiplier *= -1.0f;
	}
	// スティックを下側に倒したとき
	if (rightStick.y > 0.0f)
	{
		// 掛ける値を反転
		multiplier *= -1.0f;
	}
	// 虫網を引くとき
	if(m_pullTheNetFlag)
	{
		// 掛ける値を反転
		multiplier *= -1.0f;
	}

	// プレイヤーに近いほど90°ずらす
	m_rotateStick += 0.5f * DX_PI_F * (1.0f - m_tiltStick) * multiplier;
	

	float ringAcceleration = 500.0f * delta * D_OBJECT_SIZE_RATIO;

	// スティックが倒されていないなら
	if (Length(Vec2Sub({ 0.0f, 0.0f }, rightStick)) == 0.0f && Length(Vec2Sub({ 0.0f, 0.0f }, m_ringVector)) == 0.0f)
	{
		// 虫網を持たない
		m_holdingFlag = false;

		// 虫網（リング）の初期化
		m_ringThickness = 0.0f;
		m_ringSpeed = 0.0f;
		m_ringVector = { 0.0f, 0.0f };

		// 網の最短位置初期化
		m_netLocation = m_location;
	}
	else
	{
		// 虫網を構える
		m_holdingFlag = true;

		// リングの移動
		// リングが、倒したい位置に無かった場合
		if (Length(Vec2Sub(m_ringVector, Vec2Mult(rightStick, m_stickLength))) > 0.1f * D_OBJECT_SIZE_RATIO)
		{
			// 加速
			m_ringSpeed += ringAcceleration;

			// 位置を変える
			FixGradually(m_ringVector.x, sinf(m_rotateStick) * m_tiltStick * m_stickLength, m_ringSpeed);
			FixGradually(m_ringVector.y, -cosf(m_rotateStick) * m_tiltStick * m_stickLength, m_ringSpeed);
		}
		else
		{
			// その位置にする
			m_ringSpeed = 0.0f;
			m_ringVector = Vec2Mult(rightStick, m_stickLength);
		}

		// リングの見た目の太さを、倒したり引いた時に太くする
		FixGradually(m_ringThickness, 0.0f, fabsf(m_tiltStick - m_oldTiltStick) * m_ringRadius);

		// リングが、プレイヤーと遠かったら
		if(Length(m_ringVector) > m_stickLength / 5.0f)
		{
			// リングの見た目の太さを、回した時に細く、反対側に回す時に太くする
			m_ringThickness += AngleSub(m_rotateStick, m_oldRotateStick) * m_ringRadius / 2.0f;
		}

		// リングの太さの最小値、最大値を設定
		if (m_ringThickness < -m_ringRadius)
		{
			m_ringThickness = -m_ringRadius;
		}
		else if (m_ringThickness > m_ringRadius)
		{
			m_ringThickness = m_ringRadius;
		}


		// 網の最端位置の移動
		Vector2D ringLocation = Vec2Add(m_location, m_ringVector);	// リングの位置
		float netAngle;		// 網の向き
		float netDistance;	// 網の距離

		// 重力で落ちる表現
		Vector2D ringUnderLocation = { ringLocation.x, ringLocation.y + m_netLength };
		// 網からリングの下への向き
		netAngle = VecATan2(m_netLocation, ringUnderLocation);
		// 網からリングの下への距離
		netDistance = Length(Vec2Sub(m_netLocation, ringUnderLocation));

		// 移動
		FixGradually(m_netLocation.x, m_netLocation.x + sinf(netAngle) * netDistance, netDistance * delta);
		FixGradually(m_netLocation.y, m_netLocation.y - cosf(netAngle) * netDistance, netDistance * delta);

		// 網の長さ制限
		// 網からリングへの距離
		netDistance = Length(Vec2Sub(m_netLocation, ringLocation));
		if (netDistance > m_netLength)
		{
			// 網からリングへの向き
			netAngle = VecATan2(m_netLocation, ringLocation);

			m_netLocation.x += sinf(netAngle) * (netDistance - m_netLength);
			m_netLocation.y -= cosf(netAngle) * (netDistance - m_netLength);
		}
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
