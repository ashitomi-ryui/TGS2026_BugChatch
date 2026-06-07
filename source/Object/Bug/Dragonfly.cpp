#include "DxLib.h"
#include "Math.h"


#include "../../Utilitys/Math.h"
#include "../../Utilitys/Random.h"
#include "../../Utilitys/Camera.h"

#include "../../Scene/InGameScene.h"

#include "Dragonfly.h"

#include"../Tree.h"

int Dragonfly::images[4] = { -1,-1,-1,-1 };

Dragonfly::Dragonfly() : Bug()
{
	// 察知範囲
	m_detectionRange = 300.0f * D_OBJECT_SIZE_RATIO;

	m_destinationNum = 0;
	m_hoveringMove = 0.0f;
	m_hoveringTimeFlag = false;
	m_hoveringFlag = false;
	m_hovering = 0;
	m_isFlip = false;
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


	dragonflyGetCount = 0;
}

void Dragonfly::Update(float delta)
{
	m_hoveringMove += delta;
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
				if (m_hoveringFlag)
				{
					Hovering(delta);
				}
				else
				{
					Move(delta);
				}

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
			dragonflyGetCount += 1;
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
	Camera::DrawGraphW(m_location, 3.0f * D_OBJECT_SIZE_RATIO, m_Angle, images[m_animCount], m_isFlip, false);
	//DrawFormatString(50, 50, GetColor(255, 0, 0), "%d", m_state);

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


	// 目的地をランダムに座標をずらす
	m_destination.x += Random::GetRand((D_TREE_WIDTH / 2), -(D_TREE_WIDTH / 2));
	m_destination.y += Random::GetRand((D_TREE_HEIGHT / 2), -(D_TREE_HEIGHT / 2));
	// 位置を近くの木に設定する
	location = FindNearestTree(location);

	// スポーン
	Set(location);
}

void Dragonfly::ReSpawn(float delta)
{
	//Bug::Animation(delta);
	Spawn();

	// 画面内なら木の裏に
	if (Camera::CheckItsOnTheScreen(m_location, m_radius))
	{
		m_isBack = true;
	}
}

void Dragonfly::SetDestination()
{
	 //ランダムな位置を目的地にする
	/*for (int i = 0;i < 5;i++)
	{
		m_destinations[i] = Bug::RandomLocationOnTheScreen();
		m_isDestinations[i] = true;
	}*/


	Vector2D temp[5] = {};	// 仮の目的地
	bool m_isAlreadySet[5] = {};	// 設定済みかどうか

	// 仮の目的地に5つのランダムな点を設定する
	for (int i = 0;i < 5;i++)
	{
		temp[i] = RandomLocationOnTheScreen();
		m_isAlreadySet[i] = false;
	}

	Vector2D reference = m_location;	// 基準点
	float minLen;	// 最も近い距離

	// 仮の目的地のあてはめ
	// i = 目的地の添え字
	for (int i = 0;i < 5;i++)
	{
		// 最も近い距離の初期化
		minLen = -1.0f;

		// j = 参照する仮の目的地の添え字
		for (int j = 0;j < 5;j++)
		{
			// 並び替えがまだなら
			if(m_isAlreadySet[j] == false)
			{
				// 最も近い距離が未設定、または、基準点までの距離が最も近い距離より小さいなら
				if (minLen == -1.0f || minLen > Length(Vec2Sub(reference, temp[j])))
				{
					// 目的地をその点にする
					m_destinations[i] = temp[j];
					m_isAlreadySet[j] = true;
					// その点を基準点にする
					reference = temp[j];
				}
			}
		}
	}
	m_destinationNum = 0;
}

void Dragonfly::Animation(float delta)
{
	Bug::Animation(delta);

	// 逃げているなら
	if (m_isEscape)
	{
		// 画像の切り替え
		if (m_animTime > 0.025f)
		{
			m_animTime = 0.0f;
			m_animCount = m_animCount % 2;
		}
	}
	// 逃げていないなら
	else
	{
		switch (m_state)
		{
		case eStand:
			// 画像の切り替え
			m_animCount = 0;

			break;
		case eMove:
			// 画像の切り替え
			if (m_animTime > 0.05f)
			{
				if (m_hoveringFlag)
				{
					m_animTime = 0.0f;
					m_animCount = m_animCount % 2;
				}
				else
				{
					m_animTime = 0.0f;
					m_animCount = m_animCount % 2;
				}
			}

			break;
		case ePanic:
			// 画像の切り替え
			if (m_animTime > 0.025f)
			{
				m_animTime = 0.0f;
				m_animCount = m_animCount % 2;
			}

			break;
		}
	}
}

