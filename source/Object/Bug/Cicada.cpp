#include "DxLib.h" 
#include "Math.h"

#include "../../Utilitys/Math.h"
#include "../../Utilitys/Random.h"
#include "../../Utilitys/Camera.h"

#include "../../Scene/InGameScene.h"

#include "Cicada.h"

#include "../Tree.h"

Cicada::Cicada() : Bug()
{

	// 察知範囲
	m_detectionRange = 200.0f;
}
Cicada::~Cicada()
{
}

void Cicada::Update(float delta)
{
	Animation(delta);

	// 出現しているなら
	if (m_isAppearance)
	{
		if (m_isBack)
		{
			PutInFront();
		}

		// 逃げているなら
		if (m_isEscape)
		{
			Escape(delta);
		}
		// 逃げていないなら
		else
		{
			switch (m_state)
			{
			case eStand:
				Stand(delta);

				break;
			case eMove:
				Patrol(delta);

				break;
			case ePanic:
				Panic(delta);

				break;
			}

			PerceptionJudgment();
		}

		Bug::Update(delta);
	}
	else
	{
		if (m_transitionTime <= 0.0f)
		{
			ReSpawn(delta);
		}
	}
}

void Cicada::DrawOnTheBack() const
{
	// 出現しているかつ、背面なら
	if (m_isAppearance && m_isBack)
	{
		Camera::DrawCircleW(m_location, 20, GetColor(0, 0, 255));
	}
}

void Cicada::Draw() const
{
	// 出現しているかつ、背面ではないならなら
	if (m_isAppearance && !m_isBack)
	{
		Camera::DrawCircleW(m_location, 20, GetColor(0, 0, 255));
	}
}

void Cicada::Spawn()
{
	// スポーン位置
	Vector2D location = Bug::RandomLocationOnTheScreen();

	// 位置を近くの木に設定する
	location = FindNearestTree(location);
	// 位置を少しずらす
	location.x += (float)((Random::GetRand() % D_TREE_WIDTH) - (D_TREE_WIDTH / 2));
	location.y += (float)((Random::GetRand() % D_TREE_HEIGHT) - (D_TREE_HEIGHT / 2));

	// スポーン
	Set(location);
}

void Cicada::ReSpawn(float delta)
{
	Spawn();

	// 画面内なら木の裏に
	if (Camera::CheckItsOnTheScreen(m_location, 20.0f))
	{
		m_isBack = true;
	}
}

void Cicada::SetDestination(Vector2D location)
{
	// 近くの木を目的地にする
	m_destination = FindNearestTree(location);

	// 目的地をランダムに座標をずらす
	m_destination.x += (float)((Random::GetRand() % D_TREE_WIDTH) - (D_TREE_WIDTH / 2));
	m_destination.y += (float)((Random::GetRand() % D_TREE_HEIGHT) - (D_TREE_HEIGHT / 2));
}

void Cicada::Animation(float delta)
{
	Bug::Animation(delta);


}

void Cicada::Escape(float delta)
{
	// 向きをプレイヤーから虫への向きに
	m_direction = FindTheAngle(targetPlayer->GetPlayerLocation(), m_location);

	// 加速度
	float acceleration = 200.0f;
	// 最大速度
	float maxSpeed = 800.0f;
	// 減速度
	float deceleration = 100.0f;

	// 加速
	Acceleration(acceleration, maxSpeed, m_direction, delta);
	// 減速
	Deceleration(deceleration, delta);

	// 逃げる状態からパニック状態へ
	// プレイヤーの座標
	Vector2D playerLocation = targetPlayer->GetPlayerLocation();
	float len = Length(Vec2Sub(m_location, playerLocation));
	// プレイヤー察知
	// 察知範囲から出た時
	if (len > m_detectionRange)
	{
		// 察知時間が0以下なら
		if (m_detectionTime <= 0.0f)
		{
			// パニック状態へ
			m_isEscape = false;
			m_state = ePanic;

			// 遷移時間を0.1fごとに区切った1.0f~5.0fにする
			int r = Random::GetRand() % 40;
			m_transitionTime = (float)r / 10.0f + 1.0f;
		}
	}
	else
	{
		// 察知時間を0.1fごとに区切った0.0f~1.0fにする
		int r = Random::GetRand() % 10;
		m_detectionTime = (float)r / 10.0f;
	}
}

