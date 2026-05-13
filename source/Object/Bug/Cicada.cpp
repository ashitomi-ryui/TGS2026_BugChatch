#include "DxLib.h" 
#include "Math.h"

#include "../../Utilitys/Math.h"
#include "../../Utilitys/Random.h"
#include "../../Utilitys/Camera.h"

#include "../../Scene/InGameScene.h"

//#include "Bug.h"
#include "Cicada.h"

#include "../Tree.h"

Cicada::Cicada()
{
	// 最大速度
	cicada.m_maxSpeed = 1000.0f;

	// 察知範囲
	cicada.m_detectionRange = 50.0f;
}
Cicada::~Cicada()
{
}

void Cicada::Update(float delta)
{
	// 出現しているなら
	if (cicada.m_isAppearance)
	{
		// 逃げているなら
		if (cicada.m_isEscape)
		{
			Escape(delta);
		}
		// 逃げていないなら
		else
		{
			// とまっていないなら
			if (!cicada.m_isPerched)
			{
				float deceleration = 1.0f;	// 減速度

				// 徐々に目的地に向ける
				cicada.m_destination;

				Patrol(delta);


				// 減速
				cicada.Deceleration(deceleration, delta);
			}

			Vector2D playerLocation = cicada.targetPlayer->GetPlayerLocation();
			float len = Length(Vec2Sub(cicada.m_location, playerLocation));
			// プレイヤー察知
			if (len < cicada.m_detectionRange * 2)
			{
				int r = Random::GetRand() % (int)len;
				if (r == 0)
					cicada.m_isEscape = true;
			}
		}

		cicada.Update(delta);
	}
	else
	{

	}
}

void Cicada::Draw()
{
	Camera::DrawCircleW(cicada.m_location, 20, GetColor(0, 0, 255));
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
	cicada.Set(location);
}

void Cicada::ReSpawn()
{
	Spawn();

	// 画面内なら木の裏に
	if (Camera::CheckItsOnTheScreen(cicada.m_location))
	{
		cicada.m_isBack = true;
	}
}

void Cicada::Escape(float delta)
{
	// 加速度
	float acceleration;
	// 減速度
	float deceleration;


	cicada.m_location = Vec2Add(cicada.m_location, cicada.m_moveSpeed);
}

void Cicada::SetDestination(Vector2D location)
{
	// 近くの木を目的地にする
	cicada.m_destination = FindNearestTree(location);

	// 目的地をランダムに座標をずらす
	cicada.m_destination.x += (float)((Random::GetRand() % D_TREE_WIDTH) - (D_TREE_WIDTH / 2));
	cicada.m_destination.y += (float)((Random::GetRand() % D_TREE_HEIGHT) - (D_TREE_HEIGHT / 2));
}

void Cicada::Patrol(float delta)
{
	float travelDistance = 10.0f;	// 移動距離

	// 向いている方向に向かって移動する
	cicada.m_moveSpeed.x += sinf(cicada.m_direction) * travelDistance * delta;
	cicada.m_moveSpeed.y += cosf(cicada.m_direction) * travelDistance * delta;


}