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
float VecATan2(Vector2D a, Vector2D b);
 
/// <summary>
/// 角度を比較する
/// </summary>
/// <param name="Angle1">前の角度</param>
/// <param name="Angle2">今の角度</param>
/// <param name="tolerance">「=」判定になる許容範囲</param>
/// <returns>「＜」なら「1」、「＞」なら「-1」、「＝」なら「0」</returns>
int AngleComparison(float Angle1, float Angle2, float tolerance = 0.0f);

/// <summary>
/// 徐々に向ける
/// </summary>
/// <param name="that">変数</param>
/// <param name="angle">向けたい方向</param>
/// <param name="turningSpeed">方向転換速度</param>
void GraduallyTurn(float& that, float angle, float turningSpeed);