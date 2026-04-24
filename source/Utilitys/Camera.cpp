#include "DxLib.h"
#include "Camera.h"
#include <cmath>

Vector2D Camera::m_location = { 0.0f, 0.0f };

// コンストラクタ
Camera::Camera(Vector2D location)
{
	m_location = location;
}

// デストラクタ
Camera::~Camera()
{
}

// 更新処理
void Camera::Update(Vector2D playerLocation)
{
	m_location = playerLocation;
	if (playerLocation.x < D_WIN_WIDTH / 2)
	{
		m_location.x = D_WIN_WIDTH / 2;
	}
	if (playerLocation.x > D_STAGE_WIDTH - D_WIN_WIDTH / 2)
	{
		m_location.x = D_STAGE_WIDTH - D_WIN_WIDTH / 2;
	}
	if (playerLocation.y < D_WIN_HEIGHT / 2)
	{
		m_location.y = D_WIN_HEIGHT / 2;
	}
	if (playerLocation.y > D_STAGE_HEIGHT - D_WIN_HEIGHT / 2)
	{
		m_location.y = D_STAGE_HEIGHT - D_WIN_HEIGHT / 2;
	}

}

void Camera::Draw() const
{

}

void Camera::DrawLineW(Vector2D location1, Vector2D location2, unsigned int Color, int Thinckness)
{
	location1.x += -m_location.x + D_WIN_WIDTH / 2;
	location1.y += -m_location.y + D_WIN_HEIGHT / 2;
	location2.x += -m_location.x + D_WIN_WIDTH / 2;
	location2.y += -m_location.y + D_WIN_HEIGHT / 2;

	DrawLine(location1.x, location1.y, location2.x, location2.y, Color, Thinckness);
}

void Camera::DrawTriangleW(Vector2D location1, Vector2D location2, Vector2D location3, unsigned int Color)
{
	location1.x += -m_location.x + D_WIN_WIDTH / 2;
	location1.y += -m_location.y + D_WIN_HEIGHT / 2;
	location2.x += -m_location.x + D_WIN_WIDTH / 2;
	location2.y += -m_location.y + D_WIN_HEIGHT / 2;
	location3.x += -m_location.x + D_WIN_WIDTH / 2;
	location3.y += -m_location.y + D_WIN_HEIGHT / 2;

	DrawTriangle(location1.x, location1.y, location2.x, location2.y, location3.x, location3.y, Color, true);
}

void Camera::DrawCircleW(Vector2D location, int radius, unsigned int Color)
{
	location.x += -m_location.x + D_WIN_WIDTH / 2;
	location.y += -m_location.y + D_WIN_HEIGHT / 2;

	DrawCircle(location.x, location.y, radius, Color, true);
}

void Camera::DrawBoxW(Vector2D location1, Vector2D location2, unsigned int Color)
{
	location1.x += -m_location.x + D_WIN_WIDTH / 2;
	location1.y += -m_location.y + D_WIN_HEIGHT / 2;
	location2.x += -m_location.x + D_WIN_WIDTH / 2;
	location2.y += -m_location.y + D_WIN_HEIGHT / 2;

	DrawBox(location1.x, location1.y, location2.x, location2.y, Color, true);
}

void Camera::DrawGraphW(Vector2D location, double ExRate, double Angle, int GrHandle, int ReverseXFlag, int ReverseYFlage)
{
	location.x += -m_location.x + D_WIN_WIDTH / 2;
	location.y += -m_location.y + D_WIN_HEIGHT / 2;

	DrawRotaGraphF(location.x, location.y, ExRate, Angle, true, ReverseXFlag, ReverseYFlage);
}
