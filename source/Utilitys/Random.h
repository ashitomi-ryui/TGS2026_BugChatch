#pragma once
#include <DxLib.h>

class Random
{
public:
	static int seed;

public:
	static void SetSeed(float f);

	/// <summary>
	/// ランダムな値を取得する
	/// </summary>
	/// <param name="num1">値1から</param>
	/// <param name="num2">値2まで</param>
	/// <param name="interval">間隔</param>
	/// <returns>ランダムな値</returns>
	static float GetRand(float num1 = (float)RAND_MAX, float num2 = 0.0f, float interval = 1.0f);
};