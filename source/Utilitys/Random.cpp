#include "Random.h"
#include <math.h>
#include <DxLib.h>

int Random::seed = 0;

void Random::SetSeed(float f)
{
	seed = (int)(f * (float)0xfa2b) + DxLib::GetRand(RAND_MAX);
}

float Random::GetRand(float num1, float num2, float interval)
{
	seed += 0x6a23;
	seed *= 0xfa2b;
	seed += DxLib::GetRand(RAND_MAX);
	seed = abs(seed);
	seed %= RAND_MAX;

	// 間隔を0にしない（0で割らないため）
	if (interval == 0.0f)
	{
		interval = 1.0f;
	}
	// 値1を最小値に
	if (num1 > num2)
	{
		float num = num1;
		num1 = num2;
		num2 = num;
	}

	// 設定した最大値も含める
	num2 += interval;
	
	// 出したいランダムな値の数がランダム最大値を越さないようにする
	if ((num2 - num1) / interval > RAND_MAX)
	{
		num2 = num1 + RAND_MAX * interval;
	}

	// 0から出したいランダムな値の数までのランダムな値にする
	float random = (float)seed;
	random = (float)((int)random % (int)((num2 - num1) / interval));

	// 間隔を空ける
	random *= interval;
	// 最小値分ずらす
	random += num1;

	return random;
}
