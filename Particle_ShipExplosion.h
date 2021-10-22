#pragma once

#include "ParticleSystem.h"

class Particle_ShipExplosion final : public ParticleSystem
{
public:
	Particle_ShipExplosion();

protected:
	//virtual GameObjectID GetID() const override { return GameObjectID::PARTICLE_ASTEROIDEXPLOSION; }

private:
	static ParticleTexture m_explosionTex;

	static const char* m_explosionTexPath;

	static ParticleTexture m_shipTex;

	static const char* m_shipTexPath;
};

