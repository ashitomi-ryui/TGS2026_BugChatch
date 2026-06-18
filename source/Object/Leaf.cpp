#include<DxLib.h>
#include"Leaf.h"
#include "ObjectManager.h"
#include"../Utilitys/Camera.h"

static Player* targetPlayer;     //プレイヤー情報

int Leaf::images[4] = {};

Leaf::Leaf()
{
	m_location = { 0.0f,0.0f };
	m_vector = {};
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
	m_vector = { 0.0f,0.0f };
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

void Leaf::Draw()const
{
	Camera::DrawGraphW(m_location, 2.0f, 2.0f, 0.0f, images[m_animCount]);
}

void Leaf::SetPlayer(Player* p)
{
	targetPlayer = p;
}

bool Leaf::DetermineTheExtrusionVector(int id)
{
	// 重なりをなくす
	float radius = Length(Vec2Sub({ 0.0f, 0.0f }, { D_LEAF_WIDTH / 2.0f, D_LEAF_HEIGHT / 2.0f }));
	float playerRadius = targetPlayer->GetPlayerRadius();
	m_vector = ObjectManager::TreeHitCheak(m_location, radius, true);
	m_vector = Vec2Add(m_vector, ObjectManager::LeafHitCheak(m_location, radius, true, id));
	m_vector = Vec2Mult(m_vector, 0.5f);

	if (m_vector.x != 0.0f ||
		m_vector.y != 0.0f)
		return true;

	return false;
}

void Leaf::EliminateOverlap()
{
	m_location = Vec2Add(m_location, m_vector);
	m_location = Vec2Add(m_location, m_vector);
}

Vector2D Leaf::GetLocation() const
{
	return m_location;
}

