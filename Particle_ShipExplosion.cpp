#include "Particle_ShipExplosion.h"
ParticleTexture Particle_ShipExplosion::m_explosionTex = ParticleTexture();
const char* Particle_ShipExplosion::m_explosionTexPath = "Resources/explosion.png";

ParticleTexture Particle_ShipExplosion::m_shipTex = ParticleTexture();
const char* Particle_ShipExplosion::m_shipTexPath = "Resources/Ship.png";

Particle_ShipExplosion::Particle_ShipExplosion()
{
	if (!m_explosionTex.m_texture)
	{
		//std::shared_ptr<SDL_Texture> tex;
		SDL_Texture* tex = nullptr;

		SetTextureFromFile(m_explosionTexPath, tex);
		m_explosionTex = ParticleTexture(tex, Vector2Int(64, 64), 16);
	}

	if (!m_shipTex.m_texture)
	{
		//std::shared_ptr<SDL_Texture> tex;
		SDL_Texture* tex = nullptr;

		SetTextureFromFile(m_shipTexPath, tex);
		m_shipTex = ParticleTexture(tex, Vector2Int(160, 160), 1);
	}

	std::map<int, ParticleProperties> explosionProperties =
	{
		{ 1, ParticleProperties(m_explosionTex, 1, VEC2_ZERO, VEC2_ZERO, VEC2_ZERO, VEC2_ONE * 0.5f, VEC2_ONE, { 0.5f, 0.5f, 64, 64 }, { 0.8f, 1.2f }) },
		{ 32, ParticleProperties(m_shipTex, 32, { -360, 360 }, { 2, 0.2f }, { 12, 7 }, VEC2_ZERO, VEC2_ONE, { 0.5f, 0.5f, 12, 8 }, { 0.8f, 2.0f }, { 0.3f, 1.5f }, { 0.3f, 1.5f }, VEC2_ONE, { 0.3f, 1.5f }) }
	};

	SetParticleProperties(explosionProperties);
}
