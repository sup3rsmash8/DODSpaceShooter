#pragma once

#include <stdlib.h>
#include <time.h>

class Random
{
public:
	static float Range(const float min, const float max)
	{
		float result = min + static_cast<float>(rand()) / (static_cast <float> (RAND_MAX / (max - min)));

		return result;
	}

	static int RangeInt(const int min, const int max)
	{
		int result = min + (float)rand() / (RAND_MAX + 1) * (max - min);

		return result;
	}

	static void SRand()
	{
		srand(time(NULL));
	}
};