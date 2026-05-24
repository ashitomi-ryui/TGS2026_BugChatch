#include "DxLib.h"
#include "math.h"

#include "../../Utilitys/Math.h"
#include "../../Utilitys/Random.h"
#include "../../Utilitys/Camera.h"

#include "../../Scene/InGameScene.h"

#include "Grasshopper.h"

#include "../Leaf.h"
#include "../Tree.h"

#define NOMINMAX
#include <cmath>

int Grasshopper::images[7] = { -1,-1,-1,-1,-1,-1,-1};

Grasshopper::Grasshopper() : Bug()
{
	// 察知範囲
	m_detectionRange = 300.0f * D_OBJECT_SIZE_RATIO;
	joutai = notjump;
}
Grasshopper::~Grasshopper()
{

}

void Grasshopper::Init()
{
	images[0] = LoadGraph("assets/images/Bugs/Grasshopper/Grasshopper1.PNG");
	images[1] = LoadGraph("assets/images/Bugs/Grasshopper/Grasshopper2.PNG");
	images[2] = LoadGraph("assets/images/Bugs/Grasshopper/Grasshopper3.PNG");
	images[3] = LoadGraph("assets/images/Bugs/Grasshopper/Grasshopper4.PNG");
	images[4] = LoadGraph("assets/images/Bugs/Grasshopper/Jump1.PNG");
	images[5] = LoadGraph("assets/images/Bugs/Grasshopper/Jump2.PNG");
	images[6] = LoadGraph("assets/images/Bugs/Grasshopper/Jump3.PNG");

	grasshopperGetCount = 0;
}

void Grasshopper::Update(float delta)
{
	Animation(delta);

	// 出現しているなら
	if (m_isAppearance)
	{
		// 木の裏にいる
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
				Move(delta);

				break;
			case ePanic:
				Panic(delta);

				break;
			}

			PerceptionJudgment();
		}

		Bug::Update(delta);

		// 当たり判定
		if (HitCheck())
		{
			cicadaGetCount += 1;
			m_isAppearance = false;
			// 遷移時間を1.0f秒にする
			m_transitionTime = 1.0f;
		}
	}
	else
	{
		if (m_transitionTime <= 0.0f)
		{
			ReSpawn(delta);
		}
	}
}

void Grasshopper::Draw() const
{
	/*DrawFormatString(50, 50, GetColor(255, 0, 0), "%f", m_transitionTime);
	DrawFormatString(50, 100, GetColor(255, 0, 0), "%f", m_location.x);
	DrawFormatString(50, 150, GetColor(255, 0, 0), "%f", m_location.y);
	DrawFormatString(50, 200, GetColor(255, 0, 0), "%f", shiita);
	DrawFormatString(50, 250, GetColor(255, 0, 0), "%f", m_moveSpeed.x);
	DrawFormatString(50, 300, GetColor(255, 0, 0), "%f", m_destination.x);*/
	Camera::DrawGraphW(m_location, 3.0f * D_OBJECT_SIZE_RATIO, m_Angle, images[m_animCount], false);
}

void Grasshopper::DrawOnTheBack() const
{
	// 出現しているかつ、背面なら
	if (m_isAppearance && m_isBack)
	{
		Draw();
	}
}

void Grasshopper::DrawOnTheFront() const
{
	// 出現しているかつ、背面ではないならなら
	if (m_isAppearance && !m_isBack)
	{
		Draw();
	}
}

void Grasshopper::Spawn()
{
	// スポーン位置
	Vector2D location = Bug::RandomLocationOnTheScreen();

	// 位置を近くの木に設定する
	location = FindNearestTree(location);
	// 位置を少しずらす
	location.x += Random::GetRand((D_TREE_WIDTH / 2), -(D_TREE_WIDTH / 2));
	location.y += Random::GetRand((D_TREE_HEIGHT / 2), -(D_TREE_HEIGHT / 2));

	// スポーン
	Set(location);
}

void Grasshopper::ReSpawn(float delta)
{
	Spawn();

	// 画面内なら木の裏に
	if (Camera::CheckItsOnTheScreen(m_location, m_radius))
	{
		m_isBack = true;
	}
}

void Grasshopper::SetDestination(Vector2D location)
{
	//向き
	m_direction = Random::GetRand(0.0f, 2.0f, 0.1f) * DX_PI_F;

	//移動距離
	float distance = Random::GetRand(50.0f, 300.0f, 0.1f);

	// 目的地
	m_destination.x = location.x + cosf(m_direction) * distance;
	m_destination.y = location.y + sinf(m_direction) * distance;

	m_startLocation = location;

	// 速さ
	m_moveSpeed.x = Random::GetRand(0.5f, 1.0f, 0.1f);

	top = Random::GetRand(20.0, 50.0, 0.1f);

	//// 最小頂点
	//float min_y = std::fminf(0.0f, m_destination.y + 25.0f);
	//if (m_destination.y + 25.0f >= 50.0f)
	//{
	//	min_y = 25.0f;
	//}

	//// 最大頂点
	//float max_y = m_destination.y + 50.0f;
	//if (max_y >= 50.0f)
	//{
	//	max_y = 50.0f;
	//}

	


	//// 加速度
	//float acceleration = 2000.0f * Random::GetRand(100.0f);

	///*m_destination.x = m_location.x - Random::GetRand(100.0f, 50.0f);
	//m_destination.y = m_location.y - Random::GetRand(100.0f, 50.0f);*/

	//m_moveSpeed = { acceleration, -Random::GetRand(100.0f) };

	//float min_y = std::;

}

