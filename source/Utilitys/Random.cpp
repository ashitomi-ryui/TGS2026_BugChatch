#include "Random.h"
#include <math.h>

int Random::seed = 0;

void Random::SetSeed(float f)
{
	seed = (int)(f * (float)0xfa2b);
}

int Random::GetRand()
{
	seed = seed << 3 >> 4;
	seed += 0x6a23;
	seed *= 0xfa2b;
	seed = fabsf(seed);
	seed /= 3;
	return seed;
}
