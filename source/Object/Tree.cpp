#include<DxLib.h>
#include"Tree.h"
#include "ObjectManager.h"
#include"../Utilitys/Camera.h"

Player* targetPlayer;     //プレイヤー情報

int Tree::images[4] = {};

Tree::Tree()
{
	m_location = { 0.0f,0.0f };
	m_vector = {};
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
	m_vector = { 0.0f,0.0f };
	m_animTime = 0.0f;
	m_animCount = 0;
}

void Tree::Update(float delta)
{
	m_animTime += delta;
	if (m_animTime > 0.5f)
	{
		m_animTime = 0.0f;
		m_animCount++;
		m_animCount %= 4;
	}
}

void Tree::Draw(int id)const
{
	Camera::DrawGraphW(m_location, 2.0f, 2.0f, 0.0f, images[m_animCount]);
}

void Tree::SetPlayer(Player* p)
{
	targetPlayer = p;
}

bool Tree::DetermineTheExtrusionVector(int id)
{
	// 重なりをなくす
	float radius = Length(Vec2Sub({ 0.0f, 0.0f }, { D_TREE_WIDTH / 2.0f, D_TREE_HEIGHT / 2.0f }));
	float playerRadius = targetPlayer->GetRadius();
	m_vector = ObjectManager::TreeHitCheck(m_location, radius + playerRadius * 3.0f, true, id);
	m_vector = Vec2Add(m_vector, ObjectManager::LeafHitCheck(m_location, radius, true));
	m_vector = Vec2Mult(m_vector, 0.5f);

	if (m_vector.x != 0.0f ||
		m_vector.y != 0.0f)
		return true;

	return false;
}

void Tree::EliminateOverlap()
{
	m_location = Vec2Add(m_location, m_vector);
	m_location = Vec2Add(m_location, m_vector);
}

Vector2D Tree::GetLocation() const
{
	return m_location;
}