void Dragonfly::Escape(float delta)
{
	Vector2D playerLocation = targetPlayer->GetPlayerLocation();

	// 向きをプレイヤーから虫への向きに
	m_direction = VecATan2(playerLocation, m_location);
	if (targetPlayer->GetPlayerLocation().x <= m_location.x)
	{
		m_isFlip = true;
	}
	else
	{
		m_isFlip = false;
	}
	// 向きを0.01fπごとに区切った-0.25fπ~0.25fπずらす
	//m_direction += Random::GetRand(-0.25f, 0.25f, 0.01f) * DX_PI_F;

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

	
	if (m_transitionTime <= 0.0f)
	{

		// 巡回状態へ
		m_state = eMove;
		// 目的地を設定
		SetDestination();

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
	float destinationDirection = VecATan2(m_location, m_destinations[m_destinationNum]);	// 目的地への向き
	GraduallyTurn(m_direction, destinationDirection, 2.0f * DX_PI_F * delta);

	// 加速
	Acceleration(acceleration, maxSpeed, m_direction, delta);
	// 減速
	Deceleration(deceleration, delta);

	// 目的地についたら
	if (Length(Vec2Sub(m_location, m_destinations[m_destinationNum])) < 10.0f)
	{
		if (m_destinationNum < 4)
		{
			m_destinationNum++;
		}
		else
		{
			// 待機状態へ
			m_moveSpeed = { 0.0f, 0.0f };
			m_state = eStand;

			// 遷移時間を0.1fごとに区切った10.0f~30.0fにする
			m_transitionTime = Random::GetRand(10.0f, 30.0f, 0.1f);
		}
	}
}

void Dragonfly::Panic(float delta)
{
	// 向きを0.125fπごとに区切った-2.0fπ~2.0fπずらす
	//m_direction += Random::GetRand(-2.0f, 2.0f, 0.125f) * DX_PI_F * delta;
	m_moveSpeed.x = Random::GetRand(1.0f);
	m_moveSpeed.y = Random::GetRand(1.0f);
	if (m_moveSpeed.x == 0)
	{
		m_moveSpeed.x = -1;
		
	}
	if (m_moveSpeed.y == 1)
	{
		m_moveSpeed.y = -1;
	
	}
	
	m_hoveringTimeFlag = true;
	m_hoveringFlag = false;
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
		// 目的地を設定
		SetDestination();
	}
}

void Dragonfly::Hovering(float delta)
{
	if (m_hoveringMove >= 3.0f && m_hoveringTimeFlag == false)
	{
		int a = (int)Random::GetRand(1.0f);
		if (a)
		{
			m_moveSpeed.x = 8.0f;
			m_isFlip = true;
		}
		else
		{
			m_moveSpeed.x = -8.0f;
			m_isFlip = false;
		}

		m_moveSpeed.y = Random::GetRand(1.0f);

		if (m_moveSpeed.y == 8.0f)
		{
			m_moveSpeed.y = -8.0f;

		}
		m_hoveringTimeFlag = true;
		m_hoveringFlag = false;
	}
	if (m_hoveringMove >= 5.0f)
	{
		m_hoveringFlag = true;
	}

	if (m_hoveringMove >= 6.5f)
	{
		m_hoveringMove = 0;
		m_hoveringTimeFlag = false;
	}

	if (m_hoveringFlag == true)
	{
		m_hovering = (int)Random::GetRand(2.0f);
		if (m_hovering == 2)
		{
			m_hovering = -1;
		}
		m_location.x += m_hovering;
		m_location.y += m_hovering;
	}

	if (m_hoveringFlag == false)
	{
		m_location.x += m_moveSpeed.x;
		m_location.y += m_moveSpeed.y;
	}
	m_state = eStand;
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
	//Vector2D GroundLocation = FindNearestGround(m_location);

	// その木から離れたら、前面に置く
	/*if (m_location.x + m_radius < GroundLocation.x - D_GROUND_WIDTH ||
		m_location.x - m_radius > GroundLocation.x + D_GROUND_WIDTH ||
		m_location.y + m_radius < GroundLocation.y - D_GROUND_HEIGHT ||
		m_location.y - m_radius > GroundLocation.y + D_GROUND_HEIGHT)
	{
		m_isBack = false;
	}*/
}


