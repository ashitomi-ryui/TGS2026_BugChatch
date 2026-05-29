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

int Grasshopper::images[4] = { -1,-1,-1,-1};

Grasshopper::Grasshopper() : Bug()
{
	// 察知範囲
	m_detectionRange = 300.0f * D_OBJECT_SIZE_RATIO;
	jougai = FALSE;
}
Grasshopper::~Grasshopper()
{

}

void Grasshopper::Init()
{
	images[0] = LoadGraph("assets/images/Bugs/Grasshopper/Grasshopper1.PNG");
	images[1] = LoadGraph("assets/images/Bugs/Grasshopper/Jump1.PNG");
	images[2] = LoadGraph("assets/images/Bugs/Grasshopper/Jump2.PNG");
	images[3] = LoadGraph("assets/images/Bugs/Grasshopper/Jump3.PNG");

	grasshopperGetCount = 0;
}

void Grasshopper::Update(float delta)
{
	Animation(delta);

	// 出現しているなら
	if (m_isAppearance)
	{
		CheckOverlap();

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
			/*case ePanic:
				Panic(delta);

				break;*/
			}

			PerceptionJudgment();
		}

		Bug::Update(delta);

		// 当たり判定
		if (HitCheck())
		{
			grasshopperGetCount += 1;
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

	if (m_location.x<0 || m_location.x>D_STAGE_WIDTH ||
		m_location.y<0 || m_location.y>D_STAGE_HEIGHT)
	{
		jougai = TRUE;
	}
}

void Grasshopper::Draw() const
{
	bool isTurn = FALSE;

	if (m_Angle > 3.0f)
	{
		isTurn = TRUE;
	}

	DrawFormatString(50, 50, GetColor(255, 0, 0), "%d", m_state);
	//
	DrawFormatString(50, 100, GetColor(255, 0, 0), "%d", m_isBack);
	//DrawFormatString(50, 150, GetColor(255, 0, 0), "%f", m_location.y);
	DrawFormatString(50, 200, GetColor(255, 0, 0), "%f", shiita);
	//DrawFormatString(50, 250, GetColor(255, 0, 0), "%f", m_moveSpeed.x);
	//DrawFormatString(50, 300, GetColor(255, 0, 0), "%f", m_destination.x);
	Camera::DrawGraphW(m_location, 3.0f * D_OBJECT_SIZE_RATIO, 0.0, images[m_animCount], isTurn);
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

	// 位置を近くの草に設定する
	location = FindNearestLeaf(location);
	// 位置を少しずらす
	location.x += Random::GetRand((D_LEAF_WIDTH / 2), -(D_LEAF_WIDTH / 2));
	location.y += Random::GetRand((D_LEAF_HEIGHT / 2), -(D_LEAF_HEIGHT / 2));

	shiita = 0.0f;
	escape = FALSE;
	m_moveSpeed = { 0.0f, 0.0f };
	m_transitionTime = 0.0f;

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
	shiita = 0;

	if (jougai == TRUE)
	{
		// 近くの木を目的地にする
		nearleaf = FindNearestLeaf(location);

		m_direction = atan2f((nearleaf.y - m_location.y), (nearleaf.x - m_location.x));

		//移動距離
		float distance = Random::GetRand(50.0f, 300.0f, 10.0f);

		// 目的地
		m_destination.x = location.x + cosf(m_direction) * distance;
		m_destination.y = location.y + sinf(m_direction) * distance;

		m_startLocation = location;

		// 速さ
		m_moveSpeed.x = Random::GetRand(1.0f, 1.5f, 0.1f);

		top = Random::GetRand(20.0, 50.0, 0.1f);

		
	}
	else
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
		m_moveSpeed.x = Random::GetRand(1.0f, 1.5f, 0.1f);

		top = Random::GetRand(20.0, 50.0, 0.1f);
	}
	

}

void Grasshopper::EscapeSetDestination(Vector2D location,Vector2D Plocation)
{
	shiita = 0;

	m_direction = atan2f((location.y - Plocation.y), (location.x - Plocation.x));

	//移動距離
	float distance = Random::GetRand(150.0f, 400.0f, 0.1f);

	// 目的地
	m_destination.x = location.x + cosf(m_direction) * distance;
	
	m_destination.y = location.y + sinf(m_direction) * distance;

	m_startLocation = location;

	// 速さ
	m_moveSpeed.x = Random::GetRand(1.0f, 1.5f, 0.1f);

	top = Random::GetRand(20.0, 50.0, 0.1f);

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
		
		if (m_isEscape || m_state == eMove)
		{
			if (m_destination.x > m_startLocation.x)
			{
				m_Angle = DX_PI_F; // 右を向く
			}
			else
			{
				m_Angle = 0.0f;    // 左を向く
			}
		}

		
		if (m_isEscape || m_state == eMove)
		{
			if (shiita < 0.25f)
			{
				m_animCount = 1; // 飛び始め
			}
			else if (shiita < 0.75f)
			{
				m_animCount = 2; // 頂点通過
			}
			else
			{
				m_animCount = 3; // 着地前
			}
		}
		
		else if (m_state == eStand)
		{
			m_animCount = 0; // 通常時（地面にいる画像）に戻す！
		}
	}
}

