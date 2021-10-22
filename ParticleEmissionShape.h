#pragma once

#include "Library.h"
#include "Random.h"

//#include <algorithm>

struct CircleEmitterShape
{
	float radius;
	float innerRadius;
};

struct RectangleEmitterShape
{
	SDL_Rect rect;
};

/// <summary>
/// Base class for particle emitters that spawn according to a shape,
/// such as a rectangle or circle.
/// </summary>
class ParticleEmissionShape
{
public:
	// Returns a coordinate according to the defined shape.
	virtual Vector2 GetRandomPosition(Vector2 pivot) = 0;
};

class CircleEmitter: public ParticleEmissionShape
{
public:
	CircleEmitter(float radius, float innerRadius)
	{
		this->radius = radius;
		this->innerRadius = innerRadius;
	}

	float radius;
	float innerRadius;

	Vector2 GetRandomPosition(Vector2 pivot)
	{
		if (radius < 0)
			radius = 0;

		if (innerRadius < 0)
			innerRadius = 0;

		if (innerRadius > radius)
			innerRadius = radius;

		float rot = (rand() % 360) * D2R;
		Vector2 dir = Vector2(sin(rot), -cos(rot));

		float magn = Random::Range(innerRadius, radius);

		return pivot + dir * magn;
	}
};

class RectangleEmitter : public ParticleEmissionShape
{
public:
	RectangleEmitter(SDL_Rect rect)
	{
		this->rect = rect;
	}

	SDL_Rect rect;

	Vector2 GetRandomPosition(Vector2 pivot)
	{
		Vector2 rectOffset =
		{
			rect.x + Random::Range(0, rect.w),
			rect.y + Random::Range(0, rect.h)
		};

		return pivot + rectOffset;
	}
};