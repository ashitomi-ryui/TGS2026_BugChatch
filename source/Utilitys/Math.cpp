//==========================================================
// ファイル: Math.cpp
// 概要: 数学ユーティリティ関数の実装
//==========================================================
#include "Math.h"
#include "DxLib.h"
#define _USE_MATH_DEFINES
#include <math.h>

// 度(°)をラジアンへ変換
float ToRadians(float degrees)
{
	return degrees * (float)M_PI / 180.0f;
}

// ラジアンを度(°)へ変換
float ToDegrees(float radians)
{
	return radians * 180.0f / (float)M_PI;
}

// 値を[lower, upper]に収める
float Clamp(float value, float lower, float upper)
{
	return fminf(upper, fmaxf(lower, value));
}

// 2Dベクトル加算
Vector2D Vec2Add(Vector2D a, Vector2D b)
{
	Vector2D ret = {};
	ret.x = a.x + b.x;
	ret.y = a.y + b.y;
	return ret;
}

// 2Dベクトル減算
Vector2D Vec2Sub(Vector2D a, Vector2D b)
{
	Vector2D ret = {};
	ret.x = a.x - b.x;
	ret.y = a.y - b.y;
	return ret;
}

// スカラー乗算
Vector2D Vec2Mult(Vector2D a, float scalar)
{
	Vector2D ret = {};
	ret.x = a.x * scalar;
	ret.y = a.y * scalar;
	return ret;
}

// 長さの二乗
float LengthSq(Vector2D vec)
{
	float tx = vec.x * vec.x;
	float ty = vec.y * vec.y;
	return (tx + ty);
}

// ベクトル長
float Length(Vector2D vec)
{
	float result = sqrtf(LengthSq(vec));
	return result;
}

// 正規化ベクトル
Vector2D Normalized(Vector2D vec)
{
	float len = Length(vec);
	Vector2D result = {};
	result.x /= len;
	result.y /= len;
	return result;
}

// ドット積
float Dot(Vector2D va, Vector2D vb)
{
	return (va.x * vb.x + va.y * vb.y);
}

// 法線 n に対する v の反射ベクトル
Vector2D Reflect(Vector2D v, Vector2D n)
{
	Vector2D result = v;
	float d = Dot(v, n);

	result.x -= 2.0f * d * n.x;
	result.y -= 2.0f * d * n.y;

	return result;
}

float FindTheAngle(Vector2D a, Vector2D b)
{
	if(a.x < b.x)
	{
		if (a.y > b.y)
		{
			return atanf(-(a.y - b.y) / (a.x - b.x));
		}
		else
		{
			return atanf(-(a.y - b.y) / (a.x - b.x)) + DX_PI_F * 2.0f;
		}
	}
	if (a.x > b.x)
	{
		return atanf(-(a.y - b.y) / (a.x - b.x)) + DX_PI_F;
	}
	if (a.y > b.y)

	{
		return 0.5f * DX_PI_F;
	}
	return 1.5f * DX_PI_F;
}

int AngleComparison(float Angle1, float Angle2, float tolerance)
{
	if (Angle1 >= 0.0f)
	{
		Angle1 -= (float)((int)(Angle1 / (2.0f * DX_PI_F))) * (2.0f * DX_PI_F);
	}
	else
	{
		Angle1 -= (float)((int)(Angle1 / (2.0f * DX_PI_F)) - 1.0f) * (2.0f * DX_PI_F);
	}
	
	if (Angle2 >= 0.0f)
	{
		Angle2 -= (float)((int)(Angle2 / (2.0f * DX_PI_F))) * (2.0f * DX_PI_F);
	}
	else
	{
		Angle2 -= (float)((int)(Angle2 / (2.0f * DX_PI_F)) - 1.0f) * (2.0f * DX_PI_F);
	}

	// 差が許容範囲より小さいなら
	if (fabsf(Angle2 - Angle1) <= tolerance || 
		fabsf((Angle2 + 2.0f * DX_PI_F) - Angle1) <= tolerance ||
		fabsf(Angle2 - (Angle1 + 2.0f * DX_PI_F)) <= tolerance)
	{
		// Angle1 = Angle2
		return 0;
	}

	// Angle1がπより小さいとき
	if (Angle1 < DX_PI_F)
	{
		// Angle2がAngle1よりも大きいとき
		if (Angle2 > Angle1)
		{
			// Angle2がAngle1の反対側より大きいなら
			if (Angle2 > Angle1 + 1.0f * DX_PI_F)
			{
				// Angle1 > Angle2
				return -1;
			}
			// Angle2がAngle1の反対側より小さいなら
			else
			{
				// Angle1 < Angle2
				return 1;
			}
		}
		// Angle2がAngle1よりも小さいなら
		else
		{
			// Angle1 > Angle2
			return -1;
		}
	}
	// Angle1がπより大きいとき
	else
	{
		// Angle2がAngle1よりも小さいとき
		if (Angle2 < Angle1)
		{
			// Angle2がAngle1の反対側より小さいなら
			if (Angle2 < Angle1 - 1.0f * DX_PI_F)
			{
				// Angle1 < Angle2
				return 1;
			}
			// Angle2がAngle1の反対側より大きいなら
			else
			{
				// Angle1 > Angle2
				return -1;
			}
		}
		// Angle2がAngle1よりも大きいなら
		else
		{
			// Angle1 < Angle2
			return 1;
		}
	}
}
