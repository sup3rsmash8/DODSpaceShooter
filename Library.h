#pragma once
#include "SDL.h"
#include <vector>
#include <cmath>

#define VEC2_ZERO Vector2(0, 0)
#define VEC2_ONE Vector2(1, 1)
#define VEC2_UP Vector2(0, 1)
#define VEC2_DOWN Vector2(0, -1)
#define VEC2INT_DEFAULTSIZE Vector2Int(8, 8)
#define RAND01 (rand() / ((float) RAND_MAX))
#define TAU 6.28318530717959f
#define D2R 0.0174533f
#define R2D 57.2957795f

struct Vector2;

struct Vector2Int
{
public:
	Vector2Int()
	{
		x = 0;
		y = 0;
	}

	Vector2Int(int x, int y)
	{
		this->x = x;
		this->y = y;
	}

	Vector2Int(Vector2 vector);

	int x;
	int y;

	Vector2Int operator*(const float rhs)
	{
		return Vector2Int(static_cast<int>(round(this->x * rhs)), static_cast<int>(round(this->y * rhs)));
	}

	Vector2Int operator+(const Vector2Int rhs)
	{
		return Vector2Int(x + rhs.x, y + rhs.y);
	}
};

struct Vector2
{
public:
	Vector2()
	{
		x = 0.0f;
		y = 0.0f;
	}
	Vector2(float x, float y)
	{
		this->x = x;
		this->y = y;
	}

	float x;
	float y;

	float sqrMagnitude()
	{
		return x * x + y * y;
	}

	float magnitude()
	{
		return sqrt(sqrMagnitude());
	}

	void Normalize()
	{
		float length = magnitude();
		if (length > 0)
		{
			x /= length;
			y /= length;
		}
	}

	Vector2 normalized()
	{
		float length = magnitude();
		Vector2 vector = Vector2(x, y);
		if (length > 0)
		{
			vector.x /= length;
			vector.y /= length;
		}
		return vector;
	}

	static float Dot(Vector2 a, Vector2 b)
	{
		return a.x * b.x + a.y * b.y;
	}

	static float Distance(const Vector2 a, const Vector2 b)
	{
		Vector2 ab = { a.x - b.x, a.y - b.y };

		return ab.magnitude();
	}

	static Vector2 GetForward(float dRotation)
	{
		dRotation *= D2R;
		Vector2 fwd = { -cosf(dRotation), sinf(dRotation) };
		return fwd;
	}

	static Vector2 GetUp(float dRotation)
	{
		dRotation *= D2R;
		Vector2 up = { sinf(dRotation), -cosf(dRotation) };
		return up;
	}

	static Vector2 ConvertToVector2(Vector2Int input)
	{
		return Vector2(static_cast<float>(input.x), static_cast<float>(input.y));
	}

	Vector2 operator+(const Vector2 rhs)
	{
		return Vector2(x + rhs.x, y + rhs.y);
	}

	void operator+=(const Vector2 rhs)
	{
		x += rhs.x;
		y += rhs.y;
	}

	Vector2 operator-(const Vector2 rhs)
	{
		return Vector2(x - rhs.x, y - rhs.y);
	}

	Vector2 operator-()
	{
		return Vector2(-x, -y);
	}

	void operator-=(const Vector2 rhs)
	{
		x -= rhs.x;
		y -= rhs.y;
	}

	Vector2 operator*(const float rhs)
	{
		return Vector2(x * rhs, y * rhs);
	}

	void operator*=(const float rhs)
	{
		x *= rhs;
		y *= rhs;
	}

	Vector2 operator*(const Vector2 rhs)
	{
		return Vector2(x * rhs.x, y * rhs.y);
	}

	void operator*=(const Vector2 rhs)
	{
		x *= rhs.x;
		y *= rhs.y;
	}

	bool Equals(const Vector2 rhs)
	{
		return x == rhs.x && y == rhs.y;
	}

	bool operator==(const Vector2 rhs)
	{
		return Equals(rhs);
	}

	bool operator!=(const Vector2 rhs)
	{
		return !Equals(rhs);
	}
};


class Library
{
public:
	bool static IsInRect(Vector2Int pos, struct SDL_Rect r)
	{
		return (pos.x >= r.x) && (pos.y >= r.y) &&
			(pos.x < r.x + r.w) && (pos.y < r.y + r.h);
	}

	float static clamp(float value, float min, float max)
	{
		if (value >= min && value <= max)
			return value;

		if (value < min)
			return min;

		if (value > max)
			return max;
	}

	float static InverseLerp(float a, float b, float value)
	{
		return (value - a) / (b - a);
	}

	float static Lerp(float a, float b, float t) { return (1 - t) * a + t * b; }

	Vector2 static Lerp(Vector2 a, Vector2 b, float t) { return Vector2(Lerp(a.x, b.x, t), Lerp(a.y, b.y, t)); }
};

