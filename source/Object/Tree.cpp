#include<DxLib.h>
#include"Tree.h"
#include"../Utilitys/Camera.h"
#include"../Scene/InGameScene.h"

Player* targetPlayer;     //プレイヤー情報

int Tree::images[4] = {};

Tree::Tree()
{
	m_location = { 0.0f,0.0f };
	m_animTime = 0.0f;
	m_animCount = 0;
}

Tree::~Tree()
{
}

void Tree::Init()
{
	images[0] = LoadGraph("assets/images/OtherObjects/Tree/Tree1.PNG");
	images[1] = LoadGraph("assets/images/OtherObjects/Tree/Tree2.PNG");
	images[2] = LoadGraph("assets/images/OtherObjects/Tree/Tree3.PNG");
	images[3] = LoadGraph("assets/images/OtherObjects/Tree/Tree4.PNG");
}

void Tree::Set(Vector2D location)
{
	m_location = location;
	m_animTime = 0.0f;
	m_animCount = 0;
}

void Tree::Update(float delta)
{
	m_animTime += delta;
	if (m_animTime > 0.2f)
	{
		m_animTime = 0.0f;
		m_animCount++;
		m_animCount %= 4;
	}

	Vector2D playerLocation = targetPlayer->GetPlayerLocation();

	// プレイヤーに最も近い点
	Vector2D closest;

	// X座標の最も近い点を求める
	if (playerLocation.x > m_location.x + D_TREE_WIDTH)
	{
		closest.x = m_location.x + D_TREE_WIDTH;
	}
	else if (playerLocation.x < m_location.x - D_TREE_WIDTH)
	{
		closest.x = m_location.x - D_TREE_WIDTH;
	}
	else
	{
		closest.x = playerLocation.x;
	}

	// Y座標の最も近い点を求める
	if (playerLocation.y > m_location.y + D_TREE_HEIGHT)
	{
		closest.y = m_location.y + D_TREE_HEIGHT;
	}
	else if (playerLocation.y < m_location.y - D_TREE_HEIGHT)
	{
		closest.y = m_location.y - D_TREE_HEIGHT;
	}
	else
	{
		closest.y = playerLocation.y;
	}

	float len = Length(Vec2Sub(closest, playerLocation));
	float playerRadius = targetPlayer->GetRingRadius();
	if (len < playerRadius)
	{
		Vector2D playerMove;

		float angle = VecATan2(closest, playerLocation);

		playerMove.x = sinf(angle) * (playerRadius - len);
		playerMove.y = -cosf(angle) * (playerRadius - len);

		targetPlayer->PlayerLocationMove(playerMove);
	}

}

void Tree::Draw(int id)const
{
	Camera::DrawGraphW(m_location, 3.0f * D_OBJECT_SIZE_RATIO, 0.0f, images[m_animCount]);
}

void Tree::SetPlayer(Player* p)
{
	targetPlayer = p;
}

Vector2D Tree::GetLocation() const
{
	return m_location;
}