void Grasshopper::Escape(float delta)
{

	Vector2D playerLocation = targetPlayer->GetPlayerLocation();
	if (escape == FALSE)
	{
		EscapeSetDestination(m_location,playerLocation);   
		escape = TRUE;
	}

	//// 向きをプレイヤーから虫への向きに
	//m_direction = VecATan2(playerLocation, m_location);
	// 向きを0.01fπごとに区切った-0.25fπ~0.25fπずらす
	/*m_direction += Random::GetRand(-0.25f, 0.25f, 0.1f) * DX_PI_F;*/

	shiita += m_moveSpeed.x * delta;

	if (shiita > 1.0f)
	{
		shiita = 1.0f; // 行き過ぎ防止
	}


	//ジャンプの移動処理
	m_location.x = m_startLocation.x + (m_destination.x - m_startLocation.x) * shiita;
	m_location.y = m_startLocation.y + (m_destination.y - m_startLocation.y) * shiita;



	//AIニキ
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
		shiita = 0;
		escape = FALSE;

		m_isEscape = false;
		m_state = eStand;
		m_transitionTime = Random::GetRand(1.0f, 2.0f, 0.1f);
		return;
	}
	
	// 察知時間を0.1fごとに区切った0.0f~1.0fにする
	m_detectionTime = Random::GetRand(0.0f, 1.0f, 0.1f);
}

void Grasshopper::Stand(float delta)
{
	shiita = 0;
	m_moveSpeed = { 0.0f, 0.0f };

	if (m_transitionTime <= 0.0f)
	{
		// 巡回状態へ
		m_state = eMove;
		// 向きを0.25πごとに区切ったランダムな向きに
		/*m_direction = Random::GetRand(0.0f, 2.0f, 0.25f) * DX_PI_F;*/
		// ランダムな木を目的地に設定
		SetDestination(m_location);
	}
}

void Grasshopper::Move(float delta)
{

	shiita += m_moveSpeed.x * delta;

	if (shiita > 1.0f)
	{
		shiita = 1.0f; // 行き過ぎ防止
	}


	//ジャンプの移動処理
	m_location.x = m_startLocation.x + (m_destination.x - m_startLocation.x) * shiita;
	m_location.y = m_startLocation.y + (m_destination.y - m_startLocation.y) * shiita;

	//AIニキ
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
		shiita = 0;
		m_state = eStand;
		m_transitionTime = Random::GetRand(1.0f, 2.0f, 0.1f);
		if (jougai == TRUE)
		{

			if (Length(Vec2Sub(m_location, m_destination)) < 10.0f &&
				m_location.x > nearleaf.x - D_LEAF_WIDTH &&
				m_location.x < nearleaf.x + D_LEAF_WIDTH &&
				m_location.y > nearleaf.y - D_LEAF_HEIGHT &&
				m_location.y < nearleaf.y + D_LEAF_HEIGHT)
			{
				jougai = FALSE;
			}
		}
		
	}

	
	/*Vector2D treeLocation = FindNearestTree(m_location);*/
	if (Length(Vec2Sub(m_location, m_destination)) < 10.0f)
	{
		// 目的地についたら待機状態へ
		m_moveSpeed = { 0.0f, 0.0f };
		m_state = eStand;

		// 遷移時間を0.1fごとに区切った10.0f~30.0fにする
		m_transitionTime = Random::GetRand(1.0f, 5.0f, 0.1f);
	}
}

//void Grasshopper::Panic(float delta)
//{
//	Vector2D playerLocation = targetPlayer->GetPlayerLocation();
//	if (escape == FALSE)
//	{
//		EscapeSetDestination(m_location, playerLocation);
//		escape = TRUE;
//	}
//
//
//	shiita += m_moveSpeed.x * delta;
//
//
//	if (shiita >= 1.0f)
//	{
//		shiita = 1.0f;
//		m_location = m_destination;
//		escape = FALSE;// 行き過ぎ防止
//		// 遷移時間が0以下なら
//		if (m_transitionTime <= 0.0f)
//		{
//			// 巡回状態へ
//			m_state = eMove;
//			
//			SetDestination(m_location);
//		}
//	}
//
//	/*Vector2D treeLocation = FindNearestTree(m_location);
//	if (m_location.x + m_radius > treeLocation.x - D_LEAF_WIDTH ||
//		m_location.x - m_radius < treeLocation.x + D_LEAF_WIDTH ||
//		m_location.y + m_radius > treeLocation.y - D_LEAF_HEIGHT/2 ||
//		m_location.y - m_radius < treeLocation.y + D_LEAF_HEIGHT/2)
//	{
//		m_isBack = TRUE;
//	}*/
//
//
//	//ジャンプの移動処理
//	m_location.x = m_startLocation.x + (m_destination.x - m_startLocation.x) * shiita;
//	m_location.y = m_startLocation.y + (m_destination.y - m_startLocation.y) * shiita;
//
//	//AIニキ
//	// 2. Y軸にサインカーブ（放物線）の高さを上乗せする
//	// sinf(shiita * DX_PI_F) は shiitaが 0.0(始点) -> 0.5(頂点) -> 1.0(終点) で 0 -> 1 -> 0 と変化します
//	// ※ 2Dゲームで上がマイナス方向なら引く、プラス方向なら足す
//	float height = sinf(shiita * DX_PI_F) * top;
//	m_location.y -= height;
//}


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

//void Grasshopper::PutInFront()
//{
//	
//}

void Grasshopper::CheckOverlap()
{
	Vector2D treeLocation = FindNearestTree(m_location);

	if (m_location.x > treeLocation.x - D_TREE_WIDTH / 2.0f &&  
		m_location.x < treeLocation.x + D_TREE_WIDTH / 2.0f && 
		m_location.y > treeLocation.y - D_TREE_HEIGHT / 2.0f && 
		m_location.y < treeLocation.y)                           
	{
		m_isBack = TRUE;  
	}
	else
	{
		m_isBack = FALSE; 
	}
}