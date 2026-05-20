#include "DxLib.h"

#include "Bug.h"

#include "../../Utilitys/Camera.h"
#include "../../Utilitys/Random.h"


Player* Bug::targetPlayer;

int Bug::getCount = 0;

Bug::Bug()
{
	m_isAppearance = false;
	m_isEscape = false;
	m_state = eStand;
	m_isBack = false;
	m_location = { 0.0f, 0.0f };
	m_radius = 0.0f;
	m_direction = 0.0f;
	m_moveSpeed = { 0.0f, 0.0f };
	m_destination = { 0.0f, 0.0f };
	m_detectionRange = 0.0f;
	m_detectionTime = 0.0f;
	m_transitionTime = 0.0f;
	m_animTime = 0.0f;
	m_animCount = 0;
}
Bug::~Bug()
{
}

void Bug::Set(Vector2D location)
{
	// 出現している
	m_isAppearance = true;
	// 逃げていない
	m_isEscape = false;
	// 待機
	m_state = eStand;
	// 背面に描画するか
	m_isBack = false;
	// 座標
	m_location = location;
	// 半径
	m_radius = 20.0f;
	// 向き
	m_direction = 0.0f;
	// 動き
	m_moveSpeed = { 0.0f, 0.0f };
	// 目的地
	m_destination = { 0.0f, 0.0f };
	// 察知時間
	m_detectionTime = 0.0f;
	// 遷移時間を0.1fごとに区切った10.0f~30.0fにする
	int r = Random::GetRand() % 200;
	m_transitionTime = (float)r / 10.0f + 10.0f;
	// アニメーション
	m_animTime = 0.0f;
	m_animCount = 0;
}

void Bug::Update(float delta)
{
	// 移動
	m_location = Vec2Add(m_location, Vec2Mult(m_moveSpeed, delta));

	//ネットの位置を取得
	Vector2D netLocation = targetPlayer->GetRingLocation();
	float netRadius = targetPlayer->GetRingRadius();

	Bug::HitCheck(netLocation, netRadius);

	if (m_location.x + 300.0f < 0.0f || m_location.x - 300.0f > D_STAGE_WIDTH ||
		m_location.y + 300.0f < 0.0f || m_location.y - 300.0f > D_STAGE_HEIGHT)
	{
		m_isAppearance = false;
		// 遷移時間を1.0f秒にする
		m_transitionTime = 1.0f;
	}
}

void Bug::DrawOnTheBack() const
{
}

void Bug::Draw() const
{
}

void Bug::SetPlayer(Player* p)
{
	targetPlayer = p;
}

Vector2D Bug::RandomLocationOnTheScreen()
{
	Vector2D location;	// 位置
	// 位置を画面内のランダムな位置に設定する
	location.x = (float)(Random::GetRand() % (int)D_STAGE_WIDTH);
	location.y = (float)(Random::GetRand() % (int)D_STAGE_HEIGHT);
	return location;
}

void Bug::HitCheck(Vector2D netLocation, float netRadius)
{
	float len = Length(Vec2Sub(m_location, netLocation));
	if (len < netRadius)
	{
		getCount += 1;
		m_isAppearance = false;
		// 遷移時間を1.0f秒にする
		m_transitionTime = 1.0f;
	}
}

void Bug::Acceleration(float acceleration, float maxSpeed, float direction, float delta)
{
	m_moveSpeed.x += cosf(direction) * acceleration * delta;
	m_moveSpeed.y -= sinf(direction) * acceleration * delta;

	if (Length(m_moveSpeed) > maxSpeed)
	{
		float moveDirection = FindTheAngle({ 0.0f, 0.0f }, m_moveSpeed);
		m_moveSpeed.x = cosf(moveDirection) * maxSpeed;
		m_moveSpeed.y = -sinf(moveDirection) * maxSpeed;
	}
}

void Bug::Deceleration(float deceleration, float delta)
{
	// 減速
	// X座標を減速する
	if (m_moveSpeed.x > deceleration * delta)
	{
		m_moveSpeed.x -= deceleration * delta;
	}
	else if (m_moveSpeed.x < -deceleration * delta)
	{
		m_moveSpeed.x += deceleration * delta;
	}
	else
	{
		m_moveSpeed.x = 0.0f;
	}
	// Y座標を減速する
	if (m_moveSpeed.y > deceleration * delta)
	{
		m_moveSpeed.y -= deceleration * delta;
	}
	else if (m_moveSpeed.y < -deceleration * delta)
	{
		m_moveSpeed.y += deceleration * delta;
	}
	else
	{
		m_moveSpeed.y = 0.0f;
	}
}

void Bug::Animation(float delta)
{
	m_detectionTime -= delta;
	m_transitionTime -= delta;
	m_animTime += delta;
}
