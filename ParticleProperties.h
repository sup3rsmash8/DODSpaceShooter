#pragma once

#include "ParticleTexture.h"
#include "Random.h"

struct ParticleProperties
{
	ParticleProperties() 
	{
		this->m_particleTexture = ParticleTexture();
		this->lifetime = 0;
		this->lifetimeVarianceMultiplier = VEC2_ZERO;
		this->directionArc = VEC2_ZERO;
		this->speedOverLifetime = VEC2_ZERO;
		this->rotationSpeedOverLifetime = VEC2_ZERO;
		this->imageCycleSpeedOverLifetime = VEC2_ZERO;
		this->sizeOverLifetime = VEC2_ZERO;
		this->sizeAndPivot = { 0.f, 0.f, 0.f, 0.f };

		this->speedVarianceMult = VEC2_ZERO;
		this->rotationVarianceMult = VEC2_ZERO;
		this->imageCycleVarianceMult = VEC2_ZERO;
		this->sizeVarianceMult = VEC2_ZERO;
	}

	ParticleProperties(ParticleTexture texture, float lifetime, Vector2 directionArc, Vector2 speedOverLifetime, Vector2 rotationSpeedOverLifetime, Vector2 imageCycleSpeedOverLifetime, Vector2 sizeOverLifetime, SDL_FRect sizeAndPivot, Vector2 lifetimeVarianceMult = VEC2_ONE, Vector2 speedVarianceMult = VEC2_ONE, Vector2 rotationVarianceMult = VEC2_ONE, Vector2 imageVarianceMult = VEC2_ONE, Vector2 sizeVarianceMult = VEC2_ONE)
	{
		this->m_particleTexture = texture;
		this->lifetime = lifetime;
		this->lifetimeVarianceMultiplier = lifetimeVarianceMult;
		this->directionArc = directionArc;
		this->speedOverLifetime = speedOverLifetime;
		this->rotationSpeedOverLifetime = rotationSpeedOverLifetime;
		this->imageCycleSpeedOverLifetime = imageCycleSpeedOverLifetime;
		this->sizeOverLifetime = sizeOverLifetime;
		this->sizeAndPivot = sizeAndPivot;

		this->speedVarianceMult = speedVarianceMult;
		this->rotationVarianceMult = rotationVarianceMult;
		this->imageCycleVarianceMult = imageVarianceMult;
		this->sizeVarianceMult = sizeVarianceMult;
	}

	ParticleTexture m_particleTexture = ParticleTexture();

	/// <summary>
	/// For how long should the particle be alive for?
	/// </summary>
	float lifetime = 0;

	/// <summary>
	/// Randomly multiplies the base particle lifetime on spawn.
	/// </summary>
	Vector2 lifetimeVarianceMultiplier = { 0, 0 };
	float GetLifetimeVariance() { return Random::Range(lifetimeVarianceMultiplier.x, lifetimeVarianceMultiplier.y); }

	/// <summary>
	// The range of angles the particle may move in.
	// X = The lowest direction angle, Y = The highest direction angle.
	/// </summary>
	Vector2 directionArc = { 0, 0 };
	float GetRandomizedDirection() { return Random::Range(directionArc.x, directionArc.y); }

	/// <summary>
	/// The speed at which the particle moves
	/// in its direction. 
	/// X = The speed at spawn, Y = The speed at destruction.
	/// </summary>
	Vector2 speedOverLifetime = { 0, 0 };

	Vector2 speedVarianceMult = { 0, 0 };

	/// <summary>
	/// The speed at which the particle rotates.
	/// X = The speed at spawn, Y = The speed at destruction.
	/// </summary>
	Vector2 rotationSpeedOverLifetime = { 0, 0 };

	Vector2 rotationVarianceMult = { 0, 0 };

	/// <summary>
	/// The speed at which the particle cycles
	/// through the image sheet. Frames are cycled through
	/// each integer number.
	/// X = The speed at spawn, Y = The speed at destruction.
	/// </summary>
	Vector2 imageCycleSpeedOverLifetime = { 0, 0 };

	Vector2 imageCycleVarianceMult = { 0, 0 };

	/// <summary>
	/// The size multiplier of the particle.
	/// X = The size at spawn, Y = The size at destruction.
	/// </summary>
	Vector2 sizeOverLifetime = { 0, 0 };

	Vector2 sizeVarianceMult = { 0, 0 };

	/// <summary>
	/// The rect defining the particle's pixel size and
	/// pivot point. Keep in mind that the pivot point is
	/// normalized!
	/// </summary>
	SDL_FRect sizeAndPivot = { 0, 0, 0, 0 };

	static float EvaluateOverLifetime(const Vector2 overLifetime, float normalizedTime) { return overLifetime.x + (overLifetime.y - overLifetime.x) * std::max<float>(0, std::min<float>(normalizedTime, 1)); }
};