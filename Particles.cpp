#include "Particles.h"
#include "VectorExtensions.h"
#include "Library.h"
#include "ParticleEmissionShape.h"

Uint32 Particles::m_maxCount = 256;

ParticleProperties Particles::m_particleProperties[256];

bool Particles::m_enabled[256];

float Particles::m_lifetime[256];
float Particles::m_currentAge[256];

float Particles::m_v_speed[256];
float Particles::m_v_speedMult[256];

float Particles::m_v_direction[256];

// Vector2
float Particles::m_localPos_x[256];
float Particles::m_localPos_y[256];

// SDL_FRect
float Particles::m_rect_x[256];
float Particles::m_rect_y[256];
float Particles::m_rect_w[256];
float Particles::m_rect_h[256];

float Particles::m_rotation[256];
float Particles::m_rotationMult[256];

float Particles::m_imageIndex[256];
float Particles::m_imgSpeedMult[256];

float Particles::m_sizeScale[256];
float Particles::m_sizeMult[256];

std::vector<Uint32> Particles::m_activeIndices = std::vector<Uint32>();

void Particles::ProcessAll(float timeStep)
{
	size_t size = m_activeIndices.size();

	for (size_t ai = 0; ai < size; ai++)
	{
		Uint32 i = m_activeIndices[ai];

		m_currentAge[i] += timeStep;

		const float normalizedAge = static_cast<float>(m_currentAge[i]) / m_lifetime[i];

		const float dir_r = m_v_direction[i] * D2R;

		m_imageIndex[i] += ParticleProperties::EvaluateOverLifetime(m_particleProperties[i].imageCycleSpeedOverLifetime, normalizedAge) * m_imgSpeedMult[i];

		m_v_speed[i] = ParticleProperties::EvaluateOverLifetime(m_particleProperties[i].speedOverLifetime, normalizedAge) * m_v_speedMult[i];

 		m_rotation[i] += ParticleProperties::EvaluateOverLifetime(m_particleProperties[i].rotationSpeedOverLifetime, normalizedAge) * m_rotationMult[i];

		m_sizeScale[i] = ParticleProperties::EvaluateOverLifetime(m_particleProperties[i].sizeOverLifetime, normalizedAge) * m_sizeMult[i];

		Vector2 translation = Vector2(sin(dir_r), -cos(dir_r)) * m_v_speed[i];

		m_localPos_x[i] += translation.x;
		m_localPos_y[i] += translation.y;

		m_enabled[i] = normalizedAge < 1.0f;

		if (!m_enabled[i])
		{
			m_activeIndices.erase(m_activeIndices.begin() + ai);
			size = m_activeIndices.size();
		}
	}
}

void Particles::RenderAll(SDL_Renderer* renderer)
{
	for (size_t ai = 0; ai < m_activeIndices.size(); ai++)
	{
		Uint32 i = m_activeIndices[ai];

		//Vector2 renderPos = /*origin + */;
		Vector2 renderPos = { m_localPos_x[i], m_localPos_y[i] };

 		SDL_FRect sizeAndPiv = m_particleProperties[i].sizeAndPivot;
		SDL_Rect renderRect =
		{
			renderPos.x - sizeAndPiv.w * sizeAndPiv.x * m_sizeScale[i],
			renderPos.y - sizeAndPiv.h * sizeAndPiv.y * m_sizeScale[i],
			sizeAndPiv.w * m_sizeScale[i],
			sizeAndPiv.h * m_sizeScale[i]
		};

		ParticleTexture& pTex = m_particleProperties[i].m_particleTexture;

		const int renderImgIndex = (int)floor(m_imageIndex[i]);//% pp.frameCount;
		SDL_Rect cellRect = { pTex.m_cellSize.x * renderImgIndex, 0, pTex.m_cellSize.x, pTex.m_cellSize.y };

		if (renderImgIndex >= 0 && renderImgIndex < pTex.m_frameCount)
		{
			SDL_Texture* tex = pTex.m_texture/*.get()*/;

			if (tex)
 				SDL_RenderCopyEx(renderer, tex, &cellRect, &renderRect, m_rotation[i], NULL, SDL_FLIP_NONE);
		}
	}
}

void Particles::EnableParticle(std::vector<int>& outActiveIndices, const ParticleProperties properties, Uint32 count, const Vector2 pivot, ParticleEmissionShape* shape)
{
	for (Uint32 i = 0; i < m_maxCount; i++)
	{
		if (!VectorContains(m_activeIndices, i))
		{
			m_activeIndices.push_back(i);

			m_particleProperties[i] = properties;

			Vector2 pos = pivot;

			Vector2 position = shape ? pos + shape->GetRandomPosition(pivot) : pivot;

			m_localPos_x[i] = position.x;
			m_localPos_y[i] = position.y;
			m_lifetime[i] = m_particleProperties[i].GetLifetimeVariance();

			m_imageIndex[i] = 0;

			m_v_speed[i] = ParticleProperties::EvaluateOverLifetime(m_particleProperties[i].speedOverLifetime, 0);
			m_v_speedMult[i] = Random::Range(m_particleProperties[i].speedVarianceMult.x, m_particleProperties[i].speedVarianceMult.y);

			m_v_direction[i] = m_particleProperties[i].GetRandomizedDirection();

			m_rotation[i] = ParticleProperties::EvaluateOverLifetime(m_particleProperties[i].rotationSpeedOverLifetime, 0);
			m_rotationMult[i] = Random::Range(m_particleProperties[i].rotationVarianceMult.x, m_particleProperties[i].rotationVarianceMult.y);

			m_sizeScale[i] = ParticleProperties::EvaluateOverLifetime(m_particleProperties[i].sizeOverLifetime, 0);
			m_sizeMult[i] = Random::Range(m_particleProperties[i].sizeVarianceMult.x, m_particleProperties[i].sizeVarianceMult.y);

			m_imgSpeedMult[i] = Random::Range(m_particleProperties[i].imageCycleVarianceMult.x, m_particleProperties[i].imageCycleVarianceMult.y);

			m_currentAge[i] = 0;

			m_enabled[i] = true;

			count--;

			outActiveIndices.push_back(i);

			if (count <= 0)
				return;
		}
	}
}
