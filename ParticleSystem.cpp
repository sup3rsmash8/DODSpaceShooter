#include "ParticleSystem.h"
#include "Statics.h"

SDL_mutex* ParticleSystem::m_particleUpdateMutex = SDL_CreateMutex();

ParticleSystem::ParticleSystem()
{
	m_particlePropertiesAndCount = std::map<int, ParticleProperties>();

	m_emissionShape = nullptr;

	//m_loop = false;
	//m_particlesDieWithSystem = true;
	m_duration = 0;
	//m_particlesAreInLocalSpace = true;
	state = ParticleSystemState::STOPPED;
}

ParticleSystem::ParticleSystem(std::map<int, ParticleProperties> particlePropertiesAndCount, ParticleEmissionShape* emissionShape, const float duration, /*const bool loop, const bool particlesDieWithSystem, const bool particlesAreInLocalSpace,*/ const Vector2 position, float rotation, bool enabled)
{
	m_particlePropertiesAndCount = particlePropertiesAndCount;

	m_emissionShape = emissionShape;

	//m_loop = loop;
	//m_particlesDieWithSystem = particlesDieWithSystem;
	m_duration = duration;
	//m_particlesAreInLocalSpace = particlesAreInLocalSpace;
	state = ParticleSystemState::STOPPED;
}

ParticleSystem::~ParticleSystem()
{
	delete m_emissionShape;
}

void ParticleSystem::SetParticleProperties(/*const */std::map<int, ParticleProperties>& particlePropsAndCount)
{
	m_particlePropertiesAndCount = particlePropsAndCount;
}

void ParticleSystem::Play()
{
	m_myActiveParticles.clear();

	Vector2 spawnPos;

	//for (auto& key : m_particlePropertiesAndCount)
	//{
	//	GetListOfParticles(m_myActiveParticles, key.first, true, key.second);
	//}

	float spawnTime = Statics::GetGameEngine()->Time();

	//Particles::EnableParticle
	for (auto& key : m_particlePropertiesAndCount)
	{
		std::vector<int> enabledParticles;
		Particles::EnableParticle(enabledParticles, key.second, key.first, GetPosition(), m_emissionShape);

		m_myActiveParticles.insert(m_myActiveParticles.end(), enabledParticles.begin(), enabledParticles.end());
	}

	//for (size_t i = 0, ilen = m_myActiveParticles.size(); i < ilen; ++i)
	//{
	//	if (!m_myActiveParticles[i])
	//		continue;

	//	//Vector2 spawnPos; /*= m_emissionShape->GetRandomPosition(VEC2_ZERO);*/
	//	//if (m_emissionShape)
	//	//{
	//	//	spawnPos = m_emissionShape->GetRandomPosition(VEC2_ZERO);
	//	//}

	//m_myActiveParticles[i]->OnStart(spawnPos, spawnTime);
	//}
}

int ParticleSystem::Thread_ParticleUpdate(void* floatDeltaTime)
{
	float deltaTime = *((float*)floatDeltaTime);

	if (deltaTime > 1)
		deltaTime = 1;

	if (SDL_LockMutex(m_particleUpdateMutex) == 0)
	{
		GameBase* gameBase = Statics::GetGameBase();

		Particles::ProcessAll(deltaTime);

		SDL_UnlockMutex(m_particleUpdateMutex);
	}

	return 0;
}
