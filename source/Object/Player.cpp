#include "DxLib.h"

#include "Player.h"
#include "ObjectManager.h"
#include "../Scene/InGameScene.h"
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

	m_maxSpeed = 330.0f;	// 最大速度
	m_radius = 30.0f;	// 半径

	// 虫網
	m_stickLength = 100.0f;	// 虫網（棒）の長さ
	m_netLength = 55.0f;		// 網の終点までの長さ

	m_ringVector = { 0.0f, 0.0f };	// プレイヤーを基準とした虫網（リング）の中心の座標
	m_netLocation = m_location;	// 網の終点座標（膨らんでいる部分）

	m_ringRadius = 27.0f;// リングの半径

	// 虫網（リング）の太さ
	m_ringThickness = m_ringRadius;

	m_stickAngle = 0.0f;	// 棒の角度

	m_netRadius = 0.0f;	// 網の終点の半径

	// スティックの倒しこみ（ 1 ～ -1 ）
	m_tiltStick = 0.0f;
	m_oldTiltStick = 0.0f;
	// スティックの角度（90°= 1）
	m_rotateStick = 0.0f;
	m_oldRotateStick = 0.0f;
	m_valueRotateStick = 0.0f;

	m_ringSpeed = 0.0f;	// リングの速度

	m_walkingFlag = false;	// 歩くフラグ
	m_holdingFlag = false;	// 虫網を持つフラグ
	m_oldHoldingFlag = false;	// 前フレームの虫網を持つフラグ
	m_reverseFlag = false;	// 反転フラグ
	m_pullTheNetFlag = false;	// 虫網を引くフラグ
	m_rotatingThrustFlag = false;	// 回転させながら出すフラグ
	m_isSneak = true;	// 忍び足

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

	Vector2D treeHit = {};
	do
	{
		treeHit = ObjectManager::TreeHitCheck(m_location, m_radius, false);
		m_location = Vec2Add(m_location, treeHit);
	} while (treeHit.x != 0.0f && treeHit.y != 0.0f);

	m_moveSpeed = { 0.0f, 0.0f };	// 動く速度

	// 虫網
	m_ringVector = { 0.0f, 0.0f };	// プレイヤーを基準とした虫網（リング）の中心の座標
	m_netLocation = m_location;	// 網の終点座標（膨らんでいる部分）

	// 虫網（リング）の太さ
	m_ringThickness = m_ringRadius;

	m_stickAngle = 0.0f;	// 棒の角度

	m_netRadius = 0.0f;	// 網の終点の半径

	// スティックの倒しこみ（ 1 ～ -1 ）
	m_tiltStick = 0.0f;
	m_oldTiltStick = 0.0f;
	// スティックの角度（90°= 1）
	m_rotateStick = 0.0f;
	m_oldRotateStick = 0.0f;
	m_valueRotateStick = 0.0f;

	m_ringSpeed = 0.0f;	// リングの速度

	m_walkingFlag = false;	// 歩くフラグ
	m_holdingFlag = false;	// 虫網を持つフラグ
	m_oldHoldingFlag = false;	// 前フレームの虫網を持つフラグ
	m_reverseFlag = false;	// 反転フラグ
	m_pullTheNetFlag = false;	// 虫網を引くフラグ
	m_rotatingThrustFlag = false;	// 回転させながら出すフラグ
	m_isSneak = true;	// 忍び足

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
	float stickThickness = 5.0f;

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
			Camera::DrawGraphW(backArmLocation, 2.0f, 2.0f, stickRotate + 1.0f * DX_PI_F, m_armImage);
		}
		// 虫網を持つ手が前なら
		else
		{
			// 腕を表示
			Camera::DrawGraphW(backArmLocation, 2.0f, 2.0f, 0.0f, m_armImage);
		}
	}
	// 虫網を持っていないなら
	else
	{
		// 構えていない虫網を表示
		Camera::DrawGraphW(frontArmLocation, 2.0f, 2.0f, (0.2f - 0.4f * (int)m_reverseFlag) * DX_PI_F, m_netImage, m_reverseFlag);

		// 腕を表示
		Camera::DrawGraphW(backArmLocation, 2.0f, 2.0f, 0.0f, m_armImage);
	}

	// 脚表示
	Camera::DrawGraphW(m_location, 2.0f, 2.0f, 0.0f, m_legImage[m_legSubscript], m_reverseFlag);
	// 体表示
	Camera::DrawGraphW(m_location, 2.0f, 2.0f, 0.0f, m_bodyImage, m_reverseFlag);
	// 顔表示
	// 虫網を持っているかつ、虫網を持つ手が後ろなら
	if(m_holdingFlag && isBackHolding)
	{
		// 後ろ向きの顔を表示
		Camera::DrawGraphW(m_location, 2.0f, 2.0f, 0.0f, m_headImage[3], m_reverseFlag);
	}
	else
	{
		// 前向きの顔を表示
		Camera::DrawGraphW(m_location, 2.0f, 2.0f, 0.0f, m_headImage[m_headSubscript], m_reverseFlag);
	}

	// 前の腕表示
	// 虫網を持っているなら
	if (m_holdingFlag)
	{
		// 虫網を持つ手が後ろなら
		if (isBackHolding)
		{
			Camera::DrawGraphW(frontArmLocation, 2.0f, 2.0f, 0.0f, m_armImage);
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
			Camera::DrawGraphW(frontArmLocation, 2.0f, 2.0f, stickRotate + 1.0f * DX_PI_F, m_armImage);
			// 網を表示
			DrawNet(ringLocation);
		}
	}
	// 虫網を持っていないなら
	else
	{
		// 腕を表示
		Camera::DrawGraphW(frontArmLocation, 2.0f, 2.0f, 0.0f, m_armImage);
	}
}

