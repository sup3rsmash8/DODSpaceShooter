#pragma once

#include "ParticleSystem.h"

class Particle_AsteroidExplosion final : public ParticleSystem
{
public:
	Particle_AsteroidExplosion();

protected:
	//virtual GameObjectID GetID() const override { return GameObjectID::PARTICLE_ASTEROIDEXPLOSION; }

private:
	static ParticleTexture m_explosionTex;
	
	static const char* m_explosionTexPath;

	static ParticleTexture m_asteroidTex;

	static const char* m_asteroidTexPath;
};