void Grasshopper::Animation(float delta)
{
	Bug::Animation(delta);

	// 木の裏にいる
	if (m_isBack)
	{
		m_animCount = 0;
	}
	else
	{
		// 逃げているなら
		if (m_isEscape)
		{
			// 画像の切り替え
			if (m_animTime > 0.025f)
			{
				m_animTime = 0.0f;
				m_animCount = m_animCount % 4 + 1;
			}

			// 画像の向きを徐々に移動方向に向ける
			GraduallyTurn(m_Angle, m_direction, 2.0f * DX_PI_F * delta);
		}
		// 逃げていないなら
		else
		{
			switch (m_state)
			{
			case eStand:
				// 画像の切り替え
				if (m_animTime > 0.05f)
				{
					if (m_animCount != 0)
					{
						m_animTime = 0.0f;
						m_animCount = (m_animCount + 1) % 5;
					}
				}

				// 画像の向きを徐々に上に向ける
				GraduallyTurn(m_Angle, 0.0f, 2.0f * DX_PI_F * delta);

				break;
			case eMove:
				// 画像の切り替え
				if (m_animTime > 0.05f)
				{
					m_animTime = 0.0f;
					m_animCount = m_animCount % 4 + 1;
				}

				// 画像の向きを徐々に移動方向に向ける
				GraduallyTurn(m_Angle, m_direction, 2.0f * DX_PI_F * delta);

				break;
			case ePanic:
				// 画像の切り替え
				if (m_animTime > 0.025f)
				{
					m_animTime = 0.0f;
					m_animCount = m_animCount % 4 + 1;
				}

				// 画像の向きを徐々に移動方向に向ける
				GraduallyTurn(m_Angle, m_direction, 2.0f * DX_PI_F * delta);

				break;
			}
		}
	}
}

void Grasshopper::Escape(float delta)
{
	Vector2D playerLocation = targetPlayer->GetPlayerLocation();

	// 向きをプレイヤーから虫への向きに
	m_direction = VecATan2(playerLocation, m_location);
	// 向きを0.01fπごとに区切った-0.25fπ~0.25fπずらす
	m_direction += Random::GetRand(-0.25f, 0.25f, 0.1f) * DX_PI_F;

	// 加速度
	float acceleration = 2000.0f;
	// 最大速度
	float maxSpeed = 600.0f;
	// 減速度
	float deceleration = 400.0f;

	// 加速
	Acceleration(acceleration, maxSpeed, m_direction, delta);
	// 減速
	Deceleration(deceleration, delta);

	// 逃げる状態からパニック状態へ
	// プレイヤーの座標
	Vector2D ringLocation = targetPlayer->GetRingLocation();
	float playerLen = Length(Vec2Sub(m_location, playerLocation));
	float ringLen = Length(Vec2Sub(m_location, ringLocation));
	// プレイヤー察知
	// 察知範囲から出た時
	if (playerLen > m_detectionRange || ringLen > m_detectionRange)
	{
		// 察知時間が0以下なら
		if (m_detectionTime <= 0.0f)
		{
			// パニック状態へ
			m_isEscape = false;
			m_state = ePanic;

			// 遷移時間を0.1fごとに区切った2.0f~5.0fにする
			m_transitionTime = Random::GetRand(2.0f, 5.0f, 0.1f);
		}
	}
	else
	{
		// 察知時間を0.1fごとに区切った0.0f~1.0fにする
		m_detectionTime = Random::GetRand(0.0f, 1.0f, 0.1f);
	}
}

void Grasshopper::Stand(float delta)
{
	m_moveSpeed = { 0.0f, 0.0f };
	if (m_transitionTime <= 0.0f)
	{
		// 巡回状態へ
		m_state = eMove;
		// 向きを0.25πごとに区切ったランダムな向きに
		/*m_direction = Random::GetRand(0.0f, 2.0f, 0.25f) * DX_PI_F;*/
		// ランダムな木を目的地に設定
		SetDestination(m_location);
		shiita = 0;
		joutai = notjump;
		count = 0;
	}
}

