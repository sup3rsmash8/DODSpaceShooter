#pragma once

#include "GameObject.h"
#include "Collider.h"
#include "EnemyProjectile.h"
#include "ObjectPool.h"

class ParticleSystem;

enum class MovePattern
{
	STRAIGHT = 0,
	SINWAVE = 1,
	MOVE_STOP_MOVE = 2,
};

class EnemySpaceShip : public GameObject
{

public:
	EnemySpaceShip();
	EnemySpaceShip(MovePattern movePattern, const Vector2 position, float rotation = 0, bool enabled = true);

	virtual void OnEstablished() override;

private:
	~EnemySpaceShip();

	static const char* m_standardTexturePath;

	//static std::shared_ptr<SDL_Texture> m_standardTexture;
	static SDL_Texture* m_standardTexture;

	ParticleSystem* m_part_shipExplosion = nullptr;

	MovePattern m_movePattern = MovePattern::STRAIGHT;

	// Projectile stuff
	ObjectPool<EnemyProjectile> m_enemyProjectilePool = ObjectPool<EnemyProjectile>();

	// Shooting
	const float m_shootIntervalTime = .8f;
	float m_shootTimer = 0.f;

	// Move pattern stuff

	// STRAIGHT:
	const float m_horizontalSpeed = 200.f;

	// SINWAVE:
	const float m_radiansPerSecond = M_PI * 2.f;
	float m_sinAmplitude = 32.f;
	float m_baseYPos = 0;
	float m_sinWaveRadians = 0;

	// MOVE_STOP_MOVE:
	const float m_moveStopTime = 2.f;
	float m_moveSpeedMult = 1.f;
	const float m_distanceToTravelBeforeStopping = 250.f;
	float m_travelledDistance = 0.f;

	// Collider stuff //
	Collider* m_collider = nullptr;

	std::function<void(GameObject*)> m_onCollisionEvent = [this](GameObject* other) { OnCollision(other); };

	void OnCollision(GameObject* other);

public:
	virtual GameObjectID GetID() const override { return GameObjectID::ENEMY_SHIP; }

protected:
	virtual void Update(float deltaTime) override;

	virtual void OnEnabled() override;

private:
	void Initialize();
};

