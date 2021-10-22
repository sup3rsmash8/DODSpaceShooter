#include "Particle_AsteroidExplosion.h"

ParticleTexture Particle_AsteroidExplosion::m_explosionTex = ParticleTexture();
const char* Particle_AsteroidExplosion::m_explosionTexPath = "Resources/explosion.png";

ParticleTexture Particle_AsteroidExplosion::m_asteroidTex = ParticleTexture();
const char* Particle_AsteroidExplosion::m_asteroidTexPath = "Resources/AsteroidBrown.png";

Particle_AsteroidExplosion::Particle_AsteroidExplosion()
{
	if (!m_explosionTex.m_texture)
	{
		//std::shared_ptr<SDL_Texture> tex;
		SDL_Texture* tex = nullptr;

		SetTextureFromFile(m_explosionTexPath, tex);
		m_explosionTex = ParticleTexture(tex, Vector2Int(64, 64), 16);
	}

	if (!m_asteroidTex.m_texture)
	{
		//std::shared_ptr<SDL_Texture> tex;
		SDL_Texture* tex = nullptr;

		SetTextureFromFile(m_asteroidTexPath, tex);
		m_asteroidTex = ParticleTexture(tex, Vector2Int(160, 160), 1);
	}

	std::map<int, ParticleProperties> explosionProperties =
	{
		{ 1, ParticleProperties(m_explosionTex, 1, VEC2_ZERO, VEC2_ZERO, VEC2_ZERO, VEC2_ONE * 0.5f, VEC2_ONE, { 0.5f, 0.5f, 64, 64 }, { 0.8f, 1.2f }) },
		{ 32, ParticleProperties(m_asteroidTex, 32, { -360, 360 }, { 2, 0.2f }, { 12, 7 }, VEC2_ZERO, VEC2_ONE, { 0.5f, 0.5f, 12, 8 }, { 0.8f, 2.0f }, { 0.3f, 1.5f }, { 0.3f, 1.5f }, VEC2_ONE, { 0.3f, 1.5f }) }
	};

	SetParticleProperties(explosionProperties);
}
