#include "EnemySpaceShip.h"
#include "Particle_ShipExplosion.h"
#include <iostream>

const char* EnemySpaceShip::m_standardTexturePath = "Resources/ShipGray.png";

SDL_Texture* EnemySpaceShip::m_standardTexture = nullptr;
//std::shared_ptr<SDL_Texture> EnemySpaceShip::m_standardTexture = nullptr;

EnemySpaceShip::EnemySpaceShip()
{
	int rnd = Random::RangeInt(0, 3);
	switch (rnd)
	{
	case 0:
		m_movePattern = MovePattern::STRAIGHT;
		break;

	case 1:
		m_movePattern = MovePattern::SINWAVE;
		break;

	case 2:
		m_movePattern = MovePattern::MOVE_STOP_MOVE;
		break;
	}
}

EnemySpaceShip::EnemySpaceShip(MovePattern movePattern, const Vector2 position, float rotation, bool enabled) : GameObject(position, rotation, enabled)
{
	m_movePattern = movePattern;

	//SetTextureFromFile(m_standardTexturePath, m_standardTexture);

	//int w, h;

	//if (SDL_QueryTexture(m_standardTexture.get(), NULL, NULL, &w, &h) == -1)
	//{
	//	std::cout << SDL_GetError() << std::endl;
	//}
	//else
	//{
	//	printf("%i, %i", w, h);
	//}

	//m_texture = GameTexture(m_standardTexture, Vector2(static_cast<float>(w), static_cast<float>(h)), Vector2(0.5f, 0.5f));

	//SetRotation(-90);

	//m_collider = new Collider(this, 16.f, &m_onCollisionEvent);


	//if (!m_part_shipExplosion)
	//{
	//	m_part_shipExplosion = new Particle_ShipExplosion();
	//}

	//Initialize();
}

void EnemySpaceShip::OnEstablished()
{
	SetTextureFromFile(m_standardTexturePath, m_standardTexture);

	int w, h;

	if (SDL_QueryTexture(m_standardTexture/*.get()*/, NULL, NULL, &w, &h) == -1)
	{
		std::cout << SDL_GetError() << std::endl;
	}

	m_texture = GameTexture(m_standardTexture, Vector2(static_cast<float>(w), static_cast<float>(h)), Vector2(0.5f, 0.5f));

	SetRotation(-90);

	m_collider = new Collider(this, 16.f, &m_onCollisionEvent);


	if (!m_part_shipExplosion)
	{
		m_part_shipExplosion = new Particle_ShipExplosion();
	}

	Initialize();
}

EnemySpaceShip::~EnemySpaceShip()
{
	delete m_collider;

	if (m_part_shipExplosion)
	m_part_shipExplosion->Destroy();
}

void EnemySpaceShip::OnCollision(GameObject* other)
{
	if (!other)
		return;

	if (other->GetID() == GameObjectID::PLAYER_PROJECTILE)
	{
		if (m_part_shipExplosion)
		{
			m_part_shipExplosion->SetPosition(GetPosition());
			m_part_shipExplosion->Play();
		}

		SetEnabled(false);
	}
}

void EnemySpaceShip::Update(float deltaTime)
{
	const float despawnXPos = -100.f;
	float newYPos;

	switch (m_movePattern)
	{
	case MovePattern::STRAIGHT:
		break;

	case MovePattern::SINWAVE:
		m_sinWaveRadians += m_radiansPerSecond * deltaTime;
		newYPos = m_baseYPos + m_sinAmplitude * sinf(m_sinWaveRadians);
		SetPosition({ GetPosition().x, newYPos });
		break;

	case MovePattern::MOVE_STOP_MOVE:
		if (m_travelledDistance < m_distanceToTravelBeforeStopping)
		{
			m_travelledDistance += m_horizontalSpeed * deltaTime;
			SetPosition(GetPosition() - Vector2{ m_horizontalSpeed, 0 } * deltaTime);
		}
		else
		{
			m_moveSpeedMult += deltaTime;
			if (m_moveSpeedMult > 0)
			{
				SetXSpeed(-m_horizontalSpeed * m_moveSpeedMult * 5.f);
			}
		}
		break;
	}

	if (GetPosition().x < despawnXPos)
	{
		SetEnabled(false);
	}

	if (m_shootTimer <= 0)
	{
		m_shootTimer = m_shootIntervalTime;

		EnemyProjectile* projectile = m_enemyProjectilePool.GetPooledObject();
		if (projectile)
		{
			projectile->Shoot(GetPosition(), GetRotation());
		}
		else
		{
			printf("Projectile was null, so it couldn't be spawned. :(\n");
		}
	}
	else
	{
		m_shootTimer -= deltaTime;
	}
}

void EnemySpaceShip::OnEnabled()
{
	Initialize();
}

void EnemySpaceShip::Initialize()
{
	int rnd = Random::Range(0, 3);
	switch (rnd)
	{
	default:
	case 0:
		m_movePattern = MovePattern::STRAIGHT;
		break;

	case 1:
		m_movePattern = MovePattern::SINWAVE;
		break;

	case 2:
		m_movePattern = MovePattern::MOVE_STOP_MOVE;
		break;
	}

	m_travelledDistance = 0.f;

	m_moveSpeedMult = -m_moveStopTime;

	m_sinWaveRadians = 0;

	m_baseYPos = GetPosition().y;

	if (m_movePattern == MovePattern::STRAIGHT ||
		m_movePattern == MovePattern::SINWAVE)
	{
		SetXSpeed(-m_horizontalSpeed);
	}
	else
	{
		SetXSpeed(0);
	}
}
