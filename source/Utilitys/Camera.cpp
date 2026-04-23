#include "DxLib.h"
#include "Camera.h"
#include <cmath>

// コンストラクタ
Camera::Camera()
{
	location = { 0.0f, 0.0f };
}

// デストラクタ
Camera::~Camera()
{
}

// 更新処理
void Camera::Update()
{

}

void Camera::Draw() const
{
}

void Camera::DrawLineW(int x1, int y1, int x2, int y2, unsigned int Color)
{
	DrawLine(x1, y1, x2, y2, Color, true);
}

void Camera::DrawTriangleW(int x1, int y1, int x2, int y2, int x3, int y3, unsigned int Color)
{
	DrawTriangle(x1, y1, x2, y2, x3, y3, Color, true);
}

void Camera::DrawCircleW(int x, int y, int r, unsigned int Color)
{
	
	DrawCircle(x, y, r, Color, true);
}
