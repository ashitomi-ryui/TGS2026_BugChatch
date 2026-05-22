#include "DxLib.h" 
#include "Math.h"

#include "../../Utilitys/Math.h"
#include "../../Utilitys/Random.h"
#include "../../Utilitys/Camera.h"

#include "../../Scene/InGameScene.h"

#include "Dragonfly.h"

#include "../Tree.h"



int Dragonfly::images[4] = { -1,-1,-1,-1 };

int a;

Dragonfly::Dragonfly() : Bug()
{
	// 察知範囲
	m_detectionRange = 300.0f * D_OBJECT_SIZE_RATIO;
}
Dragonfly::~Dragonfly()
{
}

void Dragonfly::Init()
{
	images[0] = LoadGraph("assets/images/Bugs/Dragonfly/Dragonfly1.PNG");
	images[1] = LoadGraph("assets/images/Bugs/Dragonfly/Dragonfly2.PNG");
	images[2] = LoadGraph("assets/images/Bugs/Dragonfly/Dragonfly3.PNG");
	images[3] = LoadGraph("assets/images/Bugs/Dragonfly/Dragonfly4.PNG");
	

	cicadaGetCount = 0;
}

void Dragonfly::Update(float delta)
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

void Dragonfly::Draw() const
{
	Camera::DrawGraphW(m_location, 3.0f * D_OBJECT_SIZE_RATIO, m_Angle, images[m_animCount], false);
}

void Dragonfly::DrawOnTheBack() const
{
	// 出現しているかつ、背面なら
	if (m_isAppearance && m_isBack)
	{
		Draw();
	}
}

void Dragonfly::DrawOnTheFront() const
{
	// 出現しているかつ、背面ではないならなら
	if (m_isAppearance && !m_isBack)
	{
		Draw();
	}
}

void Dragonfly::Spawn()
{
	// スポーン位置
	Vector2D location = Bug::RandomLocationOnTheScreen();

	// 位置を近くの木に設定する
	location = FindNearestTree(location);
	// 位置を少しずらす
	location.x += Random::GetRand((D_TREE_WIDTH / 2), -(D_TREE_WIDTH / 2));
	location.y += Random::GetRand((D_TREE_WIDTH / 2), -(D_TREE_WIDTH / 2));

	// スポーン
	Set(location);
}

void Dragonfly::ReSpawn(float delta)
{
	Spawn();

	// 画面内なら木の裏に
	if (Camera::CheckItsOnTheScreen(m_location, m_radius))
	{
		m_isBack = true;
	}
}

void Dragonfly::SetDestination(Vector2D location)
{
	// 近くの木を目的地にする
	m_destination = FindNearestTree(location);

	// 目的地をランダムに座標をずらす
	m_destination.x += Random::GetRand((D_TREE_WIDTH / 2), -(D_TREE_WIDTH / 2));
	m_destination.y += Random::GetRand((D_TREE_WIDTH / 2), -(D_TREE_WIDTH / 2));
}

void Dragonfly::Animation(float delta)
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

