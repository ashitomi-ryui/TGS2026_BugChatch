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

float VecATan2(Vector2D a, Vector2D b)
{
	float result = atan2f(a.x - b.x, b.y - a.y);
	result += DX_PI_F;
	return result;
}

float AngleSub(float Angle1, float Angle2)
{
	// Angle1を0.0fから2.0fに
	if (Angle1 >= 0.0f)
	{
		Angle1 -= (float)((int)(Angle1 / (2.0f * DX_PI_F))) * (2.0f * DX_PI_F);
	}
	else
	{
		Angle1 -= (float)((int)(Angle1 / (2.0f * DX_PI_F)) - 1.0f) * (2.0f * DX_PI_F);
	}

	// Angle2を0.0fから2.0fに
	if (Angle2 >= 0.0f)
	{
		Angle2 -= (float)((int)(Angle2 / (2.0f * DX_PI_F))) * (2.0f * DX_PI_F);
	}
	else
	{
		Angle2 -= (float)((int)(Angle2 / (2.0f * DX_PI_F)) - 1.0f) * (2.0f * DX_PI_F);
	}

	// Angle1とAngle2の差が半周より大きいとき
	if (fabsf(Angle1 - Angle2) > DX_PI_F)
	{
		// Angle1の方が大きいとき
		if (Angle1 > Angle2)
		{
			// Angle1とAngle2の差に一周を引いた値を返す
			return Angle1 - Angle2 - 2.0f * DX_PI_F;
		}
		// Angle2の方が大きいとき
		// Angle1とAngle2の差に一周を足した値を返す
		return Angle1 - Angle2 + 2.0f * DX_PI_F;
	}

	// Angle1とAngle2の差を返す
	return Angle1 - Angle2;
}

int AngleComparison(float Angle1, float Angle2, float tolerance)
{
	float dif = AngleSub(Angle1, Angle2);

	// 差が許容範囲より大きいとき
	if (fabsf(dif) > tolerance)
	{
		// Angle1の方が大きいなら
		if (dif > 0.0f)
		{
			// Angle1 > Angle2
			return -1;
		}
		// Angle2の方が大きいなら
		// Angle1 < Angle2
		return 1;
	}

	// Angle1 = Angle2
	return 0;
}

void GraduallyTurn(float& that, float angle, float turningSpeed)
{
	// thatをturningSpeedの数だけangleに向ける
	that += AngleComparison(that, angle) * turningSpeed;
	if (AngleComparison(that, angle, turningSpeed) == 0)
	{
		that = angle;
	}
}

void FixGradually(float& that, float f, float fixSpeed)
{
	// thatをfixSpeedの数だけfに向ける
	if (fabsf(that - f) < fixSpeed)
	{
		that = f;
	}
	else if (that < f)
	{
		that += fixSpeed;
	}
	else
	{
		that -= fixSpeed;
	}
}