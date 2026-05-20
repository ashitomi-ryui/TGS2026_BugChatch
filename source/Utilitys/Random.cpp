#include "Random.h"
#include <math.h>
#include <DxLib.h>

int Random::seed = 0;

void Random::SetSeed(float f)
{
	seed = (int)(f * (float)0xfa2b) + rand();
}

int Random::GetRand()
{
	seed = seed << 3 >> 4;
	seed += 0x6a23;
	seed *= 0xfa2b;
	seed = fabsf(seed);
	//seed /= 3;
	seed %= RAND_MAX;
	return seed;
}
