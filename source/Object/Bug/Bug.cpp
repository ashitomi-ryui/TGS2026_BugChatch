#include "DxLib.h"

#include "Bug.h"

#include "Cicada.h"

#include "../../Scene/InGameScene.h"
#include "../../Utilitys/Camera.h"
#include "../../Utilitys/Random.h"


Player* Bug::targetPlayer;

Bug::Bug()
{
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
	// 止まっている
	m_isPerched = true;
	// 裏側に表示しない
	m_isBack = false;
	// 座標
	m_location = location;
	// 向き
	m_direction = 0.0f;
	// 動き
	m_moveSpeed = { 0.0f, 0.0f };
	// 目的地
	m_destination = { 0.0f, 0.0f };
}

void Bug::Update(float delta)
{
	//ネットの位置を取得
	Vector2D netLocation = targetPlayer->GetRingLocation();
	float netRadius = targetPlayer->GetRingRadius();

	Bug::HitCheck(netLocation, netRadius);
}

void Bug::Draw()
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
	location.x = (float)(Random::GetRand() % D_STAGE_WIDTH);
	location.y = (float)(Random::GetRand() % D_STAGE_HEIGHT);
	return location;
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

void Bug::HitCheck(Vector2D netLocation, float netRadius)
{
	float len = Length(Vec2Sub(m_location, netLocation));
	if (len < netRadius)
	{

	}
}