void Cicada::Stand(float delta)
{
	m_moveSpeed = { 0.0f, 0.0f };
	if (m_transitionTime <= 0.0f)
	{
		// 巡回状態へ
		m_state = eMove;
		// 向きを0.25πごとに区切ったランダムな向きに
		int r = Random::GetRand() % 8;
		m_direction = (float)r / 4.0f * DX_PI_F;
		// ランダムな木を目的地に設定
		SetDestination(RandomLocationOnTheScreen());

	}
}

void Cicada::Patrol(float delta)
{
	// 加速度
	float acceleration = 100.0f;
	// 最大速度
	float maxSpeed = 500.0f;
	// 減速度
	float deceleration = 50.0f;

	// 目的地に向ける
	m_direction = FindTheAngle(m_location, m_destination);

	// 加速
	Acceleration(acceleration, maxSpeed, m_direction, delta);
	// 減速
	Deceleration(deceleration, delta);

	if (Length(Vec2Sub(m_location, m_destination)) < 1.0f)
	{
		// 目的地についたら待機状態へ
		m_location = m_destination;
		m_moveSpeed = { 0.0f, 0.0f };
		m_state = eStand;

		// 遷移時間を0.1fごとに区切った10.0f~30.0fにする
		int r = Random::GetRand() % 200;
		m_transitionTime = (float)r / 10.0f + 10.0f;
	}
}

void Cicada::Panic(float delta)
{
	// 向きを0.125fπごとに区切った-3.0fπ~3.0fπずらす
	int r = Random::GetRand() % 48;
	m_direction += ((float)r / 8.0f - 3.0f) * DX_PI_F * delta;

	// 加速度
	float acceleration = 200.0f;
	// 最大速度
	float maxSpeed = 800.0f;
	// 減速度
	float deceleration = 100.0f;

	// 加速
	Acceleration(acceleration, maxSpeed, m_direction, delta);
	// 減速
	Deceleration(deceleration, delta);

	// 遷移時間が0以下なら
	if (m_transitionTime <= 0.0f)
	{
		// 巡回状態へ
		m_state = eMove;
		// 近くの木を目的地に設定
		SetDestination(m_location);
	}
}

void Cicada::PerceptionJudgment()
{
	Vector2D playerLocation = targetPlayer->GetPlayerLocation();
	float len = Length(Vec2Sub(m_location, playerLocation));

	// プレイヤー察知
	// 察知範囲に入った時
	if (len < m_detectionRange)
	{
		// 察知班にの1/2に入った時
		if (len < m_detectionRange / 2.0f)
		{
			// 逃げ状態へ
			TransitionToEscape();
		}
		else
		{
			// 察知時間が0以下なら
			if (m_detectionTime <= 0.0f)
			{
				TransitionToEscape();
			}
		}
	}
	else
	{
		// 察知時間を0.1fごとに区切った0.0f~2.0fにする
		int r = Random::GetRand() % 20;
		m_detectionTime = (float)r / 10.0f;
	}
}

void Cicada::TransitionToEscape()
{
	m_isEscape = true;
	// 察知時間を0.1fごとに区切った0.0f~1.0fにする
	int r = Random::GetRand() % 10;
	m_detectionTime = (float)r / 10.0f;
}

void Cicada::PutInFront()
{
	Vector2D treeLocation = FindNearestTree(m_location);

	// その木から離れたら、前面に置く
	if (m_location.x + 20 < treeLocation.x - D_TREE_WIDTH ||
		m_location.x - 20 > treeLocation.x + D_TREE_WIDTH ||
		m_location.y + 20 < treeLocation.y - D_TREE_HEIGHT ||
		m_location.y - 20 > treeLocation.y + D_TREE_HEIGHT)
	{
		m_isBack = false;
	}
}
