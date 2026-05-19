//==========================================================
// ファイル: Math.h
// 概要: 数学的なユーティリティ関数の宣言
//==========================================================
#pragma once

#include <math.h>
#include <stdlib.h>

//=========================================================
// 型定義
//=========================================================
// 2次元ベクトル構造体
struct Vector2D
{
	float x;
	float y;
};

// 度数法から弧度法に変換する
float ToRadians(float dedrees);
// 弧度法から度数法に変換する
float ToDegrees(float radians);
// 範囲制限
float Clamp(float value, float lower, float upper);

// ベクトル加算
Vector2D Vec2Add(Vector2D a, Vector2D b);
// ベクトル減算
Vector2D Vec2Sub(Vector2D a, Vector2D b);
// ベクトル乗算
Vector2D Vec2Mult(Vector2D a, float scalar);

// ベクトルの長さを取得する
float LengthSq(Vector2D vec);
// ベクトルの長さを取得する
float Length(Vector2D vec);
// ベクトルの正規化
Vector2D Normalized(Vector2D vec);
// ベクトルの内積
float Dot(Vector2D va, Vector2D vb);
// 反射ベクトルを求める
Vector2D Reflect(Vector2D v, Vector2D n);

// 角度を求める
float FindTheAngle(Vector2D a, Vector2D b);

/// <summary>
/// 角度の移動の符号を求める
/// </summary>
/// <param name="oldAngle">前の角度</param>
/// <param name="nowAngle">今の角度</param>
/// <returns>+なら1、-なら-1</returns>
int FindTheSignOfTheAngle(float oldAngle, float nowAngle);