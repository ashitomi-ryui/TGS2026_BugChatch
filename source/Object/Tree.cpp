#include<DxLib.h>
#include"Tree.h"
#include"../Utilitys/Camera.h"
#include"../Scene/InGameScene.h"

Player* targetPlayer;     //プレイヤー情報

int Tree::image = -1;

Tree::Tree()
{
	m_location = { 0.0f,0.0f };
}

Tree::~Tree()
{
}

void Tree::Init()
{
	image = LoadGraph("assets/images/tree.PNG");
}

void Tree::Set(Vector2D location)
{
	m_location = location;
}

void Tree::Update()
{
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
	if (len < 25.0f)
	{
		Vector2D playerMove;

		float angle = FindTheAngle(closest, playerLocation);

		playerMove.x = cosf(angle) * (25.0f - len);
		playerMove.y = -sinf(angle) * (25.0f - len);

		targetPlayer->PlayerLocationMove(playerMove);
	}

}

void Tree::Draw(int id)const
{
	Camera::DrawGraphW(m_location, 0.25f, 0.0f, image);
}

void Tree::SetPlayer(Player* p)
{
	targetPlayer = p;
}

Vector2D Tree::GetLocation() const
{
	return m_location;
}
