#include<DxLib.h>
#include"Ground.h"
#include"../Utilitys/Camera.h"
#include"../Scene/InGameScene.h"


static Player* targetPlayer;     //プレイヤー情報


Ground::Ground()
{
	m_location = { 0.0f,0.0f };
}

Ground::~Ground()
{
}

void Ground::Init()
{
}

void Ground::Set(Vector2D location)
{
	m_location = location;
}

void Ground::Update(float delta)
{
	Vector2D playerLocation = { 0,0 }; /*= targetPlayer->GetPlayerLocation();*/

// プレイヤーに最も近い点
Vector2D closest;


// X座標の最も近い点を求める
if (playerLocation.x > m_location.x + D_GROUND_WIDTH)
{
	closest.x = m_location.x + D_GROUND_WIDTH;
}
else if (playerLocation.x < m_location.x - D_GROUND_WIDTH)
{
	closest.x = m_location.x - D_GROUND_WIDTH;
}
else
{
	closest.x = playerLocation.x;
}

// Y座標の最も近い点を求める
if (playerLocation.y > m_location.y + D_GROUND_HEIGHT)
{
	closest.y = m_location.y + D_GROUND_HEIGHT;
}
else if (playerLocation.y < m_location.y - D_GROUND_HEIGHT)
{
	closest.y = m_location.y - D_GROUND_HEIGHT;
}
else
{
	closest.y = playerLocation.y;
}

}



void Ground::Draw(int id)const
{
}


void Ground::SetPlayer(Player* p)
{
	targetPlayer = p;
}

Vector2D Ground::GetLocation() const
{
	return m_location;
}