void Dragonfly::Escape(float delta)
{
	Vector2D playerLocation = targetPlayer->GetPlayerLocation();

	// 向きをプレイヤーから虫への向きに
	m_direction = VecATan2(playerLocation, m_location);
	// 向きを0.01fπごとに区切った-0.25fπ~0.25fπずらす
	m_direction += Random::GetRand(-0.25f, 0.25f, 0.01f) * DX_PI_F;

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

void Dragonfly::Stand(float delta)
{
	m_moveSpeed = { 0.0f, 0.0f };
	if (m_transitionTime <= 0.0f)
	{
		// 巡回状態へ
		m_state = eMove;
		// 向きを0.25πごとに区切ったランダムな向きに
		m_direction = Random::GetRand(0.0f, 2.0f, 0.25f) * DX_PI_F;
		// ランダムな木を目的地に設定
		SetDestination(RandomLocationOnTheScreen());

	}
}

void Dragonfly::Move(float delta)
{
	// 加速度
	float acceleration = 1000.0f;
	// 最大速度
	float maxSpeed = 400.0f;
	// 減速度
	float deceleration = 200.0f;

	// 徐々に目的地に向ける
	float destinationDirection = VecATan2(m_location, m_destination);
	GraduallyTurn(m_direction, destinationDirection, 2.0f * DX_PI_F * delta);

	// 加速
	Acceleration(acceleration, maxSpeed, m_direction, delta);
	// 減速
	Deceleration(deceleration, delta);

	Vector2D treeLocation = FindNearestTree(m_location);
	if (Length(Vec2Sub(m_location, m_destination)) < 10.0f &&
		m_location.x > treeLocation.x - D_TREE_WIDTH &&
		m_location.x < treeLocation.x + D_TREE_WIDTH &&
		m_location.y > treeLocation.y - D_TREE_HEIGHT &&
		m_location.y < treeLocation.y + D_TREE_HEIGHT)
	{
		// 目的地についたら待機状態へ
		m_moveSpeed = { 0.0f, 0.0f };
		m_state = eStand;

		// 遷移時間を0.1fごとに区切った10.0f~30.0fにする
		m_transitionTime = Random::GetRand(10.0f, 30.0f, 0.1f);
	}
}

void Dragonfly::Panic(float delta)
{
	// 向きを0.125fπごとに区切った-2.0fπ~2.0fπずらす
	m_direction += Random::GetRand(-2.0f, 2.0f, 0.125f) * DX_PI_F * delta;

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

void Dragonfly::PerceptionJudgment()
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

void Dragonfly::TransitionToEscape()
{
	m_isEscape = true;
	// 察知時間を0.1fごとに区切った0.0f~1.0fにする
	m_detectionTime = Random::GetRand(0.0f, 1.0f, 0.1f);
}

void Dragonfly::PutInFront()
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


//#include "../../Scene/InGameScene.h"
//
//#include "Cicada.h"
//
//#include "../Tree.h"
//
//float count = 0;
//bool flag;
//bool flag2;
//int abura;
//float r;
//int hanten = FALSE;
//
//Tonbo::Tonbo():Bug(),
//      m_moveSpeed(0.0f)
//	, animation_data()
//	, animation_count(0)
//	, animation_number(0)
//{
//
//}
//
//int Tonbo::Initialize()
//{
//	animation_data[0] = LoadGraph("assets/Dragonfly1.PNG");
//	animation_data[1] = LoadGraph("assets/Dragonfly2.PNG");
//	animation_data[2] = LoadGraph("assets/Dragonfly3.PNG");
//	animation_data[3] = LoadGraph("assets/Dragonfly4.PNG");
//	image = animation_data[animation_number];
//	if (image == -1)
//	{
//		return FALSE;
//	}
//
//	return TRUE;
//}
//
//Vector2D Tonbo::Update(float delta)
//{
//
//
//	
//	count += delta;
//	Animation();
//	if (count >= 3.0f && flag == FALSE)
//	{
//		velocity.x = GetRand(1);
//		velocity.y = GetRand(1);
//		if (velocity.x == 0)
//		{
//			velocity.x = -1;
//		}
//		if (velocity.y == 0)
//		{
//			velocity.y = -1;
//		}
//		flag = TRUE;
//		flag2 = FALSE;
//	}
//	if (count >= 5.0f)
//	{
//		flag2 = TRUE;
//	}
//
//	if (count >= 6.5f)
//	{
//		count = 0;
//		flag = FALSE;
//	}
//	if (location.x <= 10)
//	{
//		location.x = 10;
//	}
//	if (location.x >= 630)
//	{
//		location.x = 630;
//	}
//	if (location.y <= 10)
//	{
//		location.y = 10;
//	}
//	if (location.y >= 470)
//	{
//		location.y = 470;
//	}
//	if (flag2 == TRUE)
//	{
//		abura = GetRand(2);
//		if (abura == 2)
//		{
//			abura = -1;
//		}
//		location += abura;
//	}
//
//	
//
//	if (velocity.x == -1)
//	{
//		hanten = FALSE;
//	}
//	else
//	{
//		hanten = TRUE;
//	}
//	
//
//	if (flag2 == FALSE)
//	{
//		location += velocity;
//	}
//
//	return location;
//
//}
//
//
//void Tonbo::Draw() const
//{
//
//
//	DrawRotaGraph(location.x, location.y, 5.0, r, image, TRUE, hanten);
//
//
//	//DrawCircleAA(location.x, location.y, 15, 50, GetColor(255, 255, 255),TRUE);
//	DrawPixel(500, 240, GetColor(0, 255, 255));
//
//	DrawFormatString(50, 50, GetColor(255, 0, 0), "%f", count);
//	DrawFormatString(50, 80, GetColor(255, 0, 0), "%f", r);
//
//}
//void Tonbo::Movemation()
//{
//
//}
//void Tonbo::SetLocation(float x, float y)
//{
//	location.x = 320;
//	location.y = 240;
//}
//void Tonbo::SetLocation(Vector2D vec)
//{
//	location = vec;
//}
//void Tonbo::Animation()
//{
//	animation_count = (animation_count + 1) % 15;
//	if (animation_count == 0)
//	{
//		animation_number = (animation_number + 1) % 4;
//	}
//	image = animation_data[animation_number];
//}