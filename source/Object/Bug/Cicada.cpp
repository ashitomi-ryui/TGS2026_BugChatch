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
	// 最大速度
	m_maxSpeed = 1000.0f;

	// 察知範囲
	m_detectionRange = 50.0f;
}
Cicada::~Cicada()
{
}

void Cicada::Update(float delta)
{
	// 出現しているなら
	if (m_isAppearance)
	{
		// 逃げているなら
		if (m_isEscape)
		{
			Escape(delta);
		}
		// 逃げていないなら
		else
		{
			// とまっていないなら
			if (!m_isPerched)
			{
				float deceleration = 1.0f;	// 減速度

				// 徐々に目的地に向ける
				m_destination;

				Patrol(delta);


				// 減速
				Deceleration(deceleration, delta);
			}

			Vector2D playerLocation = targetPlayer->GetPlayerLocation();
			float len = Length(Vec2Sub(m_location, playerLocation));
			// プレイヤー察知
			if (len < m_detectionRange * 2)
			{
				int r = Random::GetRand() % (int)len;
				if (r == 0)
					m_isEscape = true;
			}
		}

		Bug::Update(delta);
	}
	else
	{

	}
}

void Cicada::Draw() const
{
	Camera::DrawCircleW(m_location, 20, GetColor(0, 0, 255));
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

void Cicada::ReSpawn()
{
	Spawn();

	// 画面内なら木の裏に
	if (Camera::CheckItsOnTheScreen(m_location))
	{
		m_isBack = true;
	}
}

void Cicada::Escape(float delta)
{
	// 加速度
	float acceleration;
	// 減速度
	float deceleration;


	m_location = Vec2Add(m_location, m_moveSpeed);
}

void Cicada::SetDestination(Vector2D location)
{
	// 近くの木を目的地にする
	m_destination = FindNearestTree(location);

	// 目的地をランダムに座標をずらす
	m_destination.x += (float)((Random::GetRand() % D_TREE_WIDTH) - (D_TREE_WIDTH / 2));
	m_destination.y += (float)((Random::GetRand() % D_TREE_HEIGHT) - (D_TREE_HEIGHT / 2));
}

void Cicada::Patrol(float delta)
{
	float travelDistance = 10.0f;	// 移動距離

	// 向いている方向に向かって移動する
	m_moveSpeed.x += sinf(m_direction) * travelDistance * delta;
	m_moveSpeed.y += cosf(m_direction) * travelDistance * delta;


}