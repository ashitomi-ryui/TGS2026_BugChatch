#include "DxLib.h"
#include "Camera.h"
#include <cmath>
#include <string.h>

Vector2D Camera::m_location = { 0.0f, 0.0f };

Vector2D Camera::m_screenLocation = { D_WIN_WIDTH / 2.0f, D_WIN_HEIGHT / 2.0f };
float Camera::m_screenRatioSize = 1.0f;

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

void Camera::DrawLine(Vector2D location1, Vector2D location2, unsigned int Color, float Thinckness)
{
	location1 = FitLocationToScreen(location1);
	location2 = FitLocationToScreen(location2);
	Thinckness *= m_screenRatioSize;

	DxLib::DrawLine((int)location1.x, (int)location1.y, (int)location2.x, (int)location2.y, Color, (int)Thinckness);
}

void Camera::DrawLineW(Vector2D location1, Vector2D location2, unsigned int Color, float Thinckness)
{
	location1.x += -m_location.x + D_WIN_WIDTH / 2.0f;
	location1.y += -m_location.y + D_WIN_HEIGHT / 2.0f;
	location2.x += -m_location.x + D_WIN_WIDTH / 2.0f;
	location2.y += -m_location.y + D_WIN_HEIGHT / 2.0f;

	DrawLine(location1, location2, Color, Thinckness);
}

void Camera::DrawTriangle(Vector2D location1, Vector2D location2, Vector2D location3, unsigned int Color)
{
	location1 = FitLocationToScreen(location1);
	location2 = FitLocationToScreen(location2);
	location3 = FitLocationToScreen(location3);

	DxLib::DrawTriangle((int)location1.x, (int)location1.y, (int)location2.x, (int)location2.y, (int)location3.x, (int)location3.y, Color, true);
}

void Camera::DrawTriangleW(Vector2D location1, Vector2D location2, Vector2D location3, unsigned int Color)
{
	location1.x += -m_location.x + D_WIN_WIDTH / 2.0f;
	location1.y += -m_location.y + D_WIN_HEIGHT / 2.0f;
	location2.x += -m_location.x + D_WIN_WIDTH / 2.0f;
	location2.y += -m_location.y + D_WIN_HEIGHT / 2.0f;
	location3.x += -m_location.x + D_WIN_WIDTH / 2.0f;
	location3.y += -m_location.y + D_WIN_HEIGHT / 2.0f;

	DrawTriangle(location1, location2, location3, Color);
}

void Camera::DrawCircle(Vector2D location, float radius, unsigned int Color, bool FillFlag)
{
	location = FitLocationToScreen(location);
	radius *= m_screenRatioSize;

	DxLib::DrawCircle((int)location.x, (int)location.y, (int)radius, Color, FillFlag);
}

void Camera::DrawCircleW(Vector2D location, float radius, unsigned int Color, bool FillFlag)
{
	location.x += -m_location.x + D_WIN_WIDTH / 2.0f;
	location.y += -m_location.y + D_WIN_HEIGHT / 2.0f;

	DrawCircle(location, radius, Color, FillFlag);
}

void Camera::DrawBox(Vector2D location1, Vector2D location2, unsigned int Color)
{
	location1 = FitLocationToScreen(location1);
	location2 = FitLocationToScreen(location2);

	DxLib::DrawBox((int)location1.x, (int)location1.y, (int)location2.x, (int)location2.y, Color, true);
}

void Camera::DrawBoxW(Vector2D location1, Vector2D location2, unsigned int Color)
{
	location1.x += -m_location.x + D_WIN_WIDTH / 2.0f;
	location1.y += -m_location.y + D_WIN_HEIGHT / 2.0f;
	location2.x += -m_location.x + D_WIN_WIDTH / 2.0f;
	location2.y += -m_location.y + D_WIN_HEIGHT / 2.0f;

	DrawBoxW(location1, location2, Color);
}

void Camera::DrawGraph(Vector2D location, double ExRate, double Angle, int GrHandle, bool ReverseXFlag, bool ReverseYFlage)
{
	location = FitLocationToScreen(location);
	ExRate *= m_screenRatioSize;

	DxLib::DrawRotaGraphF(location.x, location.y, ExRate, Angle, GrHandle, true, ReverseXFlag, ReverseYFlage);
}

void Camera::DrawGraphW(Vector2D location, double ExRate, double Angle, int GrHandle, bool ReverseXFlag, bool ReverseYFlage)
{
	location.x += -m_location.x + D_WIN_WIDTH / 2.0f;
	location.y += -m_location.y + D_WIN_HEIGHT / 2.0f;

	DrawGraph(location, ExRate, Angle, GrHandle, ReverseXFlag, ReverseYFlage);
}

void Camera::DrawFormatString(Vector2D location, int size, unsigned int Color, const TCHAR* FormatString, ...)
{
	location = FitLocationToScreen(location);
	size *= m_screenRatioSize;

	SetFontSize(size);
	DxLib::DrawFormatStringF(location.x, location.y, Color, FormatString);
	SetFontSize(10);
}

void Camera::DrawFormatStringW(Vector2D location, int size, unsigned int Color, const TCHAR *FormatString, ...)
{
	// 長さ
	int maxLen = -1;
	int len = 0;
	// 行数
	int count = 0;
	for (int i = 0;FormatString[i] != '\0';i++)
	{
		if (FormatString[i] == '\n')
		{
			count++;
			if (maxLen == -1 || maxLen < len)
				maxLen = len;
			len = 0;
		}
		else
		{
			len++;
		}
	}
	if (maxLen == -1)
		maxLen = (int)strlen(FormatString);

	location.x -= (float)maxLen / 2.0f * size;
	location.y -= (float)count / 2.0f * size;

	location.x += -m_location.x + D_WIN_WIDTH / 2.0f;
	location.y += -m_location.y + D_WIN_HEIGHT / 2.0f;

	DrawFormatString(location, size, Color, FormatString);
}

Vector2D Camera::FitLocationToScreen(Vector2D location)
{
	location = Vec2Mult(location, m_screenRatioSize);
	location = Vec2Add(location, Vec2Mult(Vec2Mult({ D_WIN_WIDTH, D_WIN_HEIGHT }, 1.0f - m_screenRatioSize), 0.5f));
	location = Vec2Add(location, Vec2Sub(m_screenLocation, { D_WIN_WIDTH / 2.0f, D_WIN_HEIGHT / 2.0f }));

	return location;
}

bool Camera::CheckItsOnTheScreen(Vector2D location, float radius)
{
	// カメラ座標に直す
	location.x += -m_location.x + D_WIN_WIDTH / 2.0f;
	location.y += -m_location.y + D_WIN_HEIGHT / 2.0f;

	if (location.x + radius < 0 ||
		location.x - radius > D_WIN_WIDTH ||
		location.y + radius < 0 ||
		location.y - radius > D_WIN_HEIGHT)
	{
		// 画面外
		return false;
	}

	// 画面内
	return true;
}
