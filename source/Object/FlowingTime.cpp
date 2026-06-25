#include "FlowingTime.h"

#include "ObjectManager.h"
#include "../Utilitys/Camera.h"

FlowingTime::FlowingTime()
{
	m_isDisplay = false;
	m_x = D_WIN_WIDTH;
	m_time = 0;
	m_color = 0xffffff;
}

FlowingTime::~FlowingTime()
{
}

void FlowingTime::Init()
{
	m_isDisplay = false;
	m_x = D_WIN_WIDTH;
	m_time = 0;
	m_color = 0xffffff;
}

void FlowingTime::Flow(int time, unsigned int color)
{
	m_isDisplay = true;
	m_x = D_WIN_WIDTH;
	m_time = time;
	m_color = color;
}

void FlowingTime::Update(float delta)
{
	if(m_isDisplay)
	{
		m_x -= D_WIN_WIDTH * delta;
	}
}

void FlowingTime::Draw() const
{
	if(m_isDisplay)
	{
		int size = 100;
		Vector2D loc = { m_x, D_WIN_HEIGHT / 2.0f - 100.0f };
		loc.x -= (float)size / 2.0f;
		unsigned int color = m_color;

		if (ObjectManager::CheckUIOverlapping((int)size * 2.0f, (int)size * 2.0f, loc))
			color = m_color + 0x60000000;
		else
			color = m_color + 0xff000000;
		Camera::DrawString(loc, size, color, "‚Ì");
		loc.x += (float)size;

		if (ObjectManager::CheckUIOverlapping((int)size * 2.0f, (int)size * 2.0f, loc))
			color = m_color + 0x60000000;
		else
			color = m_color + 0xff000000;
		Camera::DrawString(loc, size, color, "‚±");
		loc.x += (float)size;

		if (ObjectManager::CheckUIOverlapping((int)size * 2.0f, (int)size * 2.0f, loc))
			color = m_color + 0x60000000;
		else
			color = m_color + 0xff000000;
		Camera::DrawString(loc, size, color, "‚è");
		loc.x += (float)size;

		int num[10] = {};
		int len = 0;
		for (int keta = 1;keta <= m_time;keta *= 10)
		{
			num[len] = m_time / keta;
			num[len] %= 10;
			len++;
		}

		for (int i = len - 1;i >= 0;i--)
		{
			loc.x -= (float)size * 0.2f;
			if (ObjectManager::CheckUIOverlapping((int)size * 2.0f, (int)size * 2.0f, loc))
				color = m_color + 0x60000000;
			else
				color = m_color + 0xff000000;
			Camera::DrawString(loc, size, color, "%d", num[i]);
			loc.x += (float)size * 0.8f;
		}

		if (ObjectManager::CheckUIOverlapping((int)size * 2.0f, (int)size * 2.0f, loc))
			color = m_color + 0x60000000;
		else
			color = m_color + 0xff000000;
		Camera::DrawString(loc, size, color, "•b");
		loc.x += (float)size;
	}
}
