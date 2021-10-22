#pragma once

#include "SDL.h"
#include "ParticleProperties.h"

class ParticleEmissionShape;

struct Particles
{
public:
	static Uint32 m_maxCount;

	static ParticleProperties m_particleProperties[256];

	static bool m_enabled[256];

	static float m_lifetime[256];
	static float m_currentAge[256];

	static float m_v_speed[256];
	static float m_v_speedMult[256];

	static float m_v_direction[256];

	// Vector2
	static float m_localPos_x[256];
	static float m_localPos_y[256];

	// SDL_FRect
	static float m_rect_x[256];
	static float m_rect_y[256];
	static float m_rect_w[256];
	static float m_rect_h[256];

	static float m_rotation[256];
	static float m_rotationMult[256];

	static float m_imageIndex[256];
	static float m_imgSpeedMult[256];

	static float m_sizeScale[256];
	static float m_sizeMult[256];

	static std::vector<Uint32> m_activeIndices;

	static void RenderAll(SDL_Renderer* renderer);
	static void ProcessAll(float timeStep);
	static void EnableParticle(std::vector<int>& outActiveIndices, const ParticleProperties properties, Uint32 count, const Vector2 pivot, ParticleEmissionShape* shape);
};