void Player::DrawNet(Vector2D ringLocation) const
{
	Vector2D point[4];
	// 虫網のリング（緑の部分）の太さ
	float ringThickness = 5.0f;

	point[0].x = ringLocation.x + sinf(m_rotateStick) * (m_tiltStick * m_ringRadius + 3.0f);
	point[0].y = ringLocation.y - cosf(m_rotateStick) * (m_tiltStick * m_ringRadius + 3.0f);

	point[1].x = ringLocation.x - sinf(m_rotateStick) * (m_tiltStick * m_ringRadius + 3.0f);
	point[1].y = ringLocation.y + cosf(m_rotateStick) * (m_tiltStick * m_ringRadius + 3.0f);

	point[2].x = ringLocation.x + sinf(m_rotateStick + 0.5f * DX_PI_F) * (m_ringRadius - fabsf(m_ringThickness) + 3.0f);
	point[2].y = ringLocation.y - cosf(m_rotateStick + 0.5f * DX_PI_F) * (m_ringRadius - fabsf(m_ringThickness) + 3.0f);

	point[3].x = ringLocation.x - sinf(m_rotateStick + 0.5f * DX_PI_F) * (m_ringRadius - fabsf(m_ringThickness) + 3.0f);
	point[3].y = ringLocation.y + cosf(m_rotateStick + 0.5f * DX_PI_F) * (m_ringRadius - fabsf(m_ringThickness) + 3.0f);

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

	// ネットの終点を丸くする
	float angle = VecATan2(ringLocation, m_netLocation);
	Camera::DrawCircleW(m_netLocation, m_netRadius, 0xffffff, true, 1.0f);//, angle - 0.5f * DX_PI_F, angle + 0.5f * DX_PI_F);
	for (int i = 0;i < 4;i++)
	{
		float len = Length(Vec2Sub(m_netLocation, point[i]));
		Vector2D p[2];

		angle = VecATan2(m_netLocation, point[i]);
		float value = atanf(len / m_netRadius);

		for (int j = 0;j < 2;j++)
		{
			p[j] = m_netLocation;
			p[j].x += sinf(angle + value) * (m_netRadius);
			p[j].y -= cosf(angle + value) * (m_netRadius);
			value *= -1;
		}

		Camera::DrawTriangleW(point[i], p[0], p[1], 0xffffff);
	}
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
	leftStick.y *= -1.0f;

	float acceleration = 2700.0f * delta;
	float deceleration = 1300.0f * delta;

	m_isSneak = GetButtonState(XINPUT_BUTTON_RIGHT_SHOULDER) == eHeld;
	float max = m_maxSpeed;
	if(m_isSneak)
	{
		acceleration *= 0.5f;
		deceleration *= 0.5f;

		max *= 0.5f;
	}

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
	float len = Length(m_moveSpeed);
	if (len > max)
	{
		float shiita = VecATan2(m_moveSpeed, { 0.0f,0.0f });
		len -= max;
		m_moveSpeed.x += sinf(shiita) * len;
		m_moveSpeed.y -= cosf(shiita) * len;
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

	m_location = Vec2Add(m_location, ObjectManager::TreeHitCheck(m_location, m_radius, false));

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
	m_oldHoldingFlag = m_holdingFlag;
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
	
	float ringAcceleration = 330.0f * delta;

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
		if(!m_oldHoldingFlag)
		{
			// 虫網の向きに足す値
			m_valueRotateStick = 0.5f * DX_PI_F;
			// 右を向いているとき
			if (m_reverseFlag)
			{
				// 掛ける値を反転
				m_valueRotateStick *= -1.0f;
			}

			// スティックを右側に倒したとき
			if (rightStick.x > 0.0f)
			{
				// 掛ける値を反転
				m_valueRotateStick *= -1.0f;
			}
			// スティックを下側に倒したとき
			if (rightStick.y > 0.0f)
			{
				// 掛ける値を反転
				m_valueRotateStick *= -1.0f;
			}

			// 回転させながら出す
			m_rotatingThrustFlag = true;
		}

		// 虫網を引くとき
		if (m_pullTheNetFlag)
		{
			// スティック倒しこみが90%以上なら
			if (m_tiltStick > 0.9f)
			{
				// 回しながら引く
				m_rotatingThrustFlag = false;
			}
		}

		// 回しながら出す
		if (m_rotatingThrustFlag)
		{
			// プレイヤーに近いほど90°ずらす
			m_rotateStick += m_valueRotateStick * (1.0f - m_tiltStick);
		}
		// 回しながら引く
		else
		{
			// プレイヤーに近いほど90°ずらす
			m_rotateStick -= m_valueRotateStick * (1.0f - m_tiltStick);
		}

		// 虫網を構える
		m_holdingFlag = true;

		// リングの移動
		// リングが、倒したい位置に無かった場合
		if (Length(Vec2Sub(m_ringVector, Vec2Mult(rightStick, m_stickLength))) > 0.06f)
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
		float ringDistance;	// 網からリングへの距離
		float ringUnderDistance;	// 網からリングの下への距離

		// 重力で落ちる表現
		Vector2D ringUnderLocation = { ringLocation.x, ringLocation.y + m_netLength };
		// 網からリングの下への向き
		netAngle = VecATan2(m_netLocation, ringUnderLocation);
		// 網からリングへの距離
		ringDistance = Length(Vec2Sub(m_netLocation, ringLocation));
		// 網からリングの下への距離
		ringUnderDistance = Length(Vec2Sub(m_netLocation, ringUnderLocation));

		
		// 移動
		FixGradually(m_netLocation.x, m_netLocation.x + sinf(netAngle) * ringUnderDistance, ringUnderDistance * delta);
		FixGradually(m_netLocation.y, m_netLocation.y - cosf(netAngle) * ringUnderDistance, ringUnderDistance * delta);

		// 網の長さ制限
		if (ringDistance > m_netLength)
		{
			// 網からリングへの向き
			netAngle = VecATan2(m_netLocation, ringLocation);

			m_netLocation.x += sinf(netAngle) * (ringDistance - m_netLength);
			m_netLocation.y -= cosf(netAngle) * (ringDistance - m_netLength);
		}

		m_netRadius = (1.0f - Length(Vec2Sub(m_netLocation, ringLocation)) / m_netLength) * m_ringRadius;
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

Vector2D Player::GetLocation() const
{
	return m_location;
}

float Player::GetRadius() const
{
	return m_radius;
}

float Player::GetStickmLength() const
{
	return m_stickLength;
}

bool Player::GetNetHolding() const
{
	return m_holdingFlag;
}

bool Player::GetSneak() const
{
	return m_isSneak;
}

void Player::MoveLocation(Vector2D vector)
{
	m_location = Vec2Add(m_location, vector);
}
