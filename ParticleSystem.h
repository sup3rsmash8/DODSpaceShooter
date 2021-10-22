#pragma once

#include "GameObject.h"
#include "ObjectPool.h"
#include "ParticleEmissionShape.h"
#include "Particles.h"
#include "SDL_thread.h"

class GameHandler;

enum class ParticleSystemState
{
	PLAYING,
	STOPPED,
	PAUSED
};

/// <summary>
/// Object that helps storing particle properties and automatically
/// apply them to particles for cool effects.
/// </summary>
class ParticleSystem : public GameObject
{
	friend class Particle;
	friend class GameEngine;

public:
	ParticleSystem();
	ParticleSystem(std::map<int, ParticleProperties> particlePropertiesAndCount, ParticleEmissionShape* emissionShape, const float duration, /*const bool loop, const bool particlesDieWithSystem, const bool particlesAreInLocalSpace,*/ const Vector2 position, float rotation = 0, bool enabled = true);
	~ParticleSystem();

private:
	static SDL_mutex* m_particleUpdateMutex;

	std::vector<int> m_myActiveParticles = std::vector<int>();

	ParticleEmissionShape* m_emissionShape = nullptr;

	bool m_loop;

	// Should all remaining active particles deactivate
	// when the particle system does?
	//bool m_particlesDieWithSystem;

	// Should all particles move with the system, or should
	// they be independent?
	//bool m_particlesAreInLocalSpace;

	float m_duration;

	ParticleSystemState state;

	std::map<int, ParticleProperties> m_particlePropertiesAndCount = std::map<int, ParticleProperties>();

public:
	void SetParticleProperties(/*const */std::map<int, ParticleProperties>& particlePropsAndCount);

	void Play();

protected:
	//virtual void Update(float deltaTime) override;

	// NOTE: Child particle system classes do NOT need to override this
	// since the game engine uses this value in the particle thread.
	virtual GameObjectID GetID() const override final { return GameObjectID::PARTICLE_SYSTEM; }

private:
	// Multithread function that updates all particles currently active.
	// void* ptr = &GameEngine::m_deltaTime
	static int Thread_ParticleUpdate(void* floatDeltaTime);
};
