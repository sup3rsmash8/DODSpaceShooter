#include "Collider.h"
#include "EnemyAsteroid.h"
#include "Random.h"

#include <iostream>

const char* EnemyAsteroid::m_asteroidTexturePath = "Resources/AsteroidBrown.png";

//std::shared_ptr<SDL_Texture> EnemyAsteroid::m_asteroidTexture = nullptr;
SDL_Texture* EnemyAsteroid::m_asteroidTexture = nullptr;

EnemyAsteroid::EnemyAsteroid()
{
	//SetTextureFromFile(m_asteroidTexturePath, m_asteroidTexture);

	//int w, h;

	//if (SDL_QueryTexture(m_asteroidTexture.get(), NULL, NULL, &w, &h) == -1)
	//{
	//	std::cout << SDL_GetError() << std::endl;
	//}

	//m_texture = GameTexture(m_asteroidTexture, Vector2(static_cast<float>(w), static_cast<float>(h)), Vector2(0.5f, 0.5f));

	//m_collider = new Collider(this, 16.f, &m_onCollisionEvent);

	//if (!m_part_asteroidExplosion)
	//{
	//	m_part_asteroidExplosion = new Particle_AsteroidExplosion();
	//}

	//Initialize();
}

EnemyAsteroid::EnemyAsteroid(const Vector2 position, float rotation, bool enabled) : GameObject(position, rotation, enabled)
{
	
}

EnemyAsteroid::~EnemyAsteroid()
{
	delete m_collider;

	// change this later
	if (m_part_asteroidExplosion)
		m_part_asteroidExplosion->Destroy();
}

void EnemyAsteroid::OnEstablished()
{
	SetTextureFromFile(m_asteroidTexturePath, m_asteroidTexture);

	int w, h;

	if (SDL_QueryTexture(m_asteroidTexture/*.get()*/, NULL, NULL, &w, &h) == -1)
	{
		std::cout << SDL_GetError() << std::endl;
	}

	m_texture = GameTexture(m_asteroidTexture, Vector2(static_cast<float>(w), static_cast<float>(h)) * .25f, Vector2(0.5f, 0.5f));

	m_collider = new Collider(this, 16.f, &m_onCollisionEvent);

	if (!m_part_asteroidExplosion)
	{
		m_part_asteroidExplosion = new Particle_AsteroidExplosion();
	}

	Initialize();
}

void EnemyAsteroid::OnCollision(GameObject* other)
{
	if (!other)
		return;

	if (other->GetID() == GameObjectID::PLAYER_PROJECTILE)
	{
		SetEnabled(false);

		if (m_part_asteroidExplosion)
		{
			m_part_asteroidExplosion->SetPosition(GetPosition());
			m_part_asteroidExplosion->Play();
		}
	}
}

void EnemyAsteroid::Initialize()
{
	m_mySpeed = Random::Range(75.f, 200.f);
	SetXSpeed(-m_mySpeed);

	m_rotationSpeed = Random::Range(-360.f, 360.f);

	m_lifetimer = 0;
}

void EnemyAsteroid::Update(float deltaTime)
{
	SetRotation(GetRotation() + m_rotationSpeed * deltaTime);

	if (m_lifetimer >= m_lifetime)
	{
		SetEnabled(false);
	}
	else
	{
		m_lifetimer += deltaTime;
	}
}

void EnemyAsteroid::DrawUpdate(SDL_Renderer* renderer)
{
	if (!m_texture.texture)
	{
		printf("Texture could not be rendered: %s\n", SDL_GetError());
	}
}

void EnemyAsteroid::OnEnabled()
{
	Initialize();
}


