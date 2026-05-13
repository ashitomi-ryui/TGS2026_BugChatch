#pragma once

class Random
{
public:
	static int seed;

public:
	static void SetSeed(float f);
	static int GetRand();
};