#pragma once

#include "EnemyAsteroid.h"
#include "EnemySpaceShip.h"

class WaveSpawner : public GameObject
{
public:
	WaveSpawner(const Vector2 position, float rotation = 0, bool enabled = true);

private:
	float m_timer = 0;

	const float m_spawnTime = 0.5f;

protected:
	ObjectPool<EnemyAsteroid> m_asteroidPool = ObjectPool<EnemyAsteroid>();
	ObjectPool<EnemySpaceShip> m_enemyShipPool = ObjectPool<EnemySpaceShip>();

public:
	virtual void Update(float deltaTime) override;

	virtual GameObjectID GetID() const override { return GameObjectID::WAVE_SPAWNER; }
};

