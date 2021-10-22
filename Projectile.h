#pragma once

#include "SDL.h"
#include "GameObject.h"
#include "Collider.h"

#include <functional>

class Projectile : public GameObject
{

public:
	Projectile();
	Projectile(const Vector2 position, float rotation, bool enabled);
	~Projectile();

	virtual void OnEstablished() override;

private:
	const float m_defaultSpeed = 600.f;

	const float m_defaultLifetime = 3.f;

	float m_existenceTimer = 0.f;

	Collider* m_collider = nullptr;

protected:
	virtual void OnCollision(GameObject* other);

private:
	Collider::OnCollisionEvent m_onCollisionEvent = [this](GameObject* other) { OnCollision(other); };

protected:
	virtual void Update(float deltaTime) override;

	/*virtual void OnEnabled() override;*/

	//virtual void OnDisabled() override;
	virtual void OnExistenceTerminated() { SetEnabled(false); }

public:
	void Shoot(const Vector2 position, float rotation);

	//virtual GameObjectID GetID() const override { return GameObjectID::PLAYER_PROJECTILE; }

	/*virtual int GetMaxExistingObjects() const override { return 50; }*/

	virtual void DestroyProjectile() { OnExistenceTerminated(); }
	
	virtual float GetProjectileSpeed() const { return m_defaultSpeed; }
	virtual float GetProjectileLifetime() const { return m_defaultLifetime; }
};

