#pragma once

#include "Collider.h"
#include "ObjectPool.h"
#include "PlayerProjectile.h"
#include "PlayerObject.h"
#include <string>

class ParticleSystem;

class SpaceShip : public PlayerObject
{
public:
	SpaceShip(const Vector2 position, float rotation, bool enabled);
	~SpaceShip();

	virtual void OnEstablished() override;

private:
	static const char* m_standardTexturePath;

	//static std::shared_ptr<SDL_Texture> m_standardTexture;
	static SDL_Texture* m_standardTexture;
	/*MulticastFunction<Uint8> m_onLivesChanged = MulticastFunction<Uint8>();*/

	ObjectPool<PlayerProjectile> m_projectilePool = ObjectPool<PlayerProjectile>();

	float m_moveSpeed = 200.f;

	// Respawning/Invincibility
	const float m_respawnInvincibilityTime = 3.f;
	float m_respawnTimer = 0.f;

	// Shooting
	const float m_shootIntervalTime = 0.2f;
	float m_shootTimer = 0.f;

	ParticleSystem* m_part_shipExplosion = nullptr;

	Collider* m_collider = nullptr;

	void OnCollision(GameObject* other);

	/*Collider::OnCollisionEvent */
	std::function<void(GameObject*)> m_onCollisionEvent = [this](GameObject* other) { OnCollision(other); };

protected:
	virtual void Update(float deltaTime) override;
	virtual void DrawUpdate(SDL_Renderer* renderer) override;

	void Movement(float deltaTime);

public:
	// Sets the ship's invincibility timer.
	void SetRespawnTimer() { m_respawnTimer = m_respawnInvincibilityTime; }

// Pure virtuals
public:
	//virtual Uint8 GetLives() const override;

	//virtual void SetLives(const Uint8 newLifeCount) override;

	virtual GameObjectID GetID() const override { return GameObjectID::SPACE_SHIP; }

	/*virtual int GetMaxExistingObjects() const override { return 1; }*/
};