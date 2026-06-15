#include<DxLib.h>
#include "Effect.h"
#include"../Utilitys/Camera.h"
#include"../Scene/InGameScene.h"

int Effect::m_images[4] = {};

Effect::Effect()
{
	m_location = {};
	m_color = 0xffff00;

	m_animTime = 0.0f;
	m_animCount = 0;

	m_isDisplay = false;
}

Effect::~Effect()
{
}

void Effect::Init()
{
	m_images[0] = LoadGraph("assets/images/OtherObjects/Effect/Effect1.png");
	m_images[1] = LoadGraph("assets/images/OtherObjects/Effect/Effect2.png");
	m_images[2] = LoadGraph("assets/images/OtherObjects/Effect/Effect3.png");
	m_images[3] = LoadGraph("assets/images/OtherObjects/Effect/Effect4.png");
}

void Effect::Set(Vector2D location, unsigned int color)
{
	m_location = location;
	m_color = color;

	m_animTime = 0.0f;
	m_animCount = 0;

	m_isDisplay = true;
}

void Effect::Update(float delta)
{
	if(m_isDisplay)
	{
		m_animTime += delta;
		if (m_animTime >= 0.02f)
		{
			m_animCount++;
			m_animTime = 0.0f;

			if (m_animCount == 4)
			{
				m_animCount = 0;
				m_isDisplay = false;
			}
		}
	}
}

void Effect::Draw() const
{
	if(m_isDisplay)
	{
		Camera::DrawGraphW(m_location, 3.0f * D_OBJECT_SIZE_RATIO, 3.0f * D_OBJECT_SIZE_RATIO, 0.0f, m_images[m_animCount]);
	}
}

void Effect::SetHidden()
{
	m_isDisplay = false;
}

bool Effect::GetIsDisplay()const
{
	return m_isDisplay;
}
