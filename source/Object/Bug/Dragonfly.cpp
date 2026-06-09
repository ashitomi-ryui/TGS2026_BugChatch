#include "DxLib.h"
#include "Math.h"


#include "../../Utilitys/Math.h"
#include "../../Utilitys/Random.h"
#include "../../Utilitys/Camera.h"

#include "../../Scene/InGameScene.h"

#include "Dragonfly.h"

#include"../Tree.h"
#include"../Leaf.h"

int Dragonfly::images[4] = { -1,-1,-1,-1 };

Dragonfly::Dragonfly() : Bug()
{
	// 察知範囲
	m_detectionRange = 300.0f * D_OBJECT_SIZE_RATIO;

	m_destinationSub = 0;	// 目的地の添え字
	m_destinationNum = 0;	// 目的地の数

	m_isHovering = false;	// ホバリングしているかどうか
	m_hoveringCount = 0;	// ホバリング回数
	m_isFlapping = false;	// 羽ばたき

	m_isBreak = false;	// 休憩

	m_isFlip = false;	// 反転
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
	Animation(delta);

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
			switch (m_state)
			{
			case eStand:
				Stand(delta);

				break;
			case eMove:
				if (m_isHovering)
				{
					Hovering(delta);
				}
				else if (m_isBreak)
				{
					HeadingForABreak(delta);
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

#ifdef _DEBUG
	//if (m_isEscape)
	//{
	//	Camera::DrawFormatStringW(m_location, 10, 0xffffff, "Escape");
	//}
	//else
	//{
	//	switch (m_state)
	//	{
	//	case eStand:
	//		Camera::DrawFormatStringW(m_location, 10, 0xffffff, "Stand");
	//		break;
	//	case eMove:
	//		if (m_isHovering)
	//		{
	//			Camera::DrawFormatStringW(m_location, 10, 0xffffff, "Hovering");
	//		}
	//		else if (m_isBack)
	//		{
	//			Camera::DrawFormatStringW(m_location, 10, 0xffffff, "Back");
	//		}
	//		else
	//		{
	//			Camera::DrawFormatStringW(m_location, 10, 0xffffff, "Move");
	//		}
	//		break;
	//	case ePanic:
	//		Camera::DrawFormatStringW(m_location, 10, 0xffffff, "Panic");
	//		break;
	//	}
	//}
#endif
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
	m_destinationSub = 0;	// 目的地の添え字
	m_destinationNum = 0;	// 目的地の数

	m_isHovering = false;	// ホバリングしているかどうか
	m_hoveringCount = 0;	// ホバリング回数
	m_isFlapping = false;	// 羽ばたき

	m_isBreak = false;	// 休憩

	m_isFlip = false;	// 反転

	// 位置をランダムな草に設定
	Vector2D location = FindNearestLeaf(RandomLocationOnTheScreen());

	// スポーン位置
	// ランダムに座標をずらす
	location.x += Random::GetRand((D_LEAF_WIDTH / 2.0f), -(D_LEAF_WIDTH / 4.0f));
	location.y += Random::GetRand((D_LEAF_HEIGHT / 4.0f), -(D_LEAF_HEIGHT / 4.0f));
	
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
	// 目的地の数を1~5のランダムにする
	m_destinationNum = (int)Random::GetRand(1.0f, 5.0f);

	Vector2D temp[5] = {};	// 仮の目的地
	bool m_isAlreadySet[5] = {};	// 設定済みかどうか

	// 仮の目的地に5つのランダムな点を設定する
	for (int i = 0;i < m_destinationNum;i++)
	{
		temp[i] = RandomLocationOnTheScreen();
		m_isAlreadySet[i] = false;
	}

	Vector2D reference = m_location;	// 基準点
	int minNum;		// 基準点に最も近い点の添え字
	float minLen;	// 基準点から最も近い点までの距離

	// 仮の目的地のあてはめ
	// i = 目的地の添え字
	for (int i = 0;i < m_destinationNum;i++)
	{
		// 最も近い点の初期化
		minNum = -1;
		minLen = -1.0f;

		// j = 参照する仮の目的地の添え字
		for (int j = 0;j < m_destinationNum;j++)
		{
			// 並び替えがまだなら
			if(m_isAlreadySet[j] == false)
			{
				// 最も近い点が未設定、または基準点までの距離が最も近い距離より小さいなら
				if (minNum == -1 || minLen > Length(Vec2Sub(reference, temp[j])))
				{
					minNum = j;
				}
			}
		}
		// 目的地をその点にする
		m_destinations[i] = temp[minNum];
		m_isAlreadySet[minNum] = true;
		// その点を基準点にする
		reference = temp[minNum];
	}
	m_destinationSub = 0;
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
			m_animCount = (m_animCount + 1) % 2;
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
				if (m_isHovering && m_isFlapping)
				{
					m_animTime = 0.0f;
					m_animCount = (m_animCount + 1) % 4;
				}
				else
				{
					m_animTime = 0.0f;
					m_animCount = (m_animCount + 1) % 2;
				}
			}

			break;
		case ePanic:
			// 画像の切り替え
			if (m_animTime > 0.025f)
			{
				m_animTime = 0.0f;
				m_animCount = (m_animCount + 1) % 2;
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
		// ホバリングしない
		m_isHovering = false;

		// 移動状態へ
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

	// 目的地に向ける
	m_direction = VecATan2(m_location, m_destinations[m_destinationSub]);

	// 加速
	Acceleration(acceleration, maxSpeed, m_direction, delta);
	// 減速
	Deceleration(deceleration, delta);

	if (m_moveSpeed.x > 0.0f)
	{
		m_isFlip = true;
	}
	else
	{
		m_isFlip = false;
	}

	// 目的地についたら
	if (Length(Vec2Sub(m_location, m_destinations[m_destinationSub])) < 10.0f * D_OBJECT_SIZE_RATIO)
	{
		// 全ての目的地を通っていないなら
		if (m_destinationSub < m_destinationNum - 1)
		{
			m_destinationSub++;
		}
		// 全ての目的地を通ったなら
		else
		{
			// ホバリング
			m_moveSpeed = { 0.0f, 0.0f };
			m_isHovering = true;
			// 大きく羽ばたかない
			m_isFlapping = false;

			// 目的地の設定
			float distance = Random::GetRand(1.0f, 5.0f);
			m_direction = Random::GetRand(0.0f, 2.0f, 0.125f);
			m_destination.x = m_location.x + sinf(m_direction) * distance;
			m_destination.y = m_location.y - cosf(m_direction) * distance;

			// ホバリング回数を2回ずつに区切った2~10回にする
			m_hoveringCount = (int)Random::GetRand(2.0f, 10.0f, 2.0f);
		}
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
		// ホバリングしない
		m_isHovering = false;
		// 休憩しない
		m_isBreak = false;

		// 移動状態へ
		m_state = eMove;
		// 目的地を設定
		SetDestination();
	}

}

void Dragonfly::Hovering(float delta)
{
	// ホバリング終了
	if (m_hoveringCount == -1)
	{
		// ホバリングしない
		m_isHovering = false;

		int r = (int)Random::GetRand(1.0f);
		if (r == 0)
		{
			// 休憩へ向かう
			m_isBreak = true;

			// ランダムな草を目的地に設定
			m_destination = FindNearestLeaf(RandomLocationOnTheScreen());

			// 目的地をランダムに座標をずらす
			m_destination.x += Random::GetRand((D_LEAF_WIDTH / 2.0f), - (D_LEAF_WIDTH / 4.0f));
			m_destination.y += Random::GetRand((D_LEAF_HEIGHT / 4.0f), - (D_LEAF_HEIGHT / 4.0f));
		}
		else
		{
			// 目的地を5つ設定
			SetDestination();
		}
		
		m_moveSpeed = { 0.0f, 0.0f };

		return;
	}

	// 加速度
	float acceleration = 0.0f;
	// 最大速度
	float maxSpeed = 0.0f;
	// 減速度
	float deceleration = 0.0f;

	// 目的地に向ける
	m_direction = VecATan2(m_location, m_destination);

	// 大きく羽ばたいているとき
	if (m_isFlapping)
	{
		shiita += m_moveSpeed.x * delta;

		if (shiita > 1.0f)
		{
			shiita = 1.0f; // 行き過ぎ防止
		}

		// 大きく羽ばたくときの移動処理
		m_location.x = m_startLocation.x + (m_destination.x - m_startLocation.x) * shiita;
		m_location.y = m_startLocation.y + (m_destination.y - m_startLocation.y) * shiita;

		// 高さを下げる
		m_location.y += sinf(shiita * DX_PI_F) * bottom;

		// 到着判定
		if (shiita >= 1.0f)
		{
			// 大きく羽ばたかない
			m_isFlapping = false;

			m_moveSpeed = { 0.0f, 0.0f };

			// 次の目的地の設定
			float distance = Random::GetRand(1.0f, 5.0f);
			m_direction = Random::GetRand(0.0f, 2.0f, 0.125f);
			m_destination.x = m_location.x + sinf(m_direction) * distance;
			m_destination.y = m_location.y - cosf(m_direction) * distance;

			// ホバリング回数を減らす
			m_hoveringCount--;
		}
	}
	// 大きく羽ばたいていないとき
	else
	{
		// 加速度
		acceleration = 50.0f;
		// 最大速度
		maxSpeed = 20.0f;
		// 減速度
		deceleration = 10.0f;

		// 加速
		Acceleration(acceleration, maxSpeed, m_direction, delta);
		// 減速
		Deceleration(deceleration, delta);

		// 到着判定
		if (Length(Vec2Sub(m_location, m_destination)) < 0.1f * D_OBJECT_SIZE_RATIO)
		{
			// 大きく羽ばたく
			m_isFlapping = true;

			// 座標を完全に目的地に合わせる
			m_location = m_destination;

			// 目的地、ホバリング時の底辺の設定
			shiita = 0;
			//向き
			m_direction = Random::GetRand(0.0f, 2.0f, 0.1f) * DX_PI_F;
			//移動距離
			float distance = Random::GetRand(5.0f, 10.0f, 0.1f);

			// 目的地
			m_destination.x = m_location.x + cosf(m_direction) * distance;
			m_destination.y = m_location.y + sinf(m_direction) * distance;

			m_startLocation = m_location;

			// 速さ
			m_moveSpeed.x = Random::GetRand(2.0f, 5.0f, 0.1f);

			bottom = Random::GetRand(5.0, 10.0, 0.1f);

			// ホバリング回数を減らす
			m_hoveringCount--;
		}
	}
}

void Dragonfly::HeadingForABreak(float delta)
{
	// 反転
	if (m_moveSpeed.x > 0.0f)
	{
		m_isFlip = true;
	}
	else
	{
		m_isFlip = false;
	}

	// 加速度
	float acceleration = 1000.0f;
	// 最大速度
	float maxSpeed = 400.0f;
	// 減速度
	float deceleration = 200.0f;

	// 目的地に向ける
	m_direction = VecATan2(m_location, m_destination);

	// 加速
	Acceleration(acceleration, maxSpeed, m_direction, delta);
	// 減速
	Deceleration(deceleration, delta);

	Vector2D leafLocation = FindNearestLeaf(m_location);
	// 目的地についたかつ、草の範囲なら
	if (Length(Vec2Sub(m_location, m_destination)) < 1.0f * D_OBJECT_SIZE_RATIO)
	{
		// 目的地についたら待機状態へ
		m_moveSpeed = { 0.0f, 0.0f };
		m_state = eStand;
		m_isBreak = false;

		// 遷移時間を0.1fごとに区切った10.0f~30.0fにする
		m_transitionTime = Random::GetRand(10.0f, 30.0f, 0.1f);
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

