#include<DxLib.h>
#include "Shadow.h"
#include"../Utilitys/Camera.h"

int Shadow::m_image = -1;

Shadow::Shadow()
{
	m_location = {};
	m_isDisplay = false;
}

Shadow::~Shadow()
{
}

void Shadow::Init()
{
	m_image = LoadGraph("assets/images/OtherObjects/Shadow.PNG");
}

void Shadow::Set(Vector2D location, float height, bool isDisplay)
{
	m_location = location;
	m_location.y += height;

	m_isDisplay = isDisplay;
}

void Shadow::Draw() const
{
	if (m_isDisplay)
	{
		Camera::DrawGraphW(m_location, 3.0f * D_OBJECT_SIZE_RATIO, 3.0f * D_OBJECT_SIZE_RATIO, 0.0f, m_image);
	}
}
