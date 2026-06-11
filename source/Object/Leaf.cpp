#include<DxLib.h>
#include"Leaf.h"
#include"../Utilitys/Camera.h"
#include"../Scene/InGameScene.h"

static Player* targetPlayer;     //ƒvƒŒƒCƒ„[î•ñ

int Leaf::images[4] = {};

Leaf::Leaf()
{
	m_location = { 0.0f,0.0f };
	m_animTime = 0.0f;
	m_animCount = 0;
}


Leaf::~Leaf()
{
}

void Leaf::Init()
{
	images[0] = LoadGraph("assets/images/OtherObjects/Tree/Grass1.png");
	images[1] = LoadGraph("assets/images/OtherObjects/Tree/Grass2.png");
	images[2] = LoadGraph("assets/images/OtherObjects/Tree/Grass3.png");
	images[3] = LoadGraph("assets/images/OtherObjects/Tree/Grass4.png");
}

void Leaf::Set(Vector2D location)
{
	m_location = location;
	m_animTime = 0.0f;
	m_animCount = 0;
}

void Leaf::Update(float delta)
{
	m_animTime += delta;
	if (m_animTime > 0.5f)
	{
		m_animTime = 0.0f;
		m_animCount++;
		m_animCount %= 4;
	}

}

void Leaf::Draw(int id)const
{
	Camera::DrawGraphW(m_location, 3.0f * D_OBJECT_SIZE_RATIO, 3.0f * D_OBJECT_SIZE_RATIO, 0.0f, images[m_animCount]);
}

void Leaf::SetPlayer(Player* p)
{
	targetPlayer = p;
}

Vector2D Leaf::GetLocation() const
{
	return m_location;
}

