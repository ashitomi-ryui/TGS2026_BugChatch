#include<DxLib.h>
#include"Ground.h"
#include"../Utilitys/Camera.h"
#include"../Scene/InGameScene.h"


static Player* targetPlayer;     //ÉvÉåÉCÉÑÅ[èÓïÒ


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