void Grasshopper::Move(float delta)
{
	// delta（前フレームからの経過時間）を使って進行度を進める
	// shiita が 0.0 から 1.0 まで変化する
	shiita += m_moveSpeed.x * delta;

	if (shiita > 1.0f)
	{
		shiita = 1.0f; // 行き過ぎ防止
	}

	// 1. XとYの「水平な直線移動」を線形補間(Lerp)で計算
	m_location.x = m_startLocation.x + (m_destination.x - m_startLocation.x) * shiita;
	m_location.y = m_startLocation.y + (m_destination.y - m_startLocation.y) * shiita;

	// 2. Y軸にサインカーブ（放物線）の高さを上乗せする
	// sinf(shiita * DX_PI_F) は shiitaが 0.0(始点) -> 0.5(頂点) -> 1.0(終点) で 0 -> 1 -> 0 と変化します
	// ※ 2Dゲームで上がマイナス方向なら引く、プラス方向なら足す
	float height = sinf(shiita * DX_PI_F) * top;
	m_location.y -= height;

	// 着地判定（進行度が1.0に達したら終了）
	if (shiita >= 1.0f)
	{
		m_location = m_destination; // 座標を完全に目的地に合わせる
		m_moveSpeed = { 0.0f, 0.0f };
		m_state = eStand;
		m_transitionTime = Random::GetRand(20.0f, 5.0f, 0.1f);
	}


	//switch (joutai)
	//{
	//case notjump:
	//	joutai = jump;
	//	break;
	//case jump:
	//	shiita += m_moveSpeed.x * 0.05;
	//	/*m_location.x += (m_moveSpeed.x / (m_destination.x / 2)) * 0.05;*/
	//	m_location.y -= sinf(shiita) * (m_moveSpeed.x / top) * 0.05;
	//	if (shiita >= 0.5f)
	//	{
	//		shiita = 0;
	//		joutai = top_after;
	//	}
	//	break;
	//case top_after:
	//	shiita += m_moveSpeed.x * 0.05;
	//	m_location.y -= sinf(m_moveSpeed.x / (m_destination.y - top)) * 0.05;
	//	if (shiita >= 1.0f)
	//	{
	//		m_state = eStand;
	//	}
	//	break;
	//}

	//// 徐々に目的地に向ける
	//float destinationDirection = VecATan2(m_location, m_destination);
	//GraduallyTurn(m_direction, destinationDirection, 2.0f * DX_PI_F * delta);

	// 加速
	/*Acceleration(acceleration, maxSpeed, m_direction, delta);*/

	// 減速
	/*Deceleration(deceleration, delta);*/

	
	/*Vector2D treeLocation = FindNearestTree(m_location);*/
	if (Length(Vec2Sub(m_location, m_destination)) < 10.0f)
	{
		// 目的地についたら待機状態へ
		m_moveSpeed = { 0.0f, 0.0f };
		m_state = eStand;

		// 遷移時間を0.1fごとに区切った10.0f~30.0fにする
		m_transitionTime = Random::GetRand(10.0f, 30.0f, 0.1f);
	}
}

void Grasshopper::Panic(float delta)
{
	// 向きを0.125fπごとに区切った-2.0fπ~2.0fπずらす
	m_direction += Random::GetRand(-2.0f, 2.0f, 0.125) * DX_PI_F * delta;

	// 加速度
	float acceleration = 2000.0f;
	// 最大速度
	float maxSpeed = 600.0f;
	// 減速度
	float deceleration = 400.0f;

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

void Grasshopper::PerceptionJudgment()
{
	Vector2D playerLocation = targetPlayer->GetPlayerLocation();
	Vector2D ringLocation = targetPlayer->GetRingLocation();
	float playerLen = Length(Vec2Sub(m_location, playerLocation));
	float ringLen = Length(Vec2Sub(m_location, ringLocation));

	// プレイヤー察知
	// 察知範囲に入った時
	if (playerLen < m_detectionRange || ringLen < m_detectionRange)
	{
		// 察知班にの1/2に入った時
		if (playerLen < m_detectionRange / 2.0f || ringLen < m_detectionRange / 2.0f)
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
		m_detectionTime = Random::GetRand(0.0f, 2.0f, 0.1f);
	}
}

void Grasshopper::TransitionToEscape()
{
	m_isEscape = true;
	// 察知時間を0.1fごとに区切った0.0f~1.0fにする
	m_detectionTime = Random::GetRand(0.0f, 1.0f, 0.1f);
}

void Grasshopper::PutInFront()
{
	Vector2D treeLocation = FindNearestTree(m_location);

	// その木から離れたら、前面に置く
	if (m_location.x + m_radius < treeLocation.x - D_TREE_WIDTH ||
		m_location.x - m_radius > treeLocation.x + D_TREE_WIDTH ||
		m_location.y + m_radius < treeLocation.y - D_TREE_HEIGHT ||
		m_location.y - m_radius > treeLocation.y + D_TREE_HEIGHT)
	{
		m_isBack = false;
	}
}